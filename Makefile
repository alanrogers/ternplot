#CFLAGS = -g -O2
CFLAGS = -g
CC = gcc
.c.o:
	$(CC) $(CFLAGS) -c $<
OBJS = ternplot.o

ternplot : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm


