CC = gcc
CFLAGS = -Wall -Wno-unused-function -Wconversion -g -fopenmp
LDFLAGS =

OBJS = serial_for naive_parallel interleaved_parallel blocked_parallel \
		parallel_helloworld

.PHONY: all
all: $(OBJS)

serial_for: serial_for.c tiktok.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

naive_parallel: naive_parallel.c tiktok.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

interleaved_parallel: interleaved_parallel.c tiktok.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

blocked_parallel: blocked_parallel.c tiktok.h
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

parallel_helloworld: parallel_helloworld.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


.PHONY: clean
clean: 
	rm -f $(OBJS) *.o