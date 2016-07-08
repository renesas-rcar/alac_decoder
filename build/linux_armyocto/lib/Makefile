#######################################################################
#
# PURPOSE
#   ALAC Decode Software Library Makefile
#
# AUTHOR
#   Renesas Electronics Corporation
#
# DATE
#   2015/07/14
#
#######################################################################
#
#  Copyright(C) 2014-2016 Renesas Electronics Corporation.
#
#######################################################################

ifeq ($(ARCH),arm64)
PLATFORM=Linaro_GCC_64
else
ifeq ($(ARCH),arm)
PLATFORM=Linaro_GCC_32
else
$(error "Illegal architecture setuped. This Makefile for arm-gcc.")
endif
endif

############################################################################
# Tools Configration
############################################################################
CC            ?= $(CROSS_COMPILE)gcc
CXX           ?= $(CROSS_COMPILE)g++
LD            ?= $(CROSS_COMPILE)gcc
AR            ?= $(CROSS_COMPILE)ar
STRIP         ?= $(CROSS_COMPILE)strip
OBJDUMP       ?= $(CROSS_COMPILE)objdump

############################################################################
# Target Name
############################################################################
OUTDIR        = ..

VERSION       = 2
MINOR         = 0

LINKERNAME    = libALACDLA_L.so
SONAME        = $(LINKERNAME).$(VERSION)
REALNAME      = $(SONAME).$(MINOR)
TARGET        = $(OUTDIR)/$(REALNAME)

############################################################################
# Build Tree Top
############################################################################
TOPDIR       = ../../../lib

DEFINE       = -DRCAR_H3_M3

ifeq ($(PLATFORM),Linaro_GCC_64)
CFLAGS  = -O2 -pipe -feliminate-unused-debug-types
endif

ifeq ($(PLATFORM),Linaro_GCC_32)
CFLAGS  = -O2 -pipe -feliminate-unused-debug-types
endif

CFLAGS      += -fPIC
LDFLAGS     += -shared -nostartfiles

INCLUDE      = \
				-I$(TOPDIR) \
				-I$(TOPDIR)/inc \
				-I$(TOPDIR)/src/Common \
				-I$(TOPDIR)/src/Decoder \
				-I$(TOPDIR)/src/Decoder/inc \

SRCS         =  $(TOPDIR)/src/API/alacd_GetMemorySize.c \
                $(TOPDIR)/src/API/alacd_GetErrorFactor.c \
                $(TOPDIR)/src/API/alacd_GetVersion.c \
                $(TOPDIR)/src/API/alacd_Init.c \
                $(TOPDIR)/src/API/alacd_Decode.c \
                $(TOPDIR)/src/Decoder/src/ag_dec.c \
                $(TOPDIR)/src/Decoder/src/ALACBitUtilities.c \
                $(TOPDIR)/src/Decoder/src/ALACDecoder.c \
                $(TOPDIR)/src/Decoder/src/dp_dec.c \
                $(TOPDIR)/src/Decoder/src/matrix_dec.c \
                $(TOPDIR)/src/Common/common_SubFunc.c \

OBJS          = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $*.c -o $*.o $(INCLUDE) $(DEFINE)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -Wl,-s,-soname=$(SONAME) -o $(TARGET) $(OBJS)

clean:
	-rm -f $(OBJS) $(TARGET)

