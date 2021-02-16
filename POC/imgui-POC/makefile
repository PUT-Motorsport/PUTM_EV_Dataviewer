CPPFLAGS_END = -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation -lpthread -lallegro -lallegro_main -lallegro_primitives

CPPFLAGS = 
SRCS := $(wildcard *.cpp)
SRCS_IMGUI := $(wildcard imgui/*.cpp)
#SRCS = $(wildcard */*.cpp)
OBJ := $(SRCS:%.cpp=%.o)
OBJ_IMGUI := $(SRCS_IMGUI:%.cpp=%.o)
COMPILER = g++

.PHONY = all run clean

all: main 

main: ${OBJ} ${OBJ_IMGUI}
	@echo "Linking files"
	$(COMPILER) $(CPPFLAGS) -o data_view ${OBJ} ${OBJ_IMGUI} $(CPPFLAGS_END)
run: main
	@./data_view

main.o: main.cpp
	$(COMPILER) $(CPPFLAGS) -c main.cpp $(CPPFLAGS_END)

clean: 
	@echo "Cleaning binary files"
	rm *.o
	rm imgui/*.o
	rm data_view

#add all h files w/o cpp files
%.o: %.cpp %.h
	$(COMPILER) $(CPPFLAGS) -c $< $(CPPFLAGS_END)

imgui/%.o: imgui/%.cpp imgui/%.h
	$(COMPILER) $(CPPFLAGS) -c $< $(CPPFLAGS_END) -o $(shell echo $< | cut -d . -f 1).o
	

