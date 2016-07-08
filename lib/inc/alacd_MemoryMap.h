/*
 * ALAC Decoder
 *
 * This program has modified by Renesas Electronics Corporation.
 * This file is subject to the terms and conditions of the APPLE PUBLIC SOURCE LICENSE.
 * See the file "APPLE_LICENSE.txt" in the main directory of this archive for more details.
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

#ifndef ALACD_MEMMAP_H__
#define ALACD_MEMMAP_H__

#include "alacd_IfPackage.h"

#define ALACD_MEM_STATIC_SIZE			sizeof(alacdec_struct_static)
#define ALACD_MEM_SCRATCH_SIZE			sizeof(alacdec_struct_scratch)

/*==========================================================================*/
/*	Static Struct															*/
/*==========================================================================*/
typedef struct {
	ACMW_UINT32				nErrorFactor;									/* Error Factor */
	ACMW_UINT8				nStateSeq;
	alacdec_struct_static	stALAC_static;
} alacd_StaticArea;
/*==========================================================================*/

/*==========================================================================*/
/*	Scratch Struct															*/
/*==========================================================================*/
typedef struct {
	alacdec_struct_scratch	stALAC_scratch;
} alacd_ScratchArea;
/*==========================================================================*/

#endif	/* ALACD_MEMMAP_H__ */
/* End of File */
