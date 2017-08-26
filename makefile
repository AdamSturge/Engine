CC=g++
CFLAGS=-std=c++11 -Iinclude -I/usr/local/include/eigen3 -I/usr/local/include/GLFW
LDFLAGS=-Llib -L/usr/local/lib -L/usr/lib64
LDLIBS= -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl #-lGLEW -lglfw3 -lGLU -lGL -lX11 -lpthread -lXrandr -lXi
define SOURCES
main.cpp camera.cpp shader.cpp mesh.cpp model.cpp sphere.cpp rectangular_prism.cpp time_integrator.cpp scene.cpp physics_entity.cpp \
 explicit_euler.cpp symplectic_euler.cpp verlet.cpp constant_force.cpp gravity_force.cpp backward_euler.cpp \
 midpoint_method.cpp net_force_accumulator.cpp linear_drag_force.cpp spring.cpp spring_force.cpp light.cpp material.cpp
endef
EXECUTABLE=sim.o

all: compile
	@echo '-----------GENERATING DOCUMENTATION-------------'
	doxygen docs/doxygen_config
compile:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE)

