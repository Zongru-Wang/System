CC = gcc
CCFLAGS = -g -O0 -fPIC

all : run 

lib :  mymalloc.o
	$(CC) $(CCFLAGS) -shared -o libmalloc.so $^ -lm

%.o : %.c
	$(CC) $(CCFLAGS) $< -w -c -std=c99 -o $@ -lm -lpthread -ggdb

t-test1 : t-test1.o
	$(CC) $(CCFLAGS) $< -o $@ -ggdb -std=c99 -lm -lpthread 

run : lib t-test1 
	LD_PRELOAD=`pwd`/libmalloc.so ./t-test1

clean :
	rm libmalloc.so *.o ./t-test1 
