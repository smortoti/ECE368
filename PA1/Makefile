WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
GCC = gcc -g -std=c99 -g $(WARNING) $(ERROR) 

SRCS = shell_array.c pa1.c # shell_list.c - Commented out to test shellsorted array
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS) 
	$(GCC) $(OBJS) -o pa1

.c.o: 
	$(GCC) -c $*.c 

testall: test1a test1l test2 test3 test4

test1: pa1
	./pa1 -a 1K.b output1Ka
	diff output1Ka 1Ksa.b

test1l: pa1
	./pa1 1K.b output1Kl
	diff output1kl 1Ksl.b

clean: # remove all machine generated files
	rm -f pa1 *.o output???

