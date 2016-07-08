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
	File:		ALACAudioTypes.h
*/

/*------------------------------------------------------------------------------*/
/* ALAC Decode Software                                                         */
/* Copyright(C) 2014-2015 Renesas Electronics Corporation.                      */
/*------------------------------------------------------------------------------*/

#ifndef ALACAUDIOTYPES_H
#define ALACAUDIOTYPES_H

/* -------------------------------------------------------------------------- */
#include "alacd_Func_ReplaceName.h"

typedef signed char						int8_t;
typedef signed short					int16_t;
typedef signed int						int32_t;
typedef unsigned char					uint8_t;
typedef unsigned short					uint16_t;
typedef unsigned int					uint32_t;
typedef int								int_t;

#define LOC_MEMSIZE_MIN					((int32_t)(0))

#if !defined ( NULL )
    #define NULL  ( (void *) 0 )
#endif

#if !defined ( FALSE )
	#define FALSE	0
	#define TRUE	(!FALSE)
#endif

#ifdef __cplusplus
  #define inline	inline
#else
  #define inline	__inline
#endif
/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

#if 0
#if PRAGMA_STRUCT_ALIGN
    #pragma options align=mac68k
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(push, 2)
#elif PRAGMA_STRUCT_PACK
    #pragma pack(2)
#endif

#if defined(__ppc__)
#define TARGET_RT_BIG_ENDIAN 1
#elif defined(__ppc64__)
#define TARGET_RT_BIG_ENDIAN 1
#endif
#endif

#define kALAC_ParamError	(-50)						/* shortage */
#define kALAC_ParamError2	(-150)						/* damage */
#define kALAC_ParamError3	(-200)						/* warning */

#if 0
typedef uint32_t ALACChannelLayoutTag;

// These are the Channel Layout Tags used in the Channel Layout Info portion of the ALAC magic cookie
enum
{
    kALACChannelLayoutTag_Mono          = (100<<16) | 1,    // C
    kALACChannelLayoutTag_Stereo        = (101<<16) | 2,	// L R
    kALACChannelLayoutTag_MPEG_3_0_B    = (113<<16) | 3,	// C L R
    kALACChannelLayoutTag_MPEG_4_0_B    = (116<<16) | 4,	// C L R Cs
    kALACChannelLayoutTag_MPEG_5_0_D    = (120<<16) | 5,    // C L R Ls Rs
    kALACChannelLayoutTag_MPEG_5_1_D    = (124<<16) | 6,	// C L R Ls Rs LFE
    kALACChannelLayoutTag_AAC_6_1       = (142<<16) | 7,	// C L R Ls Rs Cs LFE
    kALACChannelLayoutTag_MPEG_7_1_B	= (127<<16) | 8     // C Lc Rc L R Ls Rs LFE    (doc: IS-13818-7 MPEG2-AAC)
};

// ALAC currently only utilizes these channels layouts. There is a one for one correspondance between a
// given number of channels and one of these layout tags
static const ALACChannelLayoutTag	ALACChannelLayoutTags[kALACMaxChannels] =
{
    kALACChannelLayoutTag_Mono,         // C
    kALACChannelLayoutTag_Stereo,		// L R
    kALACChannelLayoutTag_MPEG_3_0_B,	// C L R
    kALACChannelLayoutTag_MPEG_4_0_B,	// C L R Cs
    kALACChannelLayoutTag_MPEG_5_0_D,	// C L R Ls Rs
    kALACChannelLayoutTag_MPEG_5_1_D,	// C L R Ls Rs LFE
    kALACChannelLayoutTag_AAC_6_1,		// C L R Ls Rs Cs LFE
    kALACChannelLayoutTag_MPEG_7_1_B	// C Lc Rc L R Ls Rs LFE    (doc: IS-13818-7 MPEG2-AAC)
};

// AudioChannelLayout from CoreAudioTypes.h. We never need the AudioChannelDescription so we remove it
struct ALACAudioChannelLayout
{
    ALACChannelLayoutTag          mChannelLayoutTag;
    uint32_t                      mChannelBitmap;
    uint32_t                      mNumberChannelDescriptions;
};
typedef struct ALACAudioChannelLayout ALACAudioChannelLayout;
#endif
/* Lossless Definitions */

#define	kALACDefaultFrameSize		((uint32_t)(4096u))

// note: this struct is wrapped in an 'alac' atom in the sample description extension area
// note: in QT movies, it will be further wrapped in a 'wave' atom surrounded by 'frma' and 'term' atoms
typedef struct
{
	uint32_t				frameLength;
	uint8_t					compatibleVersion;
	uint8_t					bitDepth;							// max 32
	uint8_t					pb;									// 0 <= pb <= 255
	uint8_t					mb;
	uint8_t					kb;
	uint8_t					numChannels;
	uint16_t				maxRun;
	uint32_t				maxFrameBytes;
	uint32_t				avgBitRate;
	uint32_t				sampleRate;

} ALACSpecificConfig;

#if 0
// The AudioChannelLayout atom type is not exposed yet so define it here
enum
{
	AudioChannelLayoutAID = 'chan'
};
#endif
#if 0
#if PRAGMA_STRUCT_ALIGN
    #pragma options align=reset
#elif PRAGMA_STRUCT_PACKPUSH
    #pragma pack(pop)
#elif PRAGMA_STRUCT_PACK
    #pragma pack()
#endif
#endif

#define ALACD_MIXBUF_SIZE	(kALACDefaultFrameSize)

typedef struct {
	int32_t					aMixBufU[ALACD_MIXBUF_SIZE];
	int32_t					aMixBufV[ALACD_MIXBUF_SIZE];
	int32_t					aPredBuf[ALACD_MIXBUF_SIZE];
} ALACBuffer;


#ifdef __cplusplus
}
#endif

#endif	/* ALACAUDIOTYPES_H */
