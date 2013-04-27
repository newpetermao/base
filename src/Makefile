
LIB_PATH= ../../lib

include Makefile.env

INCS= \
  -I$(GTESTINC)

LIBS= \
  $(GTEST)

CC= g++
CFLAGS= \
  -g -pg -Wall -Winline -pipe -finline-functions
LDFLAGS = \
  $(LIBS) \
  -lm -lpthread -lz

BASEOBJ= \
  config.o

BASE_LIB= ../bin/libbase.a
TARGET= $(BASE_LIB)

all : $(TARGET)

$(BASE_LIB) : $(BASEOBJ)
	ar rcs $@ $^

%.o : %.cpp
	$(CC) $< -o $@ -c $(CFLAGS) $(INCS)

%.o : %.cc
	$(CC) $< -o $@ -c $(CFLAGS) $(INCS)

%.o : %.c
	$(CC) $< -o $@ -c $(CFLAGS) $(INCS)

test : $(BASE_LIB)
	$(CC) -c ../test/unittest.cc  -o ../test/unittest.o -I$(GTESTINC) -I./
	$(CC) -o ../test/unittest \
    ../test/unittest.o $(GTEST) -lpthread -L../bin -lbase
	../test/unittest

clean:
	rm -f *.o $(TARGET) *~
	rm -rf ../test/*.o ../test/unittest
