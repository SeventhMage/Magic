#检测系统
OS = $(shell uname)

#设置是否调试
ifeq ($(DEBUG), 0)
	DEBUG_FLAGS := -O3
else
	DEBUG_FLAGS := -G
endif

#########################################
############MinGW ###################
ifeq ($(findstring MINGW, $(OS)), MINGW)
	CROSS ?= 
	CC	:= $(CROSS)gcc -fPIC -DPIC
	CPP	:= $(CROSS)g++ -fPIC -DPIC -isystem c:/mingw/lib/gcc/mingw32/6.3.0/include/c++
	LD	:= $(CROSS)ld
	AR	:= $(CROSS)ar
	ASM	:=	yasm -DPIC
	TARGET := libmagic.dll
endif

#########################################
############linux系统 ###################
ifeq ($(findstring Linux, $(OS)), Linux) 
	CROSS ?= 
	CC	:= $(CROSS)gcc -fPIC -DPIC
	CPP	:= $(CROSS)g++ -fPIC -DPIC
	LD	:= $(CROSS)ld
	AR	:= $(CROSS)ar
	ASM	:=	yasm -DPIC
	TARGET := libmagic.so
###ARM32架构	
ifeq ($(platform), arm32)
	ARCH_DEF	:=
	EXTRA_CFLAGS := -march=armv7-a -marm $(ARCH_DEF)
	EXTRA_LFLAGS := -march=armv7-a -marm 
	EXTRA_AFLAGS := -march=armv7-a $(ARCH_DEF)
	OUT_DIR		:= ./bin/arm32
endif

###ARM64架构	
ifeq ($(platform), arm64)
	ARCH_DEF	:=
	EXTRA_CFLAGS := -march=armv8-a $(ARCH_DEF)
	EXTRA_LFLAGS := -march=armv8-a  
	EXTRA_AFLAGS := -march=armv8-a $(ARCH_DEF)
	OUT_DIR		:= ./bin/arm64
endif

###X86_32架构	
ifeq ($(platform), x86_32)
	ARCH_DEF	:=
	EXTRA_CFLAGS := -m32 $(ARCH_DEF)
	EXTRA_LFLAGS := -m32 -shared
	EXTRA_AFLAGS := -m x86 $(ARCH_DEF)
	OUT_DIR		:= ./bin/x86m32
endif


###X86_64架构	
ifeq ($(platform), x86_64)
	ARCH_DEF	:=
	EXTRA_CFLAGS := -m64 $(ARCH_DEF)
	EXTRA_LFLAGS := -m64 -shared -Wl, -Bsymbolic
	EXTRA_AFLAGS := -m amd64 $(ARCH_DEF)
	OUT_DIR		:= ./bin/x86m64
endif

endif

#########################################
############MAC/IOS系统 ###################
ifeq ($(findstring Darwin, $(OS)), Darwin) 

###MAC平台
ifeq ($(target_plat), mac)
	CROSS ?= 
	CC	:= $(CROSS)gcc -fPIC -DPIC
	CPP	:= $(CROSS)g++ -fPIC -DPIC
	AR	:= $(CROSS)ar
	ASM	:=	yasm -DPIC
	TARGET := libmagic.dylib
	
##X86_32架构
ifeq ($(platform), x86_32)
	ARCH_DEF :=
	EXTRA_CFLAGS	:= -m32
	EXTRA_LFLAGS	:= -m32 -dynamiclib -Wl, -dynamic -Wl, -read_only_relocs, suppress
	EXTRA_AFLAGS	:= -f macho32 -m x86
	OUT_DIR			:= ./bin/mac32
endif

##X86_64架构
ifeq ($(platform), x86_64)
	ARCH_DEF :=
	EXTRA_CFLAGS	:= -m64
	EXTRA_LFLAGS	:= -m64 -dynamiclib -Wl, -dynamic
	EXTRA_AFLAGS	:= -f macho64 -m amd64
	OUT_DIR			:= ./bin/mac64
endif

endif

###IOS平台
ifeq ($(target_plat), ios)
	CROSS := iphone
	TARGET := libmagic.dylib
ifeq ($(platform), ios32)
	CC	:= xcrun -sdk $(CROSS)os clang
	CPP	:= g++
	AR	:= ar
	ASM	:= gas-preprocessor.pl -arch arm -as-type apple-clang --$(CC)
	
	ARCH_DEF	:=
	EXTRA_CFLAGS := -arch armv7 -mios-version-min=6.0
	EXTRA_LFLAGS := -arch armv7 -mios-version-min=6.0
	EXTRA_AFLAGS := -arch armv7 -mios-version-min=6.0
	OUT_DIR		:= ./bin/ios32
endif

ifeq ($(platform), ios64)
	CC	:= xcrun -sdk $(CROSS)os clang
	CPP := g++
	AR	:= ar
	ASM	:= gas-preprocessor.pl -arch aarch64 -as-type apple-clang --$(CC)
	
	ARCH_DEF	:=
	EXTRA_CFLAGS := -arch arm64 -mios-version-min=6.0
	EXTRA_LFLAGS := -arch arm64 -mios-version-min=6.0
	EXTRA_AFLAGS := -arch arm64 -mios-version-min=6.0
	OUT_DIR		:= ./bin/ios64	
endif 

ifeq ($(platform), ios_sim32)
	CC	:= xcrun -sdk $(CROSS)simulators clang
	CPP	:= g++
	AR	:= ar
	ASM	:= yasm
	
	ARCH_DEF	:=
	EXTRA_CFLAGS := -arch i386 -mios-simulator-version-min=6.0
	EXTRA_LFLAGS := -arch i386 -mios-simulator-version-min=6.0 -Wl, -Bsymbolic-functions -read_only_relocs suppress
	EXTRA_AFLAGS := -f macho32 -m x86
	OUT_DIR		:= ./bin/ios_sim
endif 

ifeq ($(platform), ios_sim64)
	CC	:= xcrun -sdk $(CROSS)simulators clang
	CPP	:= g++
	AR	:= ar
	ASM	:= yasm
	
	ARCH_DEF	:=
	EXTRA_CFLAGS := -arch x86_64 -mios-simulator-version-min=6.0
	EXTRA_LFLAGS := -arch x86_64 -mios-simulator-version-min=6.0
	EXTRA_AFLAGS := -f macho64 -m amd64
	OUT_DIR		:= ./bin/ios_sim
endif 

endif ##ifeq ($(target_plat), ios)

define CRT_DIR
	if [ ! -d $(1) ];\
	 	then\
    	mkdir -p $(1);\
    	echo "******$(1) created success!!!******";\
    else\
      echo "******$(1) has been created!!!******";\
	fi	
endef

endif
