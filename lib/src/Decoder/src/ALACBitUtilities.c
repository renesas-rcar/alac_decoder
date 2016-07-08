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

/*=============================================================================
    File:		ALACBitUtilities.c

	$NoKeywords: $
=============================================================================*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2015 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#include "ALACBitUtilities.h"

// BitBufferInit
//
void BitBufferInit( BitBuffer * bits, uint8_t * buffer, uint32_t byteSize )
{
	bits->cur		= buffer;
	bits->end		= bits->cur + byteSize;
	bits->bitIndex	= 0;
	bits->byteSize	= byteSize;
}

// BitBufferRead
//
uint32_t BitBufferRead( BitBuffer * bits, uint8_t numBits )
{
	uint32_t		returnBits;
	
	//Assert( numBits <= 16 );

	returnBits = ((uint32_t)bits->cur[0] << 16) | ((uint32_t)bits->cur[1] << 8) | ((uint32_t)bits->cur[2]);
	returnBits = returnBits << bits->bitIndex;
	returnBits &= (uint32_t)0x00FFFFFFu;
	
	bits->bitIndex += numBits;
	
	returnBits = returnBits >> (24 - numBits);
	
	bits->cur		+= (bits->bitIndex >> 3);
	bits->bitIndex	&= 7;
	
	//Assert( bits->cur <= bits->end );
	
	return returnBits;
}

// BitBufferReadSmall
//
// Reads up to 8 bits
uint8_t BitBufferReadSmall( BitBuffer * bits, uint8_t numBits )
{
	uint16_t		returnBits;
	
	//Assert( numBits <= 8 );
	
	returnBits = (uint16_t)(((uint32_t)bits->cur[0] << 8) | (uint32_t)bits->cur[1]);
	returnBits = returnBits << bits->bitIndex;
	
	bits->bitIndex += numBits;
	
	returnBits = returnBits >> (16 - numBits);
	
	bits->cur		+= (bits->bitIndex >> 3);
	bits->bitIndex	&= 7;
	
	//Assert( bits->cur <= bits->end );
	
	return (uint8_t)returnBits;
}

// BitBufferReadOne
//
// Reads one byte
uint8_t BitBufferReadOne( BitBuffer * bits )
{
	uint8_t		returnBits;

	returnBits = (bits->cur[0] >> (7 - bits->bitIndex)) & 1;

	bits->bitIndex++;
	
	bits->cur		+= (bits->bitIndex >> 3);
	bits->bitIndex	&= 7;
	
	//Assert( bits->cur <= bits->end );
	
	return returnBits;
}

// BitBufferByteAlign
//
void BitBufferByteAlign( BitBuffer * bits, int32_t addZeros )
{
	// align bit buffer to next byte boundary, writing zeros if requested
	if ( bits->bitIndex == 0 )
		return;

	if ( addZeros ) {
		#if 0	/* Only an Encoder is used. */
		BitBufferWrite( bits, 0, 8 - bits->bitIndex );
		#else
		/* DO NOTHING */
		#endif
	} else {
		BitBufferAdvance( bits, 8 - bits->bitIndex );
	} /* end if */
}

// BitBufferAdvance
//
void BitBufferAdvance( BitBuffer * bits, uint32_t numBits )
{
	if ( numBits )
	{
		bits->bitIndex += numBits;
		bits->cur += (bits->bitIndex >> 3);
		bits->bitIndex &= 7;
	}
}
#if 0
void	BitBufferReset( BitBuffer * bits )
//void BitBufferInit( BitBuffer * bits, uint8_t * buffer, uint32_t byteSize )
{
	bits->cur		= bits->end - bits->byteSize;
    bits->bitIndex	= 0;
}
#endif
