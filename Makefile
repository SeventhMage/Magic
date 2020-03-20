.SUFFIXES:
.PHONY: all clean

CXX := clang++
CXXFLAGS := -Wall -g
INCLUDES := -Iinclude
LIBS := -lm
TARGET := main

VPATH := include:source
SRCDIR := source
COMPONENTDIR:= component 
SRCOBJS := $(patsubst %.cpp, %.o, $(wildcard $(SRCDIR)/*.cpp))
COMPONENTOBJS:= $(patsubst %.cpp, %.o, $(wildcard $(COMPONENTDIR)/*.cpp))
OBJS := $(SRCOBJS) $(COMPONENTOBJS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(TARGET)
	-@rm -f $(OBJS)
