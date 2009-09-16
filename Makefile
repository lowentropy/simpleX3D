INCLUDES = -I./include
DEFINES = $(INCLUDES)
CXX = g++
LD = g++
CXXFLAGS = $(DEFINES) -fPIC
LDFLAGS = --shared

OBJS = src/SFImage.o

all: $(OBJS)
	$(LD) -o libsimpleX3D.so $(LDFLAGS) $(OBJS)

.PHONY: again clean

again: clean all

clean:
	rm -f libsimpleX3D.so src/*.o
