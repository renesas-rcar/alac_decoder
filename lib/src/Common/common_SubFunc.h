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

#ifndef COMM_SUBFUNC_H__
#define COMM_SUBFUNC_H__

#include "alacd_Lib.h"

#include "alacd_ReplaceName.h"

typedef signed long					COMM_ADR_SIZE;

#define ALIGNMENT_1BYTE				((ACMW_UINT32)(0x00000000u))
#define ALIGNMENT_2BYTE				((ACMW_UINT32)(0x00000001u))
#define ALIGNMENT_4BYTE				((ACMW_UINT32)(0x00000003u))
#define ALIGNMENT_8BYTE				((ACMW_UINT32)(0x00000007u))

#define ALIGNMENT_PTR				((ACMW_UINT32)(sizeof(COMM_ADR_SIZE) - 1))

/****************************************************************/
/*                      LOCAL TYPES                             */
/****************************************************************/
typedef int						COM_INT;

/*--------------------------------------------------------------------------*/
/*	API SubFunction Prototype												*/
/*--------------------------------------------------------------------------*/
ACMW_BOOL ArgumentNullCheck( const void* const pCheckArg, const ACMW_UINT32 Alignment_Byte );
void ComMemSet( void* const pTo,
				const ACMW_UINT8 nData,
				const ACMW_INT32 nSize );
#if 0
void ComMemCpy( void* const pTo,
				const void* const pFrom,
				const ACMW_INT32 nSize );
void ComMemMove( void* const pTo,
				const void* const pFrom,
				const ACMW_INT32 nSize );
COM_INT ComStrnCmp( const ACMW_UINT8* const paS1,
					const ACMW_UINT8* const paS2,
					const ACMW_INT32 nSize );
#endif
#endif	/* COMM_SUBFUNC_H__ */
/* End of File */
