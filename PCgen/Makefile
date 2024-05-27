#
# Makefile.  Generated from Makefile.in by configure.
#

C_SOURCES = PCgen.c 
C_SOURCES += ../PC/can-bridge-filter.c
C_SOURCES += ../PC/can-bridge-filter-lookup.c 
C_SOURCES += ../PC/CANid-hex-bin.c 

#C_SOURCES += test.c

executable = PCgen

srcdir = .
CFLAGS =  -Wall -Wno-parentheses -DPF_CAN=29 -DAF_CAN=PF_CAN

C_INCLUDES = -I .
C_INCLUDES += -I../PC

LIBS = -lpthread 
CC = gcc
LDFLAGS = 
DEFS = -DHAVE_CONFIG_H
CPPFLAGS = 

all: PCgen

PCgen: $(C_SOURCES)
	$(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) $(LDFLAGS) $(C_INCLUDES) -o $(executable) $(C_SOURCES) $(LIBS)

clean:
	rm -f $(executable) *.o

