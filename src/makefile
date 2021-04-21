CPPFLAGS_END = -lpthread -lallegro -lallegro_main -lallegro_primitives 

CPPFLAGS =  -Wall -Wpedantic -std=c++1
INCFLAGS = -I $(shell pwd)/  -I $(shell pwd)/imgui 
LINKERFLAGS = -L $(shell pwd) -L $(shell pwd)/imgui
SRCS := $(wildcard *.cpp)
SRCS_IMGUI := $(wildcard imgui/*.cpp)
#SRCS = $(wildcard */*.cpp)
OBJ := $(SRCS:%.cpp=%.o)
OBJ_IMGUI := $(SRCS_IMGUI:%.cpp=%.o)
COMPILER = g++

.PHONY = all run clean

all: main 

main: ${OBJ} ${OBJ_IMGUI}
	$(COMPILER) $(CPPFLAGS) $(INCFLAGS) $(LINKERFLAGS) -o data_view ${OBJ} ${OBJ_IMGUI} $(CPPFLAGS_END)
run: main
	./data_view

main.o: main.cpp
	$(COMPILER) $(CPPFLAGS) $(INCFLAGS) $(LINKERFLAGS) -c main.cpp $(CPPFLAGS_END)

clean: 
	echo "Cleaning binary files"
	rm *.o
	rm imgui/*.o
	rm data_view

#add all h files w/o cpp files
%.o: %.cpp %.h
	$(COMPILER) $(CPPFLAGS) $(INCFLAGS) $(LINKERFLAGS) -c $< $(CPPFLAGS_END)

imgui/%.o: imgui/%.cpp imgui/%.h
	$(COMPILER) $(CPPFLAGS) $(INCFLAGS) $(LINKERFLAGS) -c $< $(CPPFLAGS_END) -o $(shell echo $< | cut -d . -f 1).o


