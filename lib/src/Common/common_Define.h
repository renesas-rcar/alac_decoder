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

#ifndef COMM_DEFINE_H__
#define COMM_DEFINE_H__

/*--------------------------------------------------------------------------*/
/*	Define																	*/
/*--------------------------------------------------------------------------*/
/*==========================================================================*/
/*	MASK																	*/
/*==========================================================================*/
#define STDCODEC_COMM_MASK_00			(0x00u)
#define STDCODEC_COMM_MASK_01			(0x01u)
#define STDCODEC_COMM_MASK_02			(0x02u)
#define STDCODEC_COMM_MASK_03			(0x03u)
#define STDCODEC_COMM_MASK_04			(0x04u)
#define STDCODEC_COMM_MASK_05			(0x05u)
#define STDCODEC_COMM_MASK_06			(0x06u)
#define STDCODEC_COMM_MASK_07			(0x07u)
#define STDCODEC_COMM_MASK_08			(0x08u)
#define STDCODEC_COMM_MASK_09			(0x09u)

#define STDCODEC_COMM_MASK_0F			(0x0Fu)

#define STDCODEC_COMM_MASK_10			(0x10u)
#define STDCODEC_COMM_MASK_20			(0x20u)
#define STDCODEC_COMM_MASK_40			(0x40u)
#define STDCODEC_COMM_MASK_80			(0x80u)
#define STDCODEC_COMM_MASK_F0			(0xF0u)

#define STDCODEC_COMM_MASK_FF			(0xFFu)

/*==========================================================================*/
/*	OFFSET																	*/
/*==========================================================================*/
#define STDCODEC_COMM_OFFSET_00			(0u)								/*  +0H */
#define STDCODEC_COMM_OFFSET_01			(1u)								/*  +1H */
#define STDCODEC_COMM_OFFSET_02			(2u)								/*  +2H */
#define STDCODEC_COMM_OFFSET_03			(3u)								/*  +3H */
#define STDCODEC_COMM_OFFSET_04			(4u)								/*  +4H */
#define STDCODEC_COMM_OFFSET_05			(5u)								/*  +5H */
#define STDCODEC_COMM_OFFSET_06			(6u)								/*  +6H */
#define STDCODEC_COMM_OFFSET_07			(7u)								/*  +7H */
#define STDCODEC_COMM_OFFSET_08			(8u)								/*  +8H */

/*==========================================================================*/
/*	SHIFT																	*/
/*==========================================================================*/
#define STDCODEC_COMM_SHIFT_00			(0)									/*  0bit shift */
#define STDCODEC_COMM_SHIFT_01			(1)									/*  1bit shift */
#define STDCODEC_COMM_SHIFT_02			(2)									/*  2bit shift */
#define STDCODEC_COMM_SHIFT_03			(3)									/*  3bit shift */
#define STDCODEC_COMM_SHIFT_04			(4)									/*  4bit shift */
#define STDCODEC_COMM_SHIFT_05			(5)									/*  5bit shift */
#define STDCODEC_COMM_SHIFT_06			(6)									/*  6bit shift */
#define STDCODEC_COMM_SHIFT_07			(7)									/*  7bit shift */
#define STDCODEC_COMM_SHIFT_08			(8)									/*  8bit shift */
#define STDCODEC_COMM_SHIFT_09			(9)									/*  9bit shift */
#define STDCODEC_COMM_SHIFT_10			(10)								/* 10bit shift */
#define STDCODEC_COMM_SHIFT_11			(11)								/* 11bit shift */
#define STDCODEC_COMM_SHIFT_12			(12)								/* 12bit shift */
#define STDCODEC_COMM_SHIFT_13			(13)								/* 13bit shift */
#define STDCODEC_COMM_SHIFT_14			(14)								/* 14bit shift */
#define STDCODEC_COMM_SHIFT_15			(15)								/* 15bit shift */
#define STDCODEC_COMM_SHIFT_16			(16)								/* 16bit shift */
#define STDCODEC_COMM_SHIFT_17			(17)								/* 17bit shift */
#define STDCODEC_COMM_SHIFT_18			(18)								/* 18bit shift */
#define STDCODEC_COMM_SHIFT_19			(19)								/* 19bit shift */
#define STDCODEC_COMM_SHIFT_20			(20)								/* 20bit shift */
#define STDCODEC_COMM_SHIFT_21			(21)								/* 21bit shift */
#define STDCODEC_COMM_SHIFT_22			(22)								/* 22bit shift */
#define STDCODEC_COMM_SHIFT_23			(23)								/* 23bit shift */
#define STDCODEC_COMM_SHIFT_24			(24)								/* 24bit shift */

/*==========================================================================*/
/*	BOOL																	*/
/*==========================================================================*/
#if !defined ( FALSE )
	#define FALSE	0
	#define TRUE	(!FALSE)
#endif

/*==========================================================================*/
/*	Other Define 															*/
/*==========================================================================*/
#if !defined ( NULL )
    #define NULL  ( (void *) 0 )
#endif

#endif	/* COMM_DEFINE_H__ */
/* End of File */
