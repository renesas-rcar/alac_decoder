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
/* Copyright(C) 2014-2017 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

/****************************************************************/
/*                      INCLUDE FILES                           */
/****************************************************************/
#include "alacd_Lib.h"
#include "alacd_ReplaceName.h"

/****************************************************************/
/*                      MACROS/DEFINES                          */
/****************************************************************/
/* Software IP Version */
#define ALACD_CUSTOMERID	((ACMW_UINT32)(0x00u))				/* Standard version */
#define ALACD_RELEASEID		((ACMW_UINT32)(0x00u))				/* Formal   version */
#define ALACD_MAJORID		((ACMW_UINT32)(0x02u))
#define ALACD_MINORID		((ACMW_UINT32)(0x00u))

#define	ALACD_IDSTRINGS_LENGTH	(160)

#ifdef	RCAR_H3_M3
	#define ALACD_ID_STRINGS	"ALAC Decode Software " \
								"Copyright(C) 2014 Renesas Electronics Corporation."
#else	/* Default */
	#define ALACD_ID_STRINGS	"IDStrings : ALAC Decoder Version 2.00"
#endif

const ACMW_UINT8 alacd_const_idstrings[ALACD_IDSTRINGS_LENGTH] = ALACD_ID_STRINGS;

/****************************************************************/
/*                      FUNCTIONS                               */
/****************************************************************/
/*------------------------------------------------------------------------------*/
/*			ALAC API GetVersion													*/
/*------------------------------------------------------------------------------*/
/*==============================================================================*/
/*
*
* FUNCTION NAME
* 		alacd_GetVersion
*
* ARGUMENT
* 		void
*
* RETURN VALUE
* 		ACMW_UINT32 versionCode
*
* OVERVIEW
* 		Version information acquisition processing
*
* DIVERSION ORIGIN
* 		Original.
*
*/
ACMW_UINT32 alacd_GetVersion( void )
{
	const ACMW_UINT32 RetVersion = (ACMW_UINT32)( ( (ACMW_UINT32)ALACD_CUSTOMERID << ALACD_SHIFT_24 ) |
												  ( (ACMW_UINT32)ALACD_RELEASEID  << ALACD_SHIFT_16 ) |
												  ( (ACMW_UINT32)ALACD_MAJORID    << ALACD_SHIFT_08 ) |
												  ( (ACMW_UINT32)ALACD_MINORID    << ALACD_SHIFT_00) );

	return RetVersion;
}

/* End of File */
