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
#define GETMEM_ARG_NUM					(2u)

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
/*			ALAC API GetMemorySize												*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		alacd_GetMemorySize
*
* ARGUMENT
* 		alacd_getMemorySizeConfigInfo* pGetMemorySizeConfigInfo
* 		alacd_getMemorySizeStatusInfo* pGetMemorySizeStatusInfo
*
* RETURN VALUE
* 		ACMW_INT32 errorCode
*
* OVERVIEW
* 		Memory requirement and size calculation processing
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_INT32 alacd_GetMemorySize( const alacd_getMemorySizeConfigInfo*	const pGetMemorySizeConfigInfo,
									  alacd_getMemorySizeStatusInfo*	const pGetMemorySizeStatusInfo )
{
	ACMW_BOOL	CheckErrorRet[GETMEM_ARG_NUM];

	/* ---- Argument Check (FATAL Check) -------------------------------------- */
	CheckErrorRet[ALACD_OFFSET_00] = ArgumentNullCheck( (const void * const)pGetMemorySizeConfigInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	CheckErrorRet[ALACD_OFFSET_01] = ArgumentNullCheck( (const void * const)pGetMemorySizeStatusInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	if ( ( CheckErrorRet[ALACD_OFFSET_00] == TRUE ) ||
		 ( CheckErrorRet[ALACD_OFFSET_01] == TRUE ) ) {							/* Error */
		return ALACD_RESULT_FATAL;												/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	/* Set size */
	pGetMemorySizeStatusInfo->nStaticSize		= sizeof(alacd_StaticArea);
	pGetMemorySizeStatusInfo->nScratchSize		= sizeof(alacd_ScratchArea);

	pGetMemorySizeStatusInfo->nInputBufferSize	= ALACD_IN_BUFF_MIN_SIZE;

	if ( (ACMW_UINT32)pGetMemorySizeConfigInfo->nOutBitsPerSample == (ACMW_UINT32)0u ) {
		pGetMemorySizeStatusInfo->nOutputBufferSize	= ALACD_OUT_BUFF_MIN_SIZE;
	} else {
		pGetMemorySizeStatusInfo->nOutputBufferSize	= ALACD_OUT_BUFF_MIN_SIZE_32;
	} /* end if */

	pGetMemorySizeStatusInfo->nStackSize		= ALACD_STACK_SIZE;

	return ALACD_RESULT_OK;
}

/* End of File */
