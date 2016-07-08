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

#ifndef ALACD_RENAME_H__
#define ALACD_RENAME_H__

#include "common_Define.h"


#define ArgumentNullCheck           alacd_ArgumentNullCheck
#define ComMemSet                   alacd_ComMemSet

/*--------------------------------------------------------------------------*/
/*	Define																	*/
/*--------------------------------------------------------------------------*/
/*==========================================================================*/
/*	MASK																	*/
/*==========================================================================*/
#define ALACD_MASK_00					(STDCODEC_COMM_MASK_00)
#define ALACD_MASK_01					(STDCODEC_COMM_MASK_01)
#define ALACD_MASK_02					(STDCODEC_COMM_MASK_02)
#define ALACD_MASK_03					(STDCODEC_COMM_MASK_03)
#define ALACD_MASK_04					(STDCODEC_COMM_MASK_04)
#define ALACD_MASK_05					(STDCODEC_COMM_MASK_05)
#define ALACD_MASK_06					(STDCODEC_COMM_MASK_06)
#define ALACD_MASK_07					(STDCODEC_COMM_MASK_07)
#define ALACD_MASK_08					(STDCODEC_COMM_MASK_08)
#define ALACD_MASK_09					(STDCODEC_COMM_MASK_09)

#define ALACD_MASK_0F					(STDCODEC_COMM_MASK_0F)

#define ALACD_MASK_10					(STDCODEC_COMM_MASK_10)
#define ALACD_MASK_20					(STDCODEC_COMM_MASK_20)
#define ALACD_MASK_40					(STDCODEC_COMM_MASK_40)
#define ALACD_MASK_80					(STDCODEC_COMM_MASK_80)
#define ALACD_MASK_F0					(STDCODEC_COMM_MASK_F0)

#define ALACD_MASK_FF					(STDCODEC_COMM_MASK_FF)

/*==========================================================================*/
/*	OFFSET																	*/
/*==========================================================================*/
#define ALACD_OFFSET_00					(STDCODEC_COMM_OFFSET_00)			/*  +0H */
#define ALACD_OFFSET_01					(STDCODEC_COMM_OFFSET_01)			/*  +1H */
#define ALACD_OFFSET_02					(STDCODEC_COMM_OFFSET_02)			/*  +2H */
#define ALACD_OFFSET_03					(STDCODEC_COMM_OFFSET_03)			/*  +3H */
#define ALACD_OFFSET_04					(STDCODEC_COMM_OFFSET_04)			/*  +4H */
#define ALACD_OFFSET_05					(STDCODEC_COMM_OFFSET_05)			/*  +5H */

/*==========================================================================*/
/*	SHIFT																	*/
/*==========================================================================*/
#define ALACD_SHIFT_00					(STDCODEC_COMM_SHIFT_00)			/*  0bit shift */
#define ALACD_SHIFT_01					(STDCODEC_COMM_SHIFT_01)			/*  1bit shift */
#define ALACD_SHIFT_02					(STDCODEC_COMM_SHIFT_02)			/*  2bit shift */
#define ALACD_SHIFT_03					(STDCODEC_COMM_SHIFT_03)			/*  3bit shift */
#define ALACD_SHIFT_04					(STDCODEC_COMM_SHIFT_04)			/*  4bit shift */
#define ALACD_SHIFT_05					(STDCODEC_COMM_SHIFT_05)			/*  5bit shift */
#define ALACD_SHIFT_06					(STDCODEC_COMM_SHIFT_06)			/*  6bit shift */
#define ALACD_SHIFT_07					(STDCODEC_COMM_SHIFT_07)			/*  7bit shift */
#define ALACD_SHIFT_08					(STDCODEC_COMM_SHIFT_08)			/*  8bit shift */
#define ALACD_SHIFT_09					(STDCODEC_COMM_SHIFT_09)			/*  9bit shift */
#define ALACD_SHIFT_10					(STDCODEC_COMM_SHIFT_10)			/* 10bit shift */
#define ALACD_SHIFT_11					(STDCODEC_COMM_SHIFT_11)			/* 11bit shift */
#define ALACD_SHIFT_12					(STDCODEC_COMM_SHIFT_12)			/* 12bit shift */
#define ALACD_SHIFT_13					(STDCODEC_COMM_SHIFT_13)			/* 13bit shift */
#define ALACD_SHIFT_14					(STDCODEC_COMM_SHIFT_14)			/* 14bit shift */
#define ALACD_SHIFT_15					(STDCODEC_COMM_SHIFT_15)			/* 15bit shift */
#define ALACD_SHIFT_16					(STDCODEC_COMM_SHIFT_16)			/* 16bit shift */
#define ALACD_SHIFT_17					(STDCODEC_COMM_SHIFT_17)			/* 17bit shift */
#define ALACD_SHIFT_18					(STDCODEC_COMM_SHIFT_18)			/* 18bit shift */
#define ALACD_SHIFT_19					(STDCODEC_COMM_SHIFT_19)			/* 19bit shift */
#define ALACD_SHIFT_20					(STDCODEC_COMM_SHIFT_20)			/* 20bit shift */
#define ALACD_SHIFT_21					(STDCODEC_COMM_SHIFT_21)			/* 21bit shift */
#define ALACD_SHIFT_22					(STDCODEC_COMM_SHIFT_22)			/* 22bit shift */
#define ALACD_SHIFT_23					(STDCODEC_COMM_SHIFT_23)			/* 23bit shift */
#define ALACD_SHIFT_24					(STDCODEC_COMM_SHIFT_24)			/* 24bit shift */

#endif	/* ALACD_RENAME_H__ */
/* End of File */
