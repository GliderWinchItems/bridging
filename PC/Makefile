#
#
sourcefiles = $(srcdir)/can-bridge-filter_test.c \
	$(srcdir)/can-bridge-filter.c \
	$(srcdir)/can-bridge-filter-lookup.c \
	$(srcdir)/CANid-hex-bin.c \

executable = can-bridge-filter_test

srcdir = .
CFLAGS =  -Wall -Wno-parentheses -DPF_CAN=29 -DAF_CAN=PF_CAN
LIBS = -lpthread 
CC = gcc
LDFLAGS = 
DEFS = -DHAVE_CONFIG_H
CPPFLAGS = 

all: can-bridge-filter_test

can-bridge-filter_test: $(sourcefiles)
	$(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) $(LDFLAGS) -I . -I ./include -o $(executable) $(sourcefiles) $(LIBS)

clean:
	rm -f $(executable) *.o

