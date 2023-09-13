#Nicholas Kalinowski
#UMSL CS 4760
#Project 1
#Dr. Sanjiv Bhatia
#September 12, 2023

CC 	= gcc
CFLAGS	= -g
TARGET 	= reverse
OBJS	= main.o
.SUFFIXES: .c .o

.DEFAULT_GOAL : $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -c $<
.PHONY: clean
clean:
	/bin/rm -f *.o $(TARGET)


