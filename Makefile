#target_plat := ios
#platform := ios32
target_plat := mac
platform := x86_64
include config.mk
.SUFFIXES:
.PHONY: all clean

CPPFLAGS := -Wall -g -std=c++11 -shared -Qunused-arguments
INCLUDES := -Iinclude -Icommon
LIBS := -lm

OBJDIR := build/obj/magic
BINDIR := build/bin
SRCDIRS := source source/render source/scene source/component
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

$(TARGET) : $(OBJS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(LIBS) $^ -o $@
	mv $(TARGET) $(BINDIR)
$(OBJDIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(BINDIR)/$(TARGET)
	-@rm -f $(OBJS)
