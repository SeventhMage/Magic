#target_plat := ios
#platform := ios_sim64
#target_plat := mac
#platform := x86_64
include config.mk
.SUFFIXES:
.PHONY: all clean

CPPFLAGS := -Wall -g -std=c++11 -Wunused-function #-Qunused-arguments -stdlib=libc++
INCLUDES := -Iinclude -Icommon -Idependencies/gl -Idependencies/rapidxml-1.13
LDFLAGS := -Lbuild/bin
LIBS := -lm 
STATIC_LIBS := lib/libEGL.lib lib/libGLESv2.lib 

OBJDIR := build/obj/magic
BINDIR := build/bin
SRCDIRS :=  source source/render source/render/gles3 source/scene source/component source/resource common
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
	$(CPP) $(CPPFLAGS) $() $(EXTRA_LFLAGS) $(INCLUDES) $(LDFLAGS)  $^ -shared -o $@ $(STATIC_LIBS) $(LIBS)
	mv $(TARGET) $(BINDIR)
$(OBJDIR)/%.o : %.cpp
	$(CPP) $(CPPFLAGS) $(EXTRA_LFLAGS) $(INCLUDES) $< -c -o $@

clean:
	-@rm -f $(BINDIR)/$(TARGET)
	-@rm -f $(OBJS)
