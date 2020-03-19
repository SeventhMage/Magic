VPATH = include:source:include/render:source/render
objects = main.o magic.o CMagic.o CApplication.o CRenderer.o 
main:$(objects)
	clang++ -std=c++11 -o main $(objects) 

magic.o : magic.h CMagic.h
CMagic.o : CMagic.h
CApplication.o : CApplication.h
CRenderer.o : CRenderer.h

.PHONY:clean
clean:
	rm main $(objects)
