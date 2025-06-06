CC=gcc
CCOPTS=--std=gnu99 -Wall 
AR=ar

HEADERS=fcb.h\
	vrFS_constants.h\
	vrFS_disk.h\
	vrFS.h\
	vrFS_block_manager.h\
	vrFS_dir.h\
	
OBJS=fcb.o\
     vrFS_disk.o\
     vrFS.o\
	 vrFS_block_manager.o\
     vrFS_dir.o\

LIBS=vrFS.a

#BINS=vrFS_test

#vrFS_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

vrFS.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

#vrFS_test:		vrFS_test.c $(LIBS)
#	$(CC) $(CCOPTS) -o $@ $^ -g

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)