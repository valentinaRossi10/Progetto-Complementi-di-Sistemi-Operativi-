CC=gcc
CCOPTS=--std=gnu99 -Wall 
AR=ar

HEADERS=vrSHELL_commands.h\
	vrSHELL_constants.h\
	vrSHELL_globals.h\
	vrSHELL.h\
	
OBJS=vrSHELL_commands.o\
	vr_ls.o\
	vr_cd.o\
	vr_cat.o\
	vr_touch.o\
	vr_mkdir.o\
	vr_rm.o\
	vr_append.o\
	vr_format.o\
	vr_close.o\
	vr_SHELL.o\

LIBS=vrSHELL.a

BINS=vr_SHELL


.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

vrSHELL.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

vr_SHELL:		vr_SHELL.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ ../vrFS/vrFS.a -g

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)