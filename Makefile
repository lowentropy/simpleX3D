INCLUDES = -I./include
DEFINES = $(INCLUDES)
CXX = g++
LD = g++
CXXFLAGS = $(DEFINES) -fPIC
LDFLAGS = 

OBJS = src/SFImage.o

all: libsimpleX3D.so

libsimpleX3D.so: $(OBJS)
	$(LD) -o libsimpleX3D.so --shared $(LDFLAGS) $(OBJS)

.PHONY: again clean

again: clean all

clean:
	rm -f libsimpleX3D.so test src/*.o
