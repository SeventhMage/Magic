VPATH = include:source
objects = main.o magic.o CMagic.o CApplication.o CRenderer.o 
main:$(objects)
	cc -o main $(objects) 

magic.o : magic.h
CMagic.o : CMagic.h
CApplication.o : CApplication.h
CRenderer.o : CRenderer.h

.PHONY:clean
clean:
	rm main $(objects)
