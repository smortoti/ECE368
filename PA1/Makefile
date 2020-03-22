WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
GCC = gcc -g -std=c99 $(WARNINGFLAGS)

SRCS = shell_array.c shell_list.c pa1.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS) 
	$(GCC) $(OBJS) -o pa1

.c.o: 
	$(GCC) -c $*.c 

test1a: pa1
	./pa1 -a examples/1K.b output1Ka
	diff output1Ka examples/1Ksa.b

test1l: pa1
	./pa1 -l examples/1K.b output1Kl

test2a: pa1
	./pa1 -a examples/15.b output15a
	diff output15a examples/15sa.b

test2l: pa1
	./pa1 -a examples/15.b output15l
	diff output15l examples/15sa.b

test1M: pa1
	./pa1 -a examples/1M.b output1Ma

clean: # remove all machine generated files
	rm -f pa1 *.o output???
push:
	git push origin master