
include ../config.mk
.SUFFIXES:
.PHONY: all clean

CPPFLAGS := -Wall -g -std=c++11
INCLUDES := -Iinclude
LDFLAGS := -L../libmagic.so
LIBS    := -lm -lmagic
TARGET := main

SRCDIRS := .
SRCOBJS := $(foreach dir, $(SRCDIRS), $(patsubst %.cpp, %.o, $(wildcard $(dir)/*.cpp))) 
OBJS := $(SRCOBJS)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(TARGET)
	-@rm -f $(OBJS)
