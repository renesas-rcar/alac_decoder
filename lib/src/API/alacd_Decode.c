/*
 * ALAC Decoder
 *
 * This program has modified by Renesas Electronics Corporation.
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

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2016 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

/****************************************************************/
/*                      INCLUDE FILES                           */
/****************************************************************/
#include "alacd_Lib.h"
#include "common_SubFunc.h"
#include "alacd_MemoryMap.h"

/****************************************************************/
/*                      MACROS/DEFINES                          */
/****************************************************************/
#define DEC_ARG_NUM						(5u)

/****************************************************************/
/*                      LOCAL TYPES                             */
/****************************************************************/
typedef int			 LOC_INT;

/****************************************************************/
/*                      VARIABLES                               */
/****************************************************************/
/*------------------------------
 |			static
 ------------------------------*/

/****************************************************************/
/*                      FORWARD DECLARATIONS                    */
/****************************************************************/
/* ------------------------------------------------------------ */
static void SetBuffInfo( const alacd_ioBufferConfigInfo*	const pBufInfo,
							   alacdec_struct_static*		const pStaticAdr );
/* ------------------------------------------------------------ */
static ACMW_BOOL DecoderMain( alacdec_struct_static*		const pStaticAdr,
							  alacdec_struct_scratch*		const pScratchAdr,
							  ACMW_INT32*					const pCheckErrFact,
							  ACMW_UINT8*					const pWriteBuffer );
/* ------------------------------------------------------------ */
static void SetDecodeResult( const alacdec_struct_scratch*	const pScratchAdr,
							 alacd_decStatusInfo*			const pStatInfo );
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/* ------------------------------------------------------------ */
static void UpdateBuffState( const alacd_ioBufferConfigInfo*	const pBufInfo,
								   alacd_ioBufferStatusInfo*	const pBufStateInfo,
							 const alacdec_struct_static*		const pStaticAdr,
							 const alacdec_struct_scratch*		const pScratchAdr );
/* ------------------------------------------------------------ */

/****************************************************************/
/*                      FUNCTIONS                               */
/****************************************************************/
/*------------------------------------------------------------------------------*/
/*			ALAC API Decode														*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		alacd_Decode
*
* ARGUMENT
* 		alacd_workMemoryInfo*		 pWorkMemInfo
*		alacd_decConfigInfo*		 pDecConfigInfo
*		alacd_ioBufferConfigInfo*	 pBuffConfigInfo
*		alacd_decStatusInfo*		 pDecStatusInfo
*		alacd_ioBufferStatusInfo*	 pBuffStatusInfo
*
* RETURN VALUE
* 		ACMW_INT32 errorCode
*
* OVERVIEW
* 		ALAC frame decoder processing
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_INT32 alacd_Decode( const alacd_workMemoryInfo*		const	pWorkMemInfo,
						 const alacd_decConfigInfo*			const	pDecConfigInfo,
						 const alacd_ioBufferConfigInfo*	const	pBuffConfigInfo,
							   alacd_decStatusInfo*			const	pDecStatusInfo,
							   alacd_ioBufferStatusInfo*	const	pBuffStatusInfo )
{
	ACMW_BOOL	CheckErrorRet[DEC_ARG_NUM];
	ACMW_BOOL	CheckDecRet;
	ACMW_INT32	CheckErrFact;

	ACMW_INT32	RetState;

	alacd_StaticArea*	pStaticArea;
	alacd_ScratchArea*	pScratchArea;

	/*==========================================================================*/
	/* [0] Preprocessing														*/
	/*==========================================================================*/
	/* ---- Argument Check (FATAL Check) -------------------------------------- */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pWorkMemInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	if ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) {								/* Error */
		return ALACD_RESULT_FATAL;												/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */

	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pWorkMemInfo->pStatic, ALIGNMENT_PTR );
	if ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) {								/* Error */
		return ALACD_RESULT_FATAL;												/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	pStaticArea	 = (alacd_StaticArea *)pWorkMemInfo->pStatic;
	/* Error Factor Set */
	pStaticArea->nErrorFactor = ALACD_ERR_NONE;									/* Init */

	/* ---- Other Argument Check 1 (NG Check) --------------------------------- */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pWorkMemInfo->pScratch, ALIGNMENT_PTR );
	CheckErrorRet[ALACD_OFFSET_01] = ArgumentNullCheck( (const void * const)pDecConfigInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	CheckErrorRet[ALACD_OFFSET_02] = ArgumentNullCheck( (const void * const)pBuffConfigInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	CheckErrorRet[ALACD_OFFSET_03] = ArgumentNullCheck( (const void * const)pDecStatusInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	CheckErrorRet[ALACD_OFFSET_04] = ArgumentNullCheck( (const void * const)pBuffStatusInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	if ( ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_01] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_02] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_03] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_04] == TRUE ) ) {							/* Error */

		pStaticArea->nErrorFactor = ALACD_ERR_POINTER;							/* Error Factor Set */

		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Other Argument Check 2 (NG Check) --------------------------------- */
	/* Input  Buffer */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pBuffConfigInfo->pInBuffStart, ALIGNMENT_1BYTE );
	/* Output Buffer */
	CheckErrorRet[ALACD_OFFSET_01] = ArgumentNullCheck( (const void * const)pBuffConfigInfo->pOutBuffStart, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check */
	if ( ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_01] == TRUE ) ) {							/* Error */

		pStaticArea->nErrorFactor = ALACD_ERR_POINTER;							/* Error Factor Set */

		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Other Argument Check 3 (NG Check) --------------------------------- */
	/* Output Buffer */
	if ( (ACMW_UINT32)pStaticArea->stALAC_static.nOutBits == (ACMW_UINT32)0u ) {/* 16bit Output */
		CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pBuffConfigInfo->pOutBuffStart[ALACD_OFFSET_00], ALIGNMENT_2BYTE );
	} else {																	/* 32bit Output */
		CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pBuffConfigInfo->pOutBuffStart[ALACD_OFFSET_00], ALIGNMENT_4BYTE );
	} /* end if */
	if ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) {								/* Error */

		pStaticArea->nErrorFactor = ALACD_ERR_POINTER;							/* Error Factor Set */

		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Other Argument Check 4 (NG Check) - exceptional status read ------- */
	/* Output Buffer */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pBuffStatusInfo->pOutBuffLast, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check */
	if ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) {								/* Error */
		pStaticArea->nErrorFactor = ALACD_ERR_POINTER;							/* Error Factor Set */
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- State Check ------------------------------------------------------- */
	if ( (LOC_INT)pStaticArea->nStateSeq != ALACD_INIT_SEQEND ) {				/* Sequence Error */
		pStaticArea->nErrorFactor = ALACD_ERR_SEQUENCE;							/* Error Factor Set */
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Parameter Check (InBuffer Check) ---------------------------------- */
	if ( pBuffConfigInfo->nInBuffSetDataSize < ALACD_HEAD_LENGTH ) {			/* The size of the Input buffer is insufficient. */
		pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Parameter Check (OutBuffer Check) --------------------------------- */
	if ( (ACMW_UINT32)pStaticArea->stALAC_static.nOutBits == (ACMW_UINT32)0u ) {/* 16bit Output */
		if ( pBuffConfigInfo->nOutBuffSize <
				( ALACD_OUT_BUFF_MIN_SIZE * ALACD_OUTCH_NUM ) ) {				/* The size of the Output buffer is insufficient. */
			pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
			return ALACD_RESULT_NG;												/* MISRA-C:Two or more in function returns */
		} else {
			/* DO NOTHING */
		} /* end if */
	} else {																	/* 32bit Output */
		if ( pBuffConfigInfo->nOutBuffSize <
				( ALACD_OUT_BUFF_MIN_SIZE_32 * ALACD_OUTCH_NUM ) ) {			/* The size of the Output buffer is insufficient. */
			pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
			return ALACD_RESULT_NG;												/* MISRA-C:Two or more in function returns */
		} else {
			/* DO NOTHING */
		} /* end if */
	} /* end if */
	/* ------------------------------------------------------------------------ */
	/*==========================================================================*/

	pScratchArea = (alacd_ScratchArea *)pWorkMemInfo->pScratch;
	/*==========================================================================*/
	/* [1] Frame Decode															*/
	/*==========================================================================*/
	SetBuffInfo( pBuffConfigInfo,												/* Set Buffer Config */
				 &pStaticArea->stALAC_static );

	/* AppleLossless Decoder */
	CheckDecRet = DecoderMain( &pStaticArea->stALAC_static,
							   &pScratchArea->stALAC_scratch,
							   &CheckErrFact,
							   (ACMW_UINT8*)pBuffConfigInfo->pOutBuffStart[0u] );

	SetDecodeResult( &pScratchArea->stALAC_scratch,								/* Set Decode Result Status */
					 pDecStatusInfo );

	UpdateBuffState( pBuffConfigInfo,											/* Set Buffer Status */
					 pBuffStatusInfo,
					 &pStaticArea->stALAC_static,
					 &pScratchArea->stALAC_scratch );
	/*==========================================================================*/

	RetState = ALACD_RESULT_OK;

	/*==========================================================================*/
	/* [2] Postprocessing														*/
	/*==========================================================================*/
	/* ---- Decode After Check ------------------------------------------------ */
	if ( CheckDecRet == TRUE ) {												/* Error */
		if ( CheckErrFact == kALAC_ParamError ) {								/* Input Shortage */
			pStaticArea->nErrorFactor = ALACD_ERR_SHORT_INPUT_DATA;				/* Error Factor Set */
			RetState = ALACD_RESULT_NG;
		} else if ( CheckErrFact == kALAC_ParamError2 ) {						/* Stream RAW Damage */
			pStaticArea->nErrorFactor = ALACD_ERR_STREAM;						/* Error Factor Set */
			RetState = ALACD_RESULT_NG;
		} else {																/* Warning */
			pStaticArea->nErrorFactor = ALACD_ERR_DECODE;						/* Error Factor Set */
			RetState=  ALACD_RESULT_WARNING;
		} /* end if */
	} else {																	/* Normality */
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */
	/*==========================================================================*/

	return RetState;
}


/*------------------------------------------------------------------------------*/
/*			Sub Function														*/
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*	Set Buffer Info																*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		SetBuffInfo
*
* ARGUMENT
* 		alacd_ioBufferConfigInfo*	pBufInfo
*		alacdec_struct_static*		pStaticAdr
*
* RETURN VALUE
* 		void
*
* OVERVIEW
* 		Setting of buffer structures of alac.
*
* DIVERSION ORIGIN
* 		Original.
*
*/
static void SetBuffInfo( const alacd_ioBufferConfigInfo*	const pBufInfo,
							   alacdec_struct_static*		const pStaticAdr )
{
	BitBufferInit( &pStaticAdr->theInputBuffer, pBufInfo->pInBuffStart, pBufInfo->nInBuffSetDataSize );

	return;
}

/*------------------------------------------------------------------------------*/
/*	Decoder Main Function														*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		DecoderMain
*
* ARGUMENT
* 		alacdec_struct_static*	pStaticAdr
* 		alacdec_struct_scratch*	pScratchAdr
*		ACMW_INT32*				pCheckErrFact
*		ACMW_UINT8*				pWriteBuffer
*
* RETURN VALUE
* 		ACMW_BOOL RetError
*			TRUE  : Error
*			FALSE : Non Error
*
* OVERVIEW
* 		AppleLossless Decoder Main Function
*
* DIVERSION ORIGIN
* 		Original.
*
*/
static ACMW_BOOL DecoderMain( alacdec_struct_static*			const pStaticAdr,
							  alacdec_struct_scratch*			const pScratchAdr,
							  ACMW_INT32*						const pCheckErrFact,
							  ACMW_UINT8*						const pWriteBuffer )
{
	ACMW_BOOL		RetError = FALSE;

	/*==========================================================================*/
	/* [1] Set Parameter														*/
	/*==========================================================================*/
	const ALACSpecificConfig*	const pConfig		= &pStaticAdr->mConfig;

	/*==========================================================================*/
	/* [2] Decode																*/
	/*==========================================================================*/
	*pCheckErrFact = ALACDecoder_Decode( &pStaticAdr->theInputBuffer,
										 pWriteBuffer,
										 pConfig->frameLength,
										 (ACMW_UINT32)pConfig->numChannels,
										 pScratchAdr,
										 pStaticAdr );
	/*==========================================================================*/

	/*==========================================================================*/
	/* [3] Check Result															*/
	/*==========================================================================*/
	if ( *pCheckErrFact != (ACMW_INT32)0 ) {									/* Error */
		RetError = TRUE;
	} else {
		/* DO NOTHING */
	} /* end if */

	return RetError;
}

/*------------------------------------------------------------------------------*/
/*	Set Decode Result Status													*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		SetDecodeResult
*
* ARGUMENT
*		alacdec_struct_scratch*		pScratchAdr
*		alacd_decStatusInfo*		pStatInfo
*
* RETURN VALUE
* 		ACMW_BOOL RetError
*			TRUE  : Error
*			FALSE : Non Error
*
* OVERVIEW
* 		Decoder result is stored. 
*
* DIVERSION ORIGIN
* 		Original.
*
*/
static void SetDecodeResult( const alacdec_struct_scratch*	const pScratchAdr,
							 alacd_decStatusInfo*			const pStatInfo )
{
	pStatInfo->nSamplesPerFrame = (ACMW_UINT16)pScratchAdr->nOutNumSamples;
	pStatInfo->nChannelNum		= (ACMW_UINT16)pScratchAdr->nChannelIndex;

	return;
}

/*------------------------------------------------------------------------------*/
/*	Update Buff State															*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		UpdateBuffState
*
* ARGUMENT
* 		alacd_ioBufferConfigInfo*	pBufInfo
*		alacd_ioBufferStatusInfo*	pBufStateInfo
*		alacdec_struct_static*		pStaticAdr
* 		alacdec_struct_scratch*		pScratchAdr
*
* RETURN VALUE
* 		void
*
* OVERVIEW
* 		Update of buffer structures.
*
* DIVERSION ORIGIN
* 		Original.
*
*/
static void UpdateBuffState( const alacd_ioBufferConfigInfo*	const pBufInfo,
								   alacd_ioBufferStatusInfo*	const pBufStateInfo,
							 const alacdec_struct_static*		const pStaticAdr,
							 const alacdec_struct_scratch*		const pScratchAdr )
{
	ACMW_UINT32		UsedLenOut;
	const BitBuffer* const pBuf			= &pStaticAdr->theInputBuffer;

	pBufStateInfo->pInBuffLast			= pBuf->cur;
	pBufStateInfo->nInBuffUsedDataSize	= (ACMW_UINT32)(pBuf->cur - pBufInfo->pInBuffStart);

	if ( (ACMW_UINT32)pStaticAdr->nOutBits == (ACMW_UINT32)0u ) {				/* 16bit Output */
		UsedLenOut = (ACMW_UINT32)(pScratchAdr->nOutNumSamples * pScratchAdr->nChannelIndex * ALACD_BYTE_PER_SAMP);
		pBufStateInfo->pOutBuffLast[ALACD_OFFSET_00]	= (ACMW_UINT16*)( (ACMW_UINT8 *)pBufInfo->pOutBuffStart[ALACD_OFFSET_00] + UsedLenOut );
	} else {																	/* 32bit Output */
		UsedLenOut = (ACMW_UINT32)(pScratchAdr->nOutNumSamples * pScratchAdr->nChannelIndex * ALACD_BYTE_PER_SAMP_32);
		pBufStateInfo->pOutBuffLast[ALACD_OFFSET_00]	= (ACMW_UINT32*)( (ACMW_UINT8 *)pBufInfo->pOutBuffStart[ALACD_OFFSET_00] + UsedLenOut );
	} /* end if */

	pBufStateInfo->nOutBuffUsedDataSize	= UsedLenOut;

	return;
}
/*------------------------------------------------------------------------------*/

/* End of File */
