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

/*=============================================================================
    File:		ALACBitUtilities.h
	
	$NoKeywords: $
=============================================================================*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2016 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#ifndef ALACBITUTILITIES_H__
#define ALACBITUTILITIES_H__

#include "ALACAudioTypes.h"

#ifndef MIN
#define MIN(x, y) 			( (x)<(y) ?(x) :(y) )
#endif //MIN
#ifndef MAX
#define MAX(x, y) 			( (x)>(y) ?(x): (y) )
#endif //MAX

#ifndef nil
#define nil NULL
#endif

#define RequireAction(condition, action)			if (!(condition)) { action }
#define RequireActionSilent(condition, action)			if (!(condition)) { action }
#define RequireNoErr(condition, action)			if ((condition)) { action }

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    ALAC_noErr = 0
};
    

typedef enum
{
    
    ID_SCE = 0,						/* Single Channel Element   */
    ID_CPE = 1,						/* Channel Pair Element     */
    ID_CCE = 2,						/* Coupling Channel Element */
    ID_LFE = 3,						/* LFE Channel Element      */
    ID_DSE = 4,						/* not yet supported        */
    ID_PCE = 5,
    ID_FIL = 6,
    ID_END = 7
} ELEMENT_TYPE;

// types
typedef struct
{
	uint8_t *		cur;
	uint8_t *		end;
	uint32_t		bitIndex;
	uint32_t		byteSize;
	
} BitBuffer;

/*
	BitBuffer routines
	- these routines take a fixed size buffer and read/write to it
	- bounds checking must be done by the client
*/
void	BitBufferInit( BitBuffer * bits, uint8_t * buffer, uint32_t byteSize );
uint32_t	BitBufferRead( BitBuffer * bits, uint8_t numBits );   // note: cannot read more than 16 bits at a time
uint8_t	BitBufferReadSmall( BitBuffer * bits, uint8_t numBits );
uint8_t	BitBufferReadOne( BitBuffer * bits );
void	BitBufferByteAlign( BitBuffer * bits, int32_t addZeros );
void	BitBufferAdvance( BitBuffer * bits, uint32_t numBits );
#if 0
void	BitBufferReset( BitBuffer * bits);
#endif

#ifdef __cplusplus
}
#endif

#endif	/* ALACBITUTILITIES_H__ */
