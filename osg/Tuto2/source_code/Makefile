CSRCS=Tuto5.cpp

CFLAGS =  -c -O3 -DNDEBUG -fPIC

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL 
INCOSG = -I/home/franclin/OpenSceneGraph/include
LDLIBS = -lm -ldl -lGL -lGLU -lpthread -lXext -lX11

LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib -L/usr/local/lib
LDOSG = -L/home/franclin/OpenSceneGraph/lib -losg -losgViewer -losgSim
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))

CC = g++

EXE=Tuto5

all: $(EXE)

$(EXE): $(COBJS) 
	g++ -o$(EXE) $(COBJS) $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)


$(COBJS): %.o : %.cpp 
	$(CC) $(CFLAGS) -o $@ $< 

