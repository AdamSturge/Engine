CC=g++
CFLAGS=-std=c++11 -Iinclude -I/usr/local/include/eigen3 
LDFLAGS=-Llib 
LDLIBS=-lSOIL -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
define SOURCES
main.cpp camera.cpp shader.cpp sphere.cpp mesh.cpp scene.cpp model.cpp physics_entity.cpp \
time_integrator.cpp explicit_euler.cpp symplectic_euler.cpp verlet.cpp \
constant_force.cpp gravity_force.cpp backward_euler.cpp midpoint_method.cpp
endef
EXECUTABLE=sim.o

all: compile
	@echo '-----------GENERATING DOCUMENTATION-------------'
	doxygen docs/doxygen_config
compile:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE)

