
target_plat := mac
include ../config.mk
.SUFFIXES:
.PHONY: all clean

CPPFLAGS := -Wall -g -std=c++11 
INCLUDES := -I../include -I../common
LDFLAGS := -L../build/bin
LIBS    := -lm -lmagic
TARGET := main


BINDIR := ../build/bin
OBJDIR := ../build/obj/example
SRCDIRS := .
vpath %.cpp $(SRCDIRS)
SRC_CPP = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
OBJ_CPP = $(addprefix $(OBJDIR)/,$(patsubst %.cpp, %.o,$(notdir $(SRC_CPP))))
SRCOBJS := $(foreach dir, $(SRCDIRS), $(patsubst %.cpp, %.o, $(wildcard $(dir)/*.cpp))) 
OBJS := $(OBJ_CPP)#$(SRCOBJS)
TARGET:=$(TARGET)
all: dir_create $(TARGET)

dir_create:  
	@$(call CRT_DIR,$(OBJDIR))
	@$(call CRT_DIR,$(BINDIR))

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) $^ -o $@
	mv $(TARGET) $(BINDIR)

$(OBJDIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(BINDIR)/$(TARGET)
	-@rm -f $(OBJS)
