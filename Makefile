BINARY=vp6500mixer

all:	build

build:	$(BINARY)

clean:
	rm -f $(BINARY)
	rm -f *~
	rm -f *.o

#$(BINARY):	$(BINARY).o

#$(BINARY).o:	$(BINARY).c
