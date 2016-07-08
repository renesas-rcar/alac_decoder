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

#ifndef ALACD_FUNC_RENAME_H__
#define ALACD_FUNC_RENAME_H__


#ifdef AUTOPROFILE_C
	#include "AutoProfile_c.h"
#else	/* It cannot be used. */
	#ifdef NON_PROFILE_FUNCTION
	#else
		#define Profiler_init(pn)
		#define Profiler_close()
		#define FUNCTION_PROFILE(fp)
		#define FUNCTION_PROFILE_START(fp,id,ptn)
		#define FUNCTION_PROFILE_STOP(fp)
		#define FUNCTION_PROFILE_INC()
		#define NON_PROFILE_FUNCTION
	#endif
#endif

#define DecoderMain												alacd_DecoderMain
#define ALACDecoder_Decode                                      alacd_ALACDecoder_Decode
#define ALACDecoder_DataStreamElement                           alacd_ALACDecoder_DataStreamElement
#define BitBufferAdvance                                        alacd_BitBufferAdvance
#define BitBufferByteAlign                                      alacd_BitBufferByteAlign
#define BitBufferReadOne                                        alacd_BitBufferReadOne
#define BitBufferReadSmall                                      alacd_BitBufferReadSmall
#define ALACDecoder_FillElement                                 alacd_ALACDecoder_FillElement
#define BitBufferRead                                           alacd_BitBufferRead
#define copyPredictorTo20                                       alacd_copyPredictorTo20
#define copyPredictorTo24                                       alacd_copyPredictorTo24
#define copyPredictorTo24Shift                                  alacd_copyPredictorTo24Shift
#define copyPredictorTo32                                       alacd_copyPredictorTo32
#define copyPredictorTo32Shift                                  alacd_copyPredictorTo32Shift
#define dyn_decomp                                              alacd_dyn_decomp
#define dyn_get                                                 alacd_dyn_get
#define lead                                                    alacd_lead
#define read32bit                                               alacd_read32bit
#define dyn_get_32bit                                           alacd_dyn_get_32bit
#define getstreambits                                           alacd_getstreambits
#define lg3a                                                    alacd_lg3a
#define set_ag_params                                           alacd_set_ag_params
#define unmix16                                                 alacd_unmix16
#define unmix20                                                 alacd_unmix20
#define unmix24                                                 alacd_unmix24
#define unmix32                                                 alacd_unmix32
#define unpc_block                                              alacd_unpc_block
#define LocMemCpy                                               alacd_LocMemCpy
#define sign_of_int                                             alacd_sign_of_int
#define Zero16                                                  alacd_Zero16
#define LocMemSet                                               alacd_LocMemSet
#define Zero24                                                  alacd_Zero24
#define Zero32                                                  alacd_Zero32
#define SetBuffInfo                                             alacd_SetBuffInfo
#define BitBufferInit                                           alacd_BitBufferInit
#define BitBufferReset                                          alacd_BitBufferReset
#define SetDecodeResult                                         alacd_SetDecodeResult
#define UpdateBuffState                                         alacd_UpdateBuffState

#define copyPredictorTo20_32                                    alacd_copyPredictorTo20_32
#define copyPredictorTo24_32                                    alacd_copyPredictorTo24_32
#define copyPredictorTo24Shift_32                               alacd_copyPredictorTo24Shift_32
#define copyPredictorTo32_32                                    alacd_copyPredictorTo32_32
#define copyPredictorTo32Shift_32                               alacd_copyPredictorTo32Shift_32
#define unmix16_32                                              alacd_unmix16_32
#define unmix20_32                                              alacd_unmix20_32
#define unmix24_32                                              alacd_unmix24_32
#define unmix32_32                                              alacd_unmix32_32


/* const */



#endif	/* ALACD_FUNC_RENAME_H__ */
/* End of File */
