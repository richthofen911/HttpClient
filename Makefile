

NDKROOT=/home/admin/Programming/sdk/android-sdk-linux/ndk-bundle
PLATFORM=$(NDKROOT)/platforms/android-21/arch-arm

CROSS_COMPILE=$(NDKROOT)/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-

CC = $(CROSS_COMPILE)gcc
LIBS =
LD = $(CROSS_COMPILE)ld
#LDFLAGS = $(PLATFORM)/usr/lib/crtbegin_dynamic.o
INCLUDE = -I.
CFLAGS = -I $(PWD) -I$(PLATFORM)/usr/include -Wall -O2 -fPIC -DANDROID -DHAVE_PTHREAD -mfpu=neon -mfloat-abi=softfp
DEFINES =
TARGET = httpDroid
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) -o $@ -fpie -pie $(OBJS)

clean:
	rm -f *.o *.a *.so



