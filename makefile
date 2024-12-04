#make file. will work for any code just make 
#sure to change the SOURCE FILES

# Define the compiler and the flags
CC=gcc
CFLAGS=-Wall -g

# Define the target executable
TARGET=myprogram

# Define the *SOURCE FILES*
SRCS=main.c bst.c float_rndm.c iom361_r2.c

# define the object files
OBJS=$(SRCS:.c=.o)

# rhe default target
all: $(TARGET)

# rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 	rule to build the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
	#use "make run" in the terminal in order to do the make stuff and then run
run: all
	./$(TARGET)

# Clean up the build files
clean:
	rm -f $(TARGET) $(OBJS)
