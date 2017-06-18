CC=g++
CFLAGS=-std=c++11 -Iinclude -I/usr/local/include/eigen3 
LDFLAGS=-Llib 
LDLIBS=-lSOIL -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
SOURCES=main.cpp shader.cpp sphere.cpp mesh.cpp scene.cpp model.cpp physics_entity.cpp explicit_euler.cpp constant_force.cpp
EXECUTABLE=sim.o

all: compile
	@echo '-----------GENERATING DOCUMENTATION-------------'
	doxygen docs/doxygen_config
compile:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE)

