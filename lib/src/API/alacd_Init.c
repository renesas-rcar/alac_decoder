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
/* Copyright(C) 2014-2015 Renesas Electronics Corporation.                      */
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
#define INIT_ARG_NUM					(2u)

/****************************************************************/
/*                      LOCAL TYPES                             */
/****************************************************************/

/****************************************************************/
/*                      VARIABLES                               */
/****************************************************************/
/*------------------------------
 |			static
 ------------------------------*/

/****************************************************************/
/*                      FORWARD DECLARATIONS                    */
/****************************************************************/

/****************************************************************/
/*                      FUNCTIONS                               */
/****************************************************************/
/*------------------------------------------------------------------------------*/
/*			ALAC API Init														*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		alacd_Init
*
* ARGUMENT
* 		alacd_workMemoryInfo* pWorkMemInfo
* 		alacd_initConfigInfo* pInitConfigInfo
*
* RETURN VALUE
* 		ACMW_INT32 errorCode
*
* OVERVIEW
* 		Initialization
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_INT32 alacd_Init( const alacd_workMemoryInfo* const pWorkMemInfo,
					   const alacd_initConfigInfo* const pInitConfigInfo )
{
	ACMW_BOOL	CheckErrorRet[INIT_ARG_NUM];
	alacd_StaticArea*	pStaticArea;
	alacd_ScratchArea*	pScratchArea;
	ALACSpecificConfig* pConfig;

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

	pStaticArea = (alacd_StaticArea *)pWorkMemInfo->pStatic;
	/*==========================================================================*/
	/* 	Initialization [1]														*/
	/*==========================================================================*/
	ComMemSet( &pStaticArea->stALAC_static, 0u, ALACD_MEM_STATIC_SIZE );		/* Static  Initialization */

	/* Error Factor Set */
	pStaticArea->nErrorFactor = ALACD_ERR_NONE;									/* Init */
	pStaticArea->nStateSeq	 = (ACMW_UINT8)ALACD_INIT_SEQSTART;					/* Init Start */

	/* ---- 2nd Argument Check (NG Check) ------------------------------------- */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pWorkMemInfo->pScratch, ALIGNMENT_PTR );
	CheckErrorRet[ALACD_OFFSET_01] = ArgumentNullCheck( (const void * const)pInitConfigInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	if ( ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_01] == TRUE ) ) {							/* Error */

		pStaticArea->nErrorFactor = ALACD_ERR_POINTER;							/* Error Factor Set */

		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Parameter Check (Fs Check) ---------------------------------------- */
	if ( ( pInitConfigInfo->nSamplingRate < ALACD_FS_MIN ) ||
		 ( pInitConfigInfo->nSamplingRate > ALACD_FS_MAX ) ) {					/* Range:8000Hz <= Sampling Rate <= 96000Hz(or 192000Hz). */
		pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Parameter Check (Ch Check) ---------------------------------------- */
	if ( ( (ACMW_UINT32)pInitConfigInfo->nChannelNum == (ACMW_UINT32)0u ) ||
		 ( (ACMW_UINT32)pInitConfigInfo->nChannelNum > ALACD_INCH_NUM ) ) {		/* 3ch or more is not supported.. */
		pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* ---- Parameter Check (Bit Check) --------------------------------------- */
	switch ( (ACMW_UINT32)pInitConfigInfo->nBitsPerSample ) {
	case ALACD_INPUT_BITS_16:
		/* DO NOTHING */
		break;
	case ALACD_INPUT_BITS_20:
		/* DO NOTHING */
		break;
	case ALACD_INPUT_BITS_24:
		/* DO NOTHING */
		break;
	case ALACD_INPUT_BITS_32:
		/* DO NOTHING */
		break;
	default:
		pStaticArea->nErrorFactor = ALACD_ERR_PARAMETER;
		return ALACD_RESULT_NG;													/* MISRA-C:Two or more in function returns */
	} /* end switch */
	/* ------------------------------------------------------------------------ */

	pScratchArea = (alacd_ScratchArea *)pWorkMemInfo->pScratch;
	/*==========================================================================*/
	/* 	Initialization [2]														*/
	/*==========================================================================*/
	ComMemSet( &pScratchArea->stALAC_scratch, 0u, ALACD_MEM_SCRATCH_SIZE );		/* Scratch Initialization */

	pConfig = &pStaticArea->stALAC_static.mConfig;

	/* Set Config */
	pConfig->frameLength		= (ACMW_UINT32)kALACDefaultFrameSize;
	pConfig->compatibleVersion	= (ACMW_UINT8)ALACD_KUKI_COMP_VER;
	pConfig->bitDepth			= (ACMW_UINT8)pInitConfigInfo->nBitsPerSample;
	pConfig->pb					= (ACMW_UINT8)ALACD_KUKI_pb;
	pConfig->mb					= (ACMW_UINT8)ALACD_KUKI_mb;
	pConfig->kb					= (ACMW_UINT8)ALACD_KUKI_kb;
	pConfig->numChannels		= (ACMW_UINT8)pInitConfigInfo->nChannelNum;
	pConfig->maxRun				= (ACMW_UINT16)ALACD_KUKI_maxRun;
	pConfig->maxFrameBytes		= (ACMW_UINT32)ALACD_KUKI_maxFrameBytes;
	pConfig->avgBitRate			= (ACMW_UINT32)ALACD_KUKI_avgBitRate;
	pConfig->sampleRate			= (ACMW_UINT32)pInitConfigInfo->nSamplingRate;

	pStaticArea->stALAC_static.nOutBits = pInitConfigInfo->nOutBitsPerSample;
	/*==========================================================================*/

	pStaticArea->nStateSeq	 = (ACMW_UINT8)ALACD_INIT_SEQEND;					/* Init End */

	return ALACD_RESULT_OK;
}

/* End of File */
