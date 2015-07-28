# Makefile Written by ticktick
# Show how to cross-compile c/c++ code for android platform

.PHONY: clean

NDKROOT=/home/admin/Programming/sdk/android-linux-sdk/ndk-bundle
PLATFORM=$(NDKROOT)/platforms/android-21/arch-arm

CROSS_COMPILE=$(NDKROOT)/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
LD=$(CROSS_COMPILE)ld

CFLAGS = -I$(PWD) -I$(PLATFORM)/usr/include -Wall -O2 -fPIC -DANDROID -DHAVE_PTHREAD -mfpu=neon -mfloat-abi=softfp
LDFLAGS =

TARGET = httpDroid
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all:$(OBJS)
	$(AR) -rc $(TARGET) $(OBJS)
clean:
	rm -f *.o *.a *.so
