/*
 * ALAC Decoder
 *
 * This program has modified by Renesas Electronics Corporation.
 * The original source code is open source software under the Apache License.
 * This file is subject to the terms and conditions of the APPLE PUBLIC SOURCE LICENSE.
 * See the file "APPLE_LICENSE.txt" in the main directory of this archive for more details.
 *
 *
 * Portions Copyright (c) 1999-2007 Apple Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code as
 * defined in and that are subject to the Apple Public Source License Version 2.0
 * (the 'License').  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.  Please see the License for the
 * specific language governing rights and limitations under the License.
 */

/*
 * Copyright (c) 2011 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

/*
	File:		ALACDecoder.c
*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2016 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#include "dplib.h"
#include "aglib.h"
#include "matrixlib.h"

#include "alacd_IfPackage.h"

static int32_t	ALACDecoder_FillElement( BitBuffer * bits );
static int32_t	ALACDecoder_DataStreamElement( BitBuffer * bits );

// prototypes
static void Zero16( int16_t * buffer, uint32_t numItems, uint32_t stride );
#if 0
static void Zero24( uint8_t * buffer, uint32_t numItems, uint32_t stride );
#endif
static void Zero32( int32_t * buffer, uint32_t numItems, uint32_t stride );
static void LocMemSet( void* const pTo, const uint8_t nData, const int32_t nSize );

/*
	Decode()
	- the decoded samples are interleaved into the output buffer in the order they arrive in
	  the bitstream
*/
int32_t ALACDecoder_Decode( BitBuffer * bits, uint8_t * sampleBuffer, uint32_t numSamples, uint32_t numChannels,
							alacdec_struct_scratch* const pScratchAdr, alacdec_struct_static* const pStaticAdr )
{
	BitBuffer			shiftBits;
	uint32_t			bits1, bits2;
	uint8_t				tag;
	uint8_t				elementInstanceTag;
	AGParamRec			agParams;
	uint32_t			channelIndex;
	int16_t				coefsU[32];		// max possible size is 32 although NUMCOEPAIRS is the current limit
	int16_t				coefsV[32];
	uint8_t				numU, numV;
	uint8_t				mixBits;
	int8_t				mixRes;
	uint16_t			unusedHeader;
	uint8_t				escapeFlag;
	uint32_t			chanBits;
	int32_t				bytesShifted;
	uint32_t			shift;
	uint8_t				modeU, modeV;
	uint32_t			denShiftU, denShiftV;
	uint16_t			pbFactorU, pbFactorV;
	uint16_t			pb;
	int16_t *			out16;
	uint8_t *			out20;
	uint8_t *			out24;
	int32_t *			out32;
	uint8_t				headerByte;
	uint8_t				partialFrame;
	uint32_t			extraBits;
	int32_t				val;
	uint32_t			i, j;
	int32_t				status;
	uint16_t			mActiveElements;
	ALACBuffer*			pMixBuf;
	int32_t*			mMixBufferU;
	int32_t*			mMixBufferV;
	int32_t*			mPredictor;
	uint16_t*			mShiftBuffer;
	ALACSpecificConfig*	pConfig;

	mActiveElements = 0;
	channelIndex	= 0;

	pConfig = &pStaticAdr->mConfig;
	status = ALAC_noErr;
	pScratchAdr->nOutNumSamples = (uint32_t)0u;									/* Default */

	/* ---- Set Buffer -------------------------------------------------------- */
	pMixBuf			= &(pScratchAdr->theOutputBuffer);
	mMixBufferU		= &(pMixBuf->aMixBufU[0u]);									/* allocate mix buffers */
	mMixBufferV		= &(pMixBuf->aMixBufV[0u]);
	mPredictor		= &(pMixBuf->aPredBuf[0u]);									/* allocate dynamic predictor buffer */
	mShiftBuffer	= (uint16_t*)mPredictor;									/* "shift off" buffer shares memory with predictor buffer */
	/* ------------------------------------------------------------------------ */

	while ( status == ALAC_noErr )
	{
		// bail if we ran off the end of the buffer
		RequireAction( bits->cur < bits->end, status = kALAC_ParamError; goto Exit; );

		// copy global decode params for this element
		pb = pConfig->pb;

		// read element tag
		tag = BitBufferReadSmall( bits, 3 );
		switch ( tag )
		{
			case ID_SCE:
			case ID_LFE:
			{
				if ( (channelIndex + (uint32_t)1u) > numChannels ) {			/* fail safe */
					status = kALAC_ParamError3;									/* Warning */
					goto NoMoreChannels;
				} else {
					/* DO NOTHING */
				} /* end if */

				// mono/LFE channel
				elementInstanceTag = BitBufferReadSmall( bits, 4 );
				mActiveElements |= (1u << elementInstanceTag);

				// read the 12 unused header bits
				unusedHeader = (uint16_t) BitBufferRead( bits, 12 );
				RequireAction( unusedHeader == 0, status = kALAC_ParamError2; goto Exit; );

				// read the 1-bit "partial frame" flag, 2-bit "shift-off" flag & 1-bit "escape" flag
				headerByte = (uint8_t) BitBufferRead( bits, 4 );
				
				partialFrame = headerByte >> 3;
				
				bytesShifted = (int32_t)((headerByte >> 1) & 0x3u);
				RequireAction( bytesShifted != 3, status = kALAC_ParamError2; goto Exit; );

				shift = (uint32_t)(bytesShifted * 8);

				escapeFlag = headerByte & 0x1;

				chanBits = (uint32_t)(pConfig->bitDepth - (bytesShifted * 8));
				
				// check for partial frame to override requested numSamples
				if ( partialFrame != 0 )
				{
					numSamples  = BitBufferRead( bits, 16 ) << 16;
					numSamples |= BitBufferRead( bits, 16 );
					RequireAction( numSamples <= kALACDefaultFrameSize, status = kALAC_ParamError2; goto Exit; );
				}

				if ( escapeFlag == 0 )
				{
					// compressed frame, read rest of parameters
					mixBits	= (uint8_t) BitBufferRead( bits, 8 );
					mixRes	= (int8_t) BitBufferRead( bits, 8 );
					//Assert( (mixBits == 0) && (mixRes == 0) );		// no mixing for mono

					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					modeU		= headerByte >> 4;
					denShiftU	= headerByte & 0xfu;
					
					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					pbFactorU	= headerByte >> 5;
					numU		= headerByte & 0x1fu;

					for ( i = 0; i < numU; i++ )
						coefsU[i] = (int16_t) BitBufferRead( bits, 16 );
					
					// if shift active, skip the the shift buffer but remember where it starts
					if ( bytesShifted != 0 )
					{
						shiftBits = *bits;
						BitBufferAdvance( bits, (uint32_t)((uint32_t)(bytesShifted * 8) * numSamples) ); 
					}

					// decompress
					set_ag_params( &agParams, pConfig->mb, (pb * pbFactorU) / 4, pConfig->kb, numSamples, numSamples, pConfig->maxRun );
					status = dyn_decomp( &agParams, bits, mPredictor, numSamples, chanBits, &bits1 );
					RequireNoErr( status, goto Exit; );

					if ( modeU == 0 )
					{
						unpc_block( mPredictor, mMixBufferU, (int32_t)numSamples, &coefsU[0], (int32_t)numU, chanBits, denShiftU );
					}
					else
					{
						// the special "numActive == 31" mode can be done in-place
						unpc_block( mPredictor, mPredictor, (int32_t)numSamples, nil, 31, chanBits, 0 );
						unpc_block( mPredictor, mMixBufferU, (int32_t)numSamples, &coefsU[0], (int32_t)numU, chanBits, denShiftU );
					}
				}
				else
				{
					//Assert( bytesShifted == 0 );

					// uncompressed frame, copy data into the mix buffer to use common output code
					shift = 32 - chanBits;
					if ( chanBits <= 16 )
					{
						for ( i = 0; i < numSamples; i++ )
						{
							val = (int32_t) BitBufferRead( bits, (uint8_t) chanBits );
							val = (val << shift) >> shift;
							mMixBufferU[i] = val;
						}
					}
					else
					{
						// BitBufferRead() can't read more than 16 bits at a time so break up the reads
						extraBits = chanBits - 16;
						for ( i = 0; i < numSamples; i++ )
						{
							val = (int32_t) BitBufferRead( bits, 16 );
							val = (val << 16) >> shift;
							mMixBufferU[i] = val | (int32_t)BitBufferRead( bits, (uint8_t) extraBits );
						}
					}

					mixBits = 0u;
					mixRes = 0;
					bits1 = chanBits * numSamples;
					bytesShifted = 0;
				}

				// now read the shifted values into the shift buffer
				if ( bytesShifted != 0 )
				{
					shift = (uint32_t)(bytesShifted * 8);
					//Assert( shift <= 16 );

					for ( i = 0; i < numSamples; i++ )
						mShiftBuffer[i] = (uint16_t) BitBufferRead( &shiftBits, (uint8_t) shift );
				}

				if ( (uint32_t)pStaticAdr->nOutBits == (uint32_t)0u ) {
					// convert 32-bit integers into output buffer
					switch ( pConfig->bitDepth )
					{
						case 16:
							out16 = &((int16_t *)sampleBuffer)[channelIndex];
							for ( i = 0, j = 0; i < numSamples; i++, j += numChannels )
								out16[j] = (int16_t) mMixBufferU[i];
							break;
						case 20:
							out20 = (uint8_t *)sampleBuffer + (channelIndex * 2);
							copyPredictorTo20( mMixBufferU, out20, numChannels, (int32_t)numSamples );
							break;
						case 24:
							out24 = (uint8_t *)sampleBuffer + (channelIndex * 2);
							if ( bytesShifted != 0 )
								copyPredictorTo24Shift( mMixBufferU, mShiftBuffer, out24, numChannels, (int32_t)numSamples, bytesShifted );
							else
								copyPredictorTo24( mMixBufferU, out24, numChannels, (int32_t)numSamples );							
							break;
						default:	/* 32 */
							out16 = &((int16_t *)sampleBuffer)[channelIndex];
							if ( bytesShifted != 0 )
								copyPredictorTo32Shift( mMixBufferU, mShiftBuffer, out16, numChannels, (int32_t)numSamples, bytesShifted );
							else
								copyPredictorTo32( mMixBufferU, out16, numChannels, (int32_t)numSamples);
							break;
					}
				} else {
					switch ( pConfig->bitDepth )
					{
						case 16:
							out32 = &((int32_t *)sampleBuffer)[channelIndex];
							for ( i = 0, j = 0; i < numSamples; i++, j += numChannels )
								out32[j] = (int32_t)(((uint32_t)mMixBufferU[i] << 16) & (uint32_t)0xFFFF0000u);				/* LITTLE ENDIAN */
							break;
						case 20:
							out20 = (uint8_t *)sampleBuffer + (channelIndex * 4);
							copyPredictorTo20_32( mMixBufferU, out20, numChannels, (int32_t)numSamples );
							break;
						case 24:
							out24 = (uint8_t *)sampleBuffer + (channelIndex * 4);
							if ( bytesShifted != 0 )
								copyPredictorTo24Shift_32( mMixBufferU, mShiftBuffer, out24, numChannels, (int32_t)numSamples, bytesShifted );
							else
								copyPredictorTo24_32( mMixBufferU, out24, numChannels, (int32_t)numSamples );							
							break;
						default:	/* 32 */
							out32 = &((int32_t *)sampleBuffer)[channelIndex];
							if ( bytesShifted != 0 )
								copyPredictorTo32Shift_32( mMixBufferU, mShiftBuffer, out32, numChannels, (int32_t)numSamples, bytesShifted );
							else
								copyPredictorTo32_32( mMixBufferU, out32, numChannels, (int32_t)numSamples);
							break;
					} /* end switch */
				} /* end if */

				channelIndex += 1;
				pScratchAdr->nOutNumSamples = numSamples;
				break;
			}

			case ID_CPE:
			{
				// if decoding this pair would take us over the max channels limit, bail
				if ( (channelIndex + (uint32_t)2u) > numChannels ) {
					status = kALAC_ParamError3;									/* Warning */
					goto NoMoreChannels;
				} else {
					/* DO NOTHING */
				} /* end if */

				// stereo channel pair
				elementInstanceTag = BitBufferReadSmall( bits, 4 );
				mActiveElements |= (1u << elementInstanceTag);

				// read the 12 unused header bits
				unusedHeader = (uint16_t) BitBufferRead( bits, 12 );
				RequireAction( unusedHeader == 0, status = kALAC_ParamError2; goto Exit; );

				// read the 1-bit "partial frame" flag, 2-bit "shift-off" flag & 1-bit "escape" flag
				headerByte = (uint8_t) BitBufferRead( bits, 4 );
				
				partialFrame = headerByte >> 3;
				
				bytesShifted = (int32_t)((headerByte >> 1) & 0x3u);
				RequireAction( bytesShifted != 3, status = kALAC_ParamError2; goto Exit; );

				shift = (uint32_t)(bytesShifted * 8);

				escapeFlag = headerByte & 0x1;

				chanBits = (uint32_t)(pConfig->bitDepth - (bytesShifted * 8) + 1);
				
				// check for partial frame length to override requested numSamples
				if ( partialFrame != 0 )
				{
					numSamples  = BitBufferRead( bits, 16 ) << 16;
					numSamples |= BitBufferRead( bits, 16 );
					RequireAction( numSamples <= kALACDefaultFrameSize, status = kALAC_ParamError2; goto Exit; );
				}

				if ( escapeFlag == 0 )
				{
					// compressed frame, read rest of parameters
					mixBits		= (uint8_t) BitBufferRead( bits, 8 );
					mixRes		= (int8_t) BitBufferRead( bits, 8 );

					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					modeU		= headerByte >> 4;
					denShiftU	= headerByte & 0xfu;
					
					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					pbFactorU	= headerByte >> 5;
					numU		= headerByte & 0x1fu;
					for ( i = 0; i < numU; i++ )
						coefsU[i] = (int16_t) BitBufferRead( bits, 16 );

					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					modeV		= headerByte >> 4;
					denShiftV	= headerByte & 0xfu;
					
					headerByte	= (uint8_t) BitBufferRead( bits, 8 );
					pbFactorV	= headerByte >> 5;
					numV		= headerByte & 0x1fu;
					for ( i = 0; i < numV; i++ )
						coefsV[i] = (int16_t) BitBufferRead( bits, 16 );

					// if shift active, skip the interleaved shifted values but remember where they start
					if ( bytesShifted != 0 )
					{
						shiftBits = *bits;
						BitBufferAdvance( bits, (uint32_t)((uint32_t)(bytesShifted * 8) * 2 * numSamples) );
					}

					// decompress and run predictor for "left" channel
					set_ag_params( &agParams, pConfig->mb, (pb * pbFactorU) / 4, pConfig->kb, numSamples, numSamples, pConfig->maxRun );
					status = dyn_decomp( &agParams, bits, mPredictor, numSamples, chanBits, &bits1 );
					RequireNoErr( status, goto Exit; );

					if ( modeU == 0 )
					{
						unpc_block( mPredictor, mMixBufferU, (int32_t)numSamples, &coefsU[0], (int32_t)numU, chanBits, denShiftU );
					}
					else
					{
						// the special "numActive == 31" mode can be done in-place
						unpc_block( mPredictor, mPredictor, (int32_t)numSamples, nil, 31, chanBits, 0 );
						unpc_block( mPredictor, mMixBufferU, (int32_t)numSamples, &coefsU[0], (int32_t)numU, chanBits, denShiftU );
					}

					// decompress and run predictor for "right" channel
					set_ag_params( &agParams, pConfig->mb, (pb * pbFactorV) / 4, pConfig->kb, numSamples, numSamples, pConfig->maxRun );
					status = dyn_decomp( &agParams, bits, mPredictor, numSamples, chanBits, &bits2 );
					RequireNoErr( status, goto Exit; );

					if ( modeV == 0 )
					{
						unpc_block( mPredictor, mMixBufferV, (int32_t)numSamples, &coefsV[0], (int32_t)numV, chanBits, denShiftV );
					}
					else
					{
						// the special "numActive == 31" mode can be done in-place
						unpc_block( mPredictor, mPredictor, (int32_t)numSamples, nil, 31, chanBits, 0 );
						unpc_block( mPredictor, mMixBufferV, (int32_t)numSamples, &coefsV[0], (int32_t)numV, chanBits, denShiftV );
					}
				}
				else
				{
					//Assert( bytesShifted == 0 );

					// uncompressed frame, copy data into the mix buffers to use common output code
					chanBits = pConfig->bitDepth;
					shift = 32 - chanBits;
					if ( chanBits <= 16 )
					{
						for ( i = 0; i < numSamples; i++ )
						{
							val = (int32_t) BitBufferRead( bits, (uint8_t) chanBits );
							val = (val << shift) >> shift;
							mMixBufferU[i] = val;

							val = (int32_t) BitBufferRead( bits, (uint8_t) chanBits );
							val = (val << shift) >> shift;
							mMixBufferV[i] = val;
						}
					}
					else
					{
						// BitBufferRead() can't read more than 16 bits at a time so break up the reads
						extraBits = chanBits - 16;
						for ( i = 0; i < numSamples; i++ )
						{
							val = (int32_t) BitBufferRead( bits, 16 );
							val = (val << 16) >> shift;
							mMixBufferU[i] = val | (int32_t)BitBufferRead( bits, (uint8_t)extraBits );

							val = (int32_t) BitBufferRead( bits, 16 );
							val = (val << 16) >> shift;
							mMixBufferV[i] = val | (int32_t)BitBufferRead( bits, (uint8_t)extraBits );
						}
					}

					bits1 = chanBits * numSamples;
					bits2 = chanBits * numSamples;
					mixBits = 0u;
					mixRes = 0;
					bytesShifted = 0;
				}

				// now read the shifted values into the shift buffer
				if ( bytesShifted != 0 )
				{
					shift = (uint32_t)(bytesShifted * 8);
					//Assert( shift <= 16 );

					for ( i = 0; i < (numSamples * 2); i += 2 )
					{
						mShiftBuffer[i + 0] = (uint16_t) BitBufferRead( &shiftBits, (uint8_t) shift );
						mShiftBuffer[i + 1] = (uint16_t) BitBufferRead( &shiftBits, (uint8_t) shift );
					}
				}

				if ( (uint32_t)pStaticAdr->nOutBits == (uint32_t)0u ) {
					// un-mix the data and convert to output format
					// - note that mixRes = 0 means just interleave so we use that path for uncompressed frames
					switch ( pConfig->bitDepth )
					{
						case 16:
							out16 = &((int16_t *)sampleBuffer)[channelIndex];
							unmix16( mMixBufferU, mMixBufferV, out16, numChannels, (int32_t)numSamples, (int32_t)mixBits, mixRes );
							break;
						case 20:
							out20 = (uint8_t *)sampleBuffer + (channelIndex * 2);
							unmix20( mMixBufferU, mMixBufferV, out20, numChannels, (int32_t)numSamples, (int32_t)mixBits, mixRes );
							break;
						case 24:
							out24 = (uint8_t *)sampleBuffer + (channelIndex * 2);
							unmix24( mMixBufferU, mMixBufferV, out24, numChannels, (int32_t)numSamples,
										(int32_t)mixBits, mixRes, mShiftBuffer, bytesShifted );
							break;
						default:	/* 32 */
							out16 = &((int16_t *)sampleBuffer)[channelIndex];
							unmix32( mMixBufferU, mMixBufferV, out16, numChannels, (int32_t)numSamples,
										(int32_t)mixBits, mixRes, mShiftBuffer, bytesShifted );
							break;
					}
				} else {
					switch ( pConfig->bitDepth )
					{
						case 16:
							out32 = &((int32_t *)sampleBuffer)[channelIndex];
							unmix16_32( mMixBufferU, mMixBufferV, out32, numChannels, (int32_t)numSamples, (int32_t)mixBits, mixRes );
							break;
						case 20:
							out20 = (uint8_t *)sampleBuffer + (channelIndex * 4);
							unmix20_32( mMixBufferU, mMixBufferV, out20, numChannels, (int32_t)numSamples, (int32_t)mixBits, mixRes );
							break;
						case 24:
							out24 = (uint8_t *)sampleBuffer + (channelIndex * 4);
							unmix24_32( mMixBufferU, mMixBufferV, out24, numChannels, (int32_t)numSamples,
										(int32_t)mixBits, mixRes, mShiftBuffer, bytesShifted );
							break;
						default:	/* 32 */
							out32 = &((int32_t *)sampleBuffer)[channelIndex];
							unmix32_32( mMixBufferU, mMixBufferV, out32, numChannels, (int32_t)numSamples,
										(int32_t)mixBits, mixRes, mShiftBuffer, bytesShifted );
							break;
					} /* end switch */
				} /* end if */

				channelIndex += 2;
				pScratchAdr->nOutNumSamples = numSamples;
				break;
			}

			case ID_CCE:
			case ID_PCE:
			{
				// unsupported element, bail
				//AssertNoErr( tag );
				status = kALAC_ParamError2;
				break;
			}

			case ID_DSE:
			{
				// data stream element -- parse but ignore
				status = ALACDecoder_DataStreamElement( bits );
				break;
			}
			
			case ID_FIL:
			{
				// fill element -- parse but ignore
				status = ALACDecoder_FillElement( bits );
				break;
			}

			default:	/* ID_END */
			{
				// frame end, all done so byte align the frame and check for overruns
				BitBufferByteAlign( bits, FALSE );
				//Assert( bits->cur == bits->end );
				if ( ( (uint32_t)mActiveElements != (uint32_t)0u ) &&			/* SCE/CPE */
					 ( channelIndex < numChannels ) ) {
					status = kALAC_ParamError3;									/* Warning */
					goto NoMoreChannels;
				} else {
					/* DO NOTHING */
				} /* end if */
				goto Exit;
			}
		}
	}

	RequireAction( channelIndex != (uint32_t)0u, goto Exit; );					/* No OutputPCM */

NoMoreChannels:

	// if we get here and haven't decoded all of the requested channels, fill the remaining channels with zeros
	for ( ; channelIndex < numChannels; channelIndex++ )
	{
		if ( (uint32_t)pStaticAdr->nOutBits == (uint32_t)0u ) {
			int16_t *	fill16 = &((int16_t *)sampleBuffer)[channelIndex];
			Zero16( fill16, numSamples, numChannels );
		} else {
			int32_t *	fill32 = &((int32_t *)sampleBuffer)[channelIndex];
			Zero32( fill32, numSamples, numChannels );
		} /* end if */
		pScratchAdr->nOutNumSamples = numSamples;
	} /* end for */

Exit:
	if ( ( status != (int32_t)0 ) &&
		 ( pScratchAdr->nOutNumSamples != (uint32_t)0u ) ) {					/* Error and Output */
		status = kALAC_ParamError3;												/* Warning */
	} else {
		/* DO NOTHING */
	} /* end if */

	pScratchAdr->nChannelIndex = channelIndex;
	return status;
}

/*
	FillElement()
	- they're just filler so we don't need 'em
*/
static int32_t ALACDecoder_FillElement( BitBuffer * bits )
{
	uint16_t		count;
	
	// 4-bit count or (4-bit + 8-bit count) if 4-bit count == 15
	// - plus this weird -1 thing I still don't fully understand
	count = BitBufferReadSmall( bits, 4 );
	if ( count == 15 )
		count += (int16_t) BitBufferReadSmall( bits, 8 ) - 1;

	BitBufferAdvance( bits, count * 8 );

	RequireAction( bits->cur <= bits->end, return kALAC_ParamError; );

	return ALAC_noErr;	
}

/*
	DataStreamElement()
	- we don't care about data stream elements so just skip them
*/
static int32_t ALACDecoder_DataStreamElement( BitBuffer * bits )
{
	uint8_t		element_instance_tag;
	int32_t		data_byte_align_flag;
	uint16_t		count;
	
	// the tag associates this data stream element with a given audio element
	element_instance_tag = BitBufferReadSmall( bits, 4 );
	
	data_byte_align_flag = (int32_t)BitBufferReadOne( bits );

	// 8-bit count or (8-bit + 8-bit count) if 8-bit count == 255
	count = BitBufferReadSmall( bits, 8 );
	if ( count == 255 )
		count += BitBufferReadSmall( bits, 8 );

	// the align flag means the bitstream should be byte-aligned before reading the following data bytes
	if ( data_byte_align_flag )
		BitBufferByteAlign( bits, FALSE );

	// skip the data bytes
	BitBufferAdvance( bits, count * 8 );

	RequireAction( bits->cur <= bits->end, return kALAC_ParamError; );

	return ALAC_noErr;
}

/*
	ZeroN()
	- helper routines to clear out output channel buffers when decoding fewer channels than requested
*/
static void Zero16( int16_t * buffer, uint32_t numItems, uint32_t stride )
{
	if ( stride == 1 )
	{
		LocMemSet( buffer, 0, (int32_t)(numItems * sizeof(int16_t)) );
	}
	else
	{
		uint32_t index;

		for ( index = 0; index < (numItems * stride); index += stride )
			buffer[index] = 0;
	}
}
#if 0
static void Zero24( uint8_t * buffer, uint32_t numItems, uint32_t stride )
{
	if ( stride == 1 )
	{
		LocMemSet( buffer, 0, numItems * 3 );
	}
	else
	{
		uint32_t index;

		for ( index = 0; index < (numItems * stride * 3); index += (stride * 3) )
		{
			buffer[index + 0] = 0;
			buffer[index + 1] = 0;
			buffer[index + 2] = 0;
		}
	}
}
#endif
static void Zero32( int32_t * buffer, uint32_t numItems, uint32_t stride )
{
	if ( stride == 1 )
	{
		LocMemSet( buffer, 0, (int32_t)(numItems * sizeof(int32_t)) );
	}
	else
	{
		uint32_t index;

		for ( index = 0; index < (numItems * stride); index += stride )
			buffer[index] = 0;
	}
}

/* ---------------------------------------------------------------------------- */

static void LocMemSet( void* const pTo,
				const uint8_t nData,
				const int32_t nSize )
{
	uint8_t* const ptrDest = (uint8_t* const)pTo;

	if ( ( pTo != NULL ) && ( nSize > LOC_MEMSIZE_MIN ) ) {
		int_t	index;															/* for counter */
		/* The address of the setting destination isn't NULL and the established size is normal. */
		for ( index = 0; index < nSize; index++ ) {
			ptrDest[index] = nData;
		} /* end for */
	} else {
		/* The address of the setting destination is NULL or the established size is abnormal. */
		/* DO NOTHING */
	} /* end if */

	return;
}
