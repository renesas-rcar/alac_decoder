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

/****************************************************************/
/*                      FUNCTIONS                               */
/****************************************************************/
/*------------------------------------------------------------------------------*/
/*			ALAC API GetErrorFactor												*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		alacd_GetErrorFactor
*
* ARGUMENT
* 		alacd_workMemoryInfo* pWorkMemInfo
*
* RETURN VALUE
* 		ACMW_UINT32 errorFactor
*
* OVERVIEW
* 		Error factor information acquisition processing
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_UINT32 alacd_GetErrorFactor( const alacd_workMemoryInfo* const pWorkMemInfo )
{
	ACMW_BOOL	CheckErrorRet;
	alacd_StaticArea*	pStaticArea;

	const ACMW_INT32	RetExceptFactFatal = ALACD_RESULT_FATAL;

	/* ---- Argument Check (FATAL Check) -------------------------------------- */
	CheckErrorRet = ArgumentNullCheck( (const void * const)pWorkMemInfo, ALIGNMENT_1BYTE );	/* [2015.09.04] -> Alignment do not check for structure pointer */
	if ( CheckErrorRet == TRUE ) {												/* Error */
		return (ACMW_UINT32)RetExceptFactFatal;									/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */

	CheckErrorRet = ArgumentNullCheck( (const void * const)pWorkMemInfo->pStatic, ALIGNMENT_PTR );
	if ( CheckErrorRet == TRUE ) {												/* Error */
		return (ACMW_UINT32)RetExceptFactFatal;									/* MISRA-C:Two or more in function returns */
	} else {
		/* DO NOTHING */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	pStaticArea = (alacd_StaticArea *)pWorkMemInfo->pStatic;

	/* ---- State Check ------------------------------------------------------- */
	if ( ( (LOC_INT)pStaticArea->nStateSeq != ALACD_INIT_SEQEND   ) &&			/* Sequence Error */
	     ( (LOC_INT)pStaticArea->nStateSeq != ALACD_INIT_SEQSTART ) ) {
		pStaticArea->nErrorFactor = ALACD_ERR_SEQUENCE;
	} else {
		/* DO NOTHING */														/* Other Error Factor Set */
	} /* end if */
	/* ------------------------------------------------------------------------ */

	return pStaticArea->nErrorFactor;
}

/* End of File */
