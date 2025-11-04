# Compiler
CC = gcc

# Current working directory
CURRENT_DIR := $(shell pwd)

FREERTOS_DIR = ../../Source

# Compiler flags (include directories and warnings)
CFLAGS = -I$(FREERTOS_DIR)/include \
         -I$(FREERTOS_DIR)/portable/MSVC-MingW \
         -I../common \
         -Wall 
#          -Wno-unused-but-set-variable
		 
# Source files             
SRC = main.c \
      $(FREERTOS_DIR)/tasks.c \
      $(FREERTOS_DIR)/queue.c \
      $(FREERTOS_DIR)/list.c \
      $(FREERTOS_DIR)/timers.c \
      $(FREERTOS_DIR)/event_groups.c \
      $(FREERTOS_DIR)/portable/MemMang/heap_4.c \
      $(FREERTOS_DIR)/portable/MSVC-MingW/port.c

# Output name
TARGET = freertos_demo

# Default rule
all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET).exe -lwinmm

# Run the program
run: all
	@echo "Running $(TARGET).exe in $(CURRENT_DIR) ..."
	./$(TARGET).exe

# Clean up generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET).exe
      
