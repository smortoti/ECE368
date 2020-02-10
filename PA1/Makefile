WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
GCC = gcc -03 -std=c99 -g $(WARNING) $(ERROR) 

SRCS = shell_array.c shell_list.c pa1.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS) 
	$(GCC) $(OBJS) -o pa1

.c.o: 
	$(GCC) -c $*.c 

testall: test1sa test1sl test2 test3 test4

test1sa: pa1
	./pa1 1K.b output1Ka
	diff output1Ka 1Ksa.b

test1sl: pa1
	./pa1 1K.b output1Kl
	diff output1kl 1Ksl.b

clean: # remove all machine generated files
	rm -f pa1 *.o output???

