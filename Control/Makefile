#Shared Variables
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
 
#C++ Project Variables
OBJS = Alfred_1_0_0.o AlarmTime.o
LIBS_1 = `mysql_config --libs`
COMP_C++ = g++
CFLAGS_1 = -Wall -c $(DEBUG) `mysql_config --cflags`
TARGET_1 = Alfred
 
#C Project Variables
LIBS_2 = -lmpg123 -lao
COMP_C = gcc
TARGET_2 = PlayMedia
 
.PHONY: all
.DEFAULT: all
 
all : $(TARGET_1) $(TARGET_2)
############################################################################
#This is the compiling info for the C++ Alfred Software
$(TARGET_1) : $(OBJS)
    $(COMP_C++) -o $(TARGET_1) $(LFLAGS) $(OBJS) $(LIBS_1)
 
Alfred_1_0_0.o : Alfred_1_0_0.cpp AlarmTime.hpp AlarmTime.cpp
    $(COMP_C++) $(CFLAGS_1) Alfred_1_0_0.cpp
 
AlarmTime.o : AlarmTime.hpp AlarmTime.cpp
    $(COMP_C++) $(CFLAGS_1) AlarmTime.cpp
 
############################################################################
#This is the compiling info for the C PlayMedia program
$(TARGET_2) : play.o
    $(COMP_C) -o $(TARGET_2) $(LFLAGS) play.c $(LIBS_2)
 
play.o : play.c
    $(COMP_C) $(CFLAGS) play.c
clean:
    \rm *.o
 
tar:
    tar cfv $(TARGET_1)_Source.tar *.cpp *.hpp *.c *.txt makefile