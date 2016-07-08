/*
 * ALAC Decoder
 *
 * This program has modified by Renesas Electronics Corporation.
 * The original source code is open source software under the Apache License.
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

/*
 * Copyright (c) 2011 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

/*
	File:		dplib.h
	
	Contains:	Dynamic Predictor routines

	Copyright:	Copyright (C) 2001-2011 Apple, Inc.
*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2016 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#ifndef DPLIB_H__
#define DPLIB_H__

#include "ALACAudioTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

// defines

#define DENSHIFT_MAX  15
#define DENSHIFT_DEFAULT 9
#define AINIT 38
#define BINIT (-29)
#define CINIT (-2)
#define NUMCOEPAIRS 16

// prototypes

// NOTE: these routines read at least "numactive" samples so the i/o buffers must be at least that big

void pc_block( int32_t * in, int32_t * pc, int32_t num, int16_t * coefs, int32_t numactive, uint32_t chanbits, uint32_t denshift );
void unpc_block( int32_t * pc1, int32_t * out, int32_t num, int16_t * coefs, int32_t numactive, uint32_t chanbits, uint32_t denshift );

#ifdef __cplusplus
}
#endif

#endif	/* DPLIB_H__ */
