include config.mk
.SUFFIXES:
.PHONY: all clean

CPPFLAGS := -Wall -g -std=c++11 -shared
INCLUDES := -Iinclude -Icommon
LIBS := -lm

SRCDIRS := source source/render source/scene source/component
SRCOBJS := $(foreach dir, $(SRCDIRS), $(patsubst %.cpp, %.o, $(wildcard $(dir)/*.cpp))) 
OBJS := $(SRCOBJS)
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(TARGET)
	-@rm -f $(OBJS)
