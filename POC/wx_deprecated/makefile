CPPFLAGS_END = -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation -lpthread
WX_FLAGS = $(shell wx-config --libs)
WX_CXXFLAGS = $(shell wx-config --cxxflags)

CPPFLAGS = 
SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
COMPILER = g++

.PHONY = all run clean

all: main

main: ${OBJ}
	@echo "Linking files"
	$(COMPILER) $(WX_FLAGS) $(WX_CXXFLAGS) $(CPPFLAGS) -o main ${OBJ} $(CPPFLAGS_END)
run: main
	@./main

main.o: main.cpp
	$(COMPILER) $(WX_FLAGS) $(WX_CXXFLAGS) $(CPPFLAGS) -c main.cpp $(CPPFLAGS_END)

clean: 
	@echo "Cleaning binary files"
	rm *.o
	rm main

#add all h files w/o cpp files
%.o: %.cpp %.h
	$(COMPILER) $(WX_FLAGS) $(WX_CXXFLAGS) $(CPPFLAGS) -c $< $(CPPFLAGS_END)
