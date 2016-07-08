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

#ifndef ALACD_LIB_H
#define ALACD_LIB_H

/*--------------------------------------------------------------------------*/
/*	Define																	*/
/*--------------------------------------------------------------------------*/
#ifndef ACMW_COMM_STDTYPES_H
#define ACMW_COMM_STDTYPES_H

/*==========================================================================*/
/*	Define Type for Software IP												*/
/*==========================================================================*/
typedef signed char						ACMW_INT8;
typedef signed short					ACMW_INT16;
typedef signed int						ACMW_INT32;
typedef unsigned char					ACMW_UINT8;
typedef unsigned short					ACMW_UINT16;
typedef unsigned int					ACMW_UINT32;
typedef signed short					ACMW_BOOL;

#endif	/* ACMW_COMM_STDTYPES_H */

/*==========================================================================*/
/*	Define Error Code														*/
/*==========================================================================*/
#define	ALACD_RESULT_OK					((ACMW_INT32)(0x00000000))
#define	ALACD_RESULT_NG					((ACMW_INT32)(0x00000001))
#define	ALACD_RESULT_WARNING			((ACMW_INT32)(0x00000002))
#define	ALACD_RESULT_FATAL				((ACMW_INT32)(0x00000003))

/*==========================================================================*/
/*	Define Error Factor														*/
/*==========================================================================*/
#define	ALACD_ERR_NONE					((ACMW_UINT32)(0x00000000u))
#define	ALACD_ERR_POINTER				((ACMW_UINT32)(0x00000010u))
#define	ALACD_ERR_PARAMETER				((ACMW_UINT32)(0x00000020u))
#define	ALACD_ERR_SEQUENCE				((ACMW_UINT32)(0x00000040u))
#define	ALACD_ERR_SHORT_INPUT_DATA		((ACMW_UINT32)(0x00000100u))
#define	ALACD_ERR_STREAM				((ACMW_UINT32)(0x00001000u))
#define	ALACD_ERR_DECODE				((ACMW_UINT32)(0x01000000u))

/*==========================================================================*/
/*	Standard Define 														*/
/*==========================================================================*/
#define	ALACD_KUKI_COMP_VER				(0u)
#define	ALACD_KUKI_pb					(40u)
#define	ALACD_KUKI_mb					(10u)
#define	ALACD_KUKI_kb					(14u)
#define	ALACD_KUKI_maxRun				(255u)
#define	ALACD_KUKI_maxFrameBytes		((ACMW_UINT32)(0u))					/* 0:unknown */
#define	ALACD_KUKI_avgBitRate			((ACMW_UINT32)(0u))					/* 0:unknown */

#define ALACD_DEF_FRAME_LEN				((ACMW_UINT32)(4096u))

/*==========================================================================*/
/*	Specification Define 													*/
/*==========================================================================*/
#define ALACD_HEAD_LENGTH				((ACMW_UINT32)(8u))

#define ALACD_INCH_NUM					((ACMW_UINT32)(2u))
#define ALACD_OUTCH_NUM					((ACMW_UINT32)(2u))

#define ALACD_BYTE_PER_SAMP				((ACMW_UINT32)(2u))
#define ALACD_BYTE_PER_SAMP_32			((ACMW_UINT32)(4u))

/* Max => 1ch * 16bit / 8bit * 4096[Sample] */
#define ALACD_OUT_BUFF_MIN_SIZE			(ALACD_BYTE_PER_SAMP * ALACD_DEF_FRAME_LEN)
/* Max => 1ch * 32bit / 8bit * 4096[Sample] */
#define ALACD_OUT_BUFF_MIN_SIZE_32		(ALACD_BYTE_PER_SAMP_32 * ALACD_DEF_FRAME_LEN)

/* Max => 2ch * 32bit / 8bit * 4096[Sample] + 8 */
#define ALACD_IN_BUFF_MIN_SIZE			((ALACD_OUT_BUFF_MIN_SIZE_32 * ALACD_INCH_NUM) + ALACD_HEAD_LENGTH)

#define ALACD_STACK_SIZE				((ACMW_UINT32)(4096u))

/*--------------------------------------------------------------------------*/

/*==========================================================================*/
/*	Other Define 															*/
/*==========================================================================*/
#define ALACD_INIT_SEQEND				(1)
#define ALACD_INIT_SEQSTART				(2)

#define ALACD_FS192000HZ				((ACMW_UINT32)(192000u))
#define ALACD_FS_96000HZ				((ACMW_UINT32)( 96000u))
#define ALACD_FS_88200HZ				((ACMW_UINT32)( 88200u))
#define ALACD_FS_64000HZ				((ACMW_UINT32)( 64000u))
#define ALACD_FS_48000HZ				((ACMW_UINT32)( 48000u))
#define ALACD_FS_44100HZ				((ACMW_UINT32)( 44100u))
#define ALACD_FS_32000HZ				((ACMW_UINT32)( 32000u))
#define ALACD_FS_24000HZ				((ACMW_UINT32)( 24000u))
#define ALACD_FS_22050HZ				((ACMW_UINT32)( 22050u))
#define ALACD_FS_16000HZ				((ACMW_UINT32)( 16000u))
#define ALACD_FS_12000HZ				((ACMW_UINT32)( 12000u))
#define ALACD_FS_11025HZ				((ACMW_UINT32)( 11025u))
#define ALACD_FS_08000HZ				((ACMW_UINT32)(  8000u))

#define ALACD_FS_MIN					ALACD_FS_08000HZ

#ifdef	RCAR_H3_M3
	#define ALACD_INPUT_FSRANGE_192
#endif

#ifdef	ALACD_INPUT_FSRANGE_192
	#define ALACD_FS_MAX					ALACD_FS192000HZ
#else
	#define ALACD_FS_MAX					ALACD_FS_96000HZ
#endif

#define ALACD_INPUT_BITS_16				((ACMW_UINT32)(16u))
#define ALACD_INPUT_BITS_20				((ACMW_UINT32)(20u))
#define ALACD_INPUT_BITS_24				((ACMW_UINT32)(24u))
#define ALACD_INPUT_BITS_32				((ACMW_UINT32)(32u))

/***************************************************************************/

/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*	API Structure															*/
/*--------------------------------------------------------------------------*/
/*==========================================================================*/
/*	[1] Define Struct alacd_getMemorySizeConfigInfo							*/
/*==========================================================================*/
/* [Description]
 *   Structure that specifies condition when size is acquired memory requirement
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT16		nOutBitsPerSample;
	ACMW_UINT16		nInputChannel;
	ACMW_UINT16		nOutputChannel;
	ACMW_UINT16		Reserved;
} alacd_getMemorySizeConfigInfo;

/*==========================================================================*/
/*	[2] Define Struct alacd_getMemorySizeStatusInfo							*/
/*==========================================================================*/
/* [Description]
 *   Structure that stores memory requirement and size calculation result
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT32		nStaticSize;
	ACMW_UINT32		nScratchSize;
	ACMW_UINT32		nInputBufferSize;
	ACMW_UINT32		nOutputBufferSize;
	ACMW_UINT32		nStackSize;
} alacd_getMemorySizeStatusInfo;

/*==========================================================================*/
/*	[3] Define Struct alacd_workMemoryInfo									*/
/*==========================================================================*/
/* [Description]
 *   Structure that specifies address information on work memory
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	void*			pStatic;
	void*			pScratch;
} alacd_workMemoryInfo;

/*==========================================================================*/
/*	[4] Define Struct alacd_initConfigInfo									*/
/*==========================================================================*/
/* [Description]
 *   Structure that specifies decode condition when initializing it
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT32		nSamplingRate;
	ACMW_UINT16		nChannelNum;
	ACMW_UINT16		nBitsPerSample;
	ACMW_UINT16		nOutBitsPerSample;
	ACMW_UINT16		nInputChannel;
	ACMW_UINT16		nOutputChannel;
	ACMW_UINT16		Reserved;
} alacd_initConfigInfo;

/*==========================================================================*/
/*	[5] Define Struct alacd_decConfigInfo									*/
/*==========================================================================*/
/* [Description]
 *   Structure that specifies processing condition
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT32		Reserved;
} alacd_decConfigInfo;

/*==========================================================================*/
/*	[6] Define Struct alacd_decStatusInfo									*/
/*==========================================================================*/
/* [Description]
 *   Structure that stores decoder processing result
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT16		nSamplesPerFrame;
	ACMW_UINT16		nChannelNum;
	ACMW_UINT16		nChannelInfo;
	ACMW_UINT16		Reserved;
} alacd_decStatusInfo;

/*==========================================================================*/
/*	[7] Define Struct alacd_ioBufferConfigInfo								*/
/*==========================================================================*/
/* [Description]
 *   Structure that specifies parameter of input buffer
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT8*		pInBuffStart;
	ACMW_UINT32		nInBuffSetDataSize;
	void**			pOutBuffStart;
	ACMW_UINT32		nOutBuffSize;
} alacd_ioBufferConfigInfo;

/*==========================================================================*/
/*	[8] Define Struct alacd_ioBufferStatusInfo								*/
/*==========================================================================*/
/* [Description]
 *   Structure that stores buffer memory information result after decode
 *
 * [Note]
 *   User allocate
 *==========================================================================*/
typedef struct {
	ACMW_UINT8*		pInBuffLast;
	ACMW_UINT32		nInBuffUsedDataSize;
	void**			pOutBuffLast;
	ACMW_UINT32		nOutBuffUsedDataSize;
} alacd_ioBufferStatusInfo;
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*	API Function Prototype													*/
/*--------------------------------------------------------------------------*/
extern ACMW_INT32 alacd_GetMemorySize( const alacd_getMemorySizeConfigInfo* const pGetMemorySizeConfigInfo,
											 alacd_getMemorySizeStatusInfo*	const pGetMemorySizeStatusInfo );

extern ACMW_INT32 alacd_Init( const alacd_workMemoryInfo* const pWorkMemInfo,
							  const alacd_initConfigInfo* const pInitConfigInfo );

extern ACMW_INT32 alacd_Decode( const alacd_workMemoryInfo*		const	pWorkMemInfo,
								const alacd_decConfigInfo*		const	pDecConfigInfo,
								const alacd_ioBufferConfigInfo*	const	pBuffConfigInfo,
									  alacd_decStatusInfo*		const	pDecStatusInfo,
									  alacd_ioBufferStatusInfo*	const	pBuffStatusInfo );

extern ACMW_UINT32 alacd_GetErrorFactor( const alacd_workMemoryInfo* const pWorkMemInfo );

extern ACMW_UINT32 alacd_GetVersion( void );
/*--------------------------------------------------------------------------*/

#endif	/* ALACD_LIB_H */
/* End of File */
