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
#include "common_SubFunc.h"

/****************************************************************/
/*                      MACROS/DEFINES                          */
/****************************************************************/
#define GENERAL_MEMSIZE_MIN			((ACMW_INT32)(0))

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
/*			API Sub Function													*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		ArgumentNullCheck
*
* ARGUMENT
* 		void* pCheckArg : Address
*
* RETURN VALUE
* 		ACMW_BOOL RetError
*			TRUE  : Error
*			FALSE : Non Error
*
* OVERVIEW
* 		Argument Check
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_BOOL ArgumentNullCheck( const void* const pCheckArg, const ACMW_UINT32 Alignment_Byte )
{
	ACMW_BOOL RetError = FALSE;													/* Non Error */

	if ( pCheckArg == NULL ) {													/* NULL Check */
		RetError = TRUE;														/* Error */
	} else if ( ((ACMW_UINT32)pCheckArg & Alignment_Byte) != (ACMW_UINT32)0u ) {/* [2013.07.25] Alignment Check */
		RetError = TRUE;														/* Error */
	} else {
		/* DO NOTHING */
	} /* end if */

	return RetError;
}

/*------------------------------------------------------------------------------*/
/*			 memory Function													*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		ComMemSet
*
* ARGUMENT
* 		void* pTo
*		ACMW_UINT8 nData
*		ACMW_INT32 nSize
*
* RETURN VALUE
*		void
*
* OVERVIEW
* 		Memory Set
*
* DIVERSION ORIGIN
* 		Original.
*
*/
void ComMemSet( void* const pTo,
				const ACMW_UINT8 nData,
				const ACMW_INT32 nSize )
{
	ACMW_UINT8* const ptrDest = (ACMW_UINT8* const)pTo;

	if ( ( pTo != NULL ) && ( nSize > GENERAL_MEMSIZE_MIN ) ) {
		COM_INT	index;															/* for counter */
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
#if 0
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		ComMemCpy
*
* ARGUMENT
* 		void* pTo
*		void* pFrom
*		ACMW_INT32 nSize
*
* RETURN VALUE
*		void
*
* OVERVIEW
* 		Memory Copy
*
* DIVERSION ORIGIN
* 		Original.
*
*/
void ComMemCpy( void* const pTo,
				const void* const pFrom,
				const ACMW_INT32 nSize )
{
	ACMW_UINT8* const ptrDest = (ACMW_UINT8* const)pTo;
	const ACMW_UINT8* const ptrSrc  = (const ACMW_UINT8* const)pFrom;

	if ( ( pTo != NULL ) && ( pFrom != NULL ) &&
		 ( nSize > GENERAL_MEMSIZE_MIN ) ) {
		COM_INT	index;															/* for counter */
		/* The address of the setting destination isn't NULL and the established size is normal. */
		for ( index = 0; index < nSize; index++ ) {
			ptrDest[index] = ptrSrc[index];
		} /* end for */
	} else {
		/* The address of the setting destination is NULL or the established size is abnormal. */
		/* DO NOTHING */
	} /* end if */

	return;
}

/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		ComMemMove
*
* ARGUMENT
* 		void* pTo
*		void* pFrom
*		ACMW_INT32 nSize
*
* RETURN VALUE
*		void
*
* OVERVIEW
* 		Memory Move
*
* DIVERSION ORIGIN
* 		Original.
*
*/
void ComMemMove( void* const pTo,
				 const void* const pFrom,
				 const ACMW_INT32 nSize )
{
	ACMW_UINT8* const ptrDest = (ACMW_UINT8* const)pTo;
	const ACMW_UINT8* const ptrSrc  = (const ACMW_UINT8* const)pFrom;

	if ( ( pTo != NULL ) && ( pFrom != NULL ) &&
		 ( nSize > GENERAL_MEMSIZE_MIN ) ) {
		COM_INT	index;															/* for counter */
		const ACMW_UINT32	toAdr	= (ACMW_UINT32)pTo;
		const ACMW_UINT32	fromAdr	= (ACMW_UINT32)pFrom;
		/* The address of the setting destination isn't NULL and the established size is normal. */
		if ( ( toAdr > fromAdr ) &&
			 ( toAdr < (fromAdr + (ACMW_UINT32)nSize) ) ) {						/* It copies from back. */
			for ( index = (nSize-(ACMW_INT32)1); index >= 0 ; index-- ) {
				ptrDest[index] = ptrSrc[index];
			} /* end for */
		} else {
			for ( index = 0; index < nSize; index++ ) {
				ptrDest[index] = ptrSrc[index];
			} /* end for */
		} /* end if */
	} else {
		/* The address of the setting destination is NULL or the established size is abnormal. */
		/* DO NOTHING */
	} /* end if */

	return;
}

/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		ComStrnCmp
*
* ARGUMENT
* 		ACMW_UINT8* paS1
*		ACMW_UINT8* paS2
*		ACMW_INT32  nSize
*
* RETURN VALUE
* 		COM_INT	RetCmpResult
*			0 : *paS1 = *paS2
*			+ : *paS1 > *paS2
*			- : *paS1 < *paS2
*
* OVERVIEW
* 		Character string comparison.
*
* DIVERSION ORIGIN
* 		Original.
*
*/
COM_INT ComStrnCmp( const ACMW_UINT8* const paS1,
					const ACMW_UINT8* const paS2,
					const ACMW_INT32 nSize )
{
	COM_INT	RetCmpResult = 0;

	if ( ( paS1 != NULL ) && ( paS2 != NULL ) &&
		 ( nSize > GENERAL_MEMSIZE_MIN ) ) {
		COM_INT	index;															/* for counter */
		/* The address of the setting destination isn't NULL and the established size is normal. */
		for ( index = 0; index < nSize; index++ ) {
			if ( (COM_INT)paS1[index] != (COM_INT)paS2[index] ) {
				RetCmpResult = (COM_INT)((COM_INT)paS1[index] - (COM_INT)paS2[index]);
				break;
			} else {
				/* DO NOTHING */
			} /* end if */
		} /* end for */
	} else {
		/* The address of the setting destination is NULL or the established size is abnormal. */
		/* DO NOTHING */
	} /* end if */

	return RetCmpResult;
}
#endif
/* End of File */
