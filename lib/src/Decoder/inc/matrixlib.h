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
	File:		matrixlib.h
	
	Contains:	ALAC mixing/matrixing routines to/from 32-bit predictor buffers.

	Copyright:	Copyright (C) 2004 to 2011 Apple, Inc.
*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2016 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#ifndef MATRIXLIB_H__
#define MATRIXLIB_H__

#include "ALACAudioTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

// 16-bit routines
void	unmix16( int32_t * u, int32_t * v, int16_t * out, uint32_t stride, int32_t numSamples, int32_t mixbits, int32_t mixres );

// 20-bit routines
void	unmix20( int32_t * u, int32_t * v, uint8_t * out, uint32_t stride, int32_t numSamples, int32_t mixbits, int32_t mixres );

// 24-bit routines
// - 24-bit data sometimes compresses better by shifting off the bottom byte so these routines deal with
//	 the specified "unused lower bytes" in the combined "shift" buffer
void	unmix24( int32_t * u, int32_t * v, uint8_t * out, uint32_t stride, int32_t numSamples,
				 int32_t mixbits, int32_t mixres, uint16_t * shiftUV, int32_t bytesShifted );

// 32-bit routines
// - note that these really expect the internal data width to be < 32-bit but the arrays are 32-bit
// - otherwise, the calculations might overflow into the 33rd bit and be lost
// - therefore, these routines deal with the specified "unused lower" bytes in the combined "shift" buffer
void	unmix32( int32_t * u, int32_t * v, int16_t * out, uint32_t stride, int32_t numSamples,
				 int32_t mixbits, int32_t mixres, uint16_t * shiftUV, int32_t bytesShifted );

// 20/24/32-bit <-> 32-bit helper routines (not really matrixing but convenient to put here)

void	copyPredictorTo24( int32_t * in, uint8_t * out, uint32_t stride, int32_t numSamples );
void	copyPredictorTo24Shift( int32_t * in, uint16_t * shift, uint8_t * out, uint32_t stride, int32_t numSamples, int32_t bytesShifted );
void	copyPredictorTo20( int32_t * in, uint8_t * out, uint32_t stride, int32_t numSamples );

void	copyPredictorTo32( int32_t * in, int16_t * out, uint32_t stride, int32_t numSamples );
void	copyPredictorTo32Shift( int32_t * in, uint16_t * shift, int16_t * out, uint32_t stride, int32_t numSamples, int32_t bytesShifted );

/*------------------------------------------------------------------------------*/
/*	32bit Output																*/
/*------------------------------------------------------------------------------*/

// 16-bit routines
void	unmix16_32( int32_t * u, int32_t * v, int32_t * out, uint32_t stride, int32_t numSamples, int32_t mixbits, int32_t mixres );

// 20-bit routines
void	unmix20_32( int32_t * u, int32_t * v, uint8_t * out, uint32_t stride, int32_t numSamples, int32_t mixbits, int32_t mixres );

// 24-bit routines
// - 24-bit data sometimes compresses better by shifting off the bottom byte so these routines deal with
//	 the specified "unused lower bytes" in the combined "shift" buffer
void	unmix24_32( int32_t * u, int32_t * v, uint8_t * out, uint32_t stride, int32_t numSamples,
				 int32_t mixbits, int32_t mixres, uint16_t * shiftUV, int32_t bytesShifted );

// 32-bit routines
// - note that these really expect the internal data width to be < 32-bit but the arrays are 32-bit
// - otherwise, the calculations might overflow into the 33rd bit and be lost
// - therefore, these routines deal with the specified "unused lower" bytes in the combined "shift" buffer
void	unmix32_32( int32_t * u, int32_t * v, int32_t * out, uint32_t stride, int32_t numSamples,
				 int32_t mixbits, int32_t mixres, uint16_t * shiftUV, int32_t bytesShifted );

// 20/24/32-bit <-> 32-bit helper routines (not really matrixing but convenient to put here)

void	copyPredictorTo24_32( int32_t * in, uint8_t * out, uint32_t stride, int32_t numSamples );
void	copyPredictorTo24Shift_32( int32_t * in, uint16_t * shift, uint8_t * out, uint32_t stride, int32_t numSamples, int32_t bytesShifted );
void	copyPredictorTo20_32( int32_t * in, uint8_t * out, uint32_t stride, int32_t numSamples );

void	copyPredictorTo32_32( int32_t * in, int32_t * out, uint32_t stride, int32_t numSamples );
void	copyPredictorTo32Shift_32( int32_t * in, uint16_t * shift, int32_t * out, uint32_t stride, int32_t numSamples, int32_t bytesShifted );

#ifdef __cplusplus
}
#endif

#endif	/* MATRIXLIB_H__ */
