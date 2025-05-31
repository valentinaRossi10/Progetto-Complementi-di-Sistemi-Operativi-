CC=gcc
CCOPTS=--std=gnu99 -Wall 
AR=ar

HEADERS=vrSHELL_commands.h\
	vrSHELL_constants.h\
	vrSHELL_functions.h\
	vrSHELL_globals.h\

OBJS=vrSHELL_commands.o\
	vrSHELL_test.o\

LIBS=vrSHELL.a

BINS=vrSHELL_test


.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

vrSHELL.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

vrSHELL_test:		vrSHELL_test.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ -g

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)