CPPFLAGS_END = -lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation -lpthread
CPPFLAGS = 
SRCS := $(wildcard *.cpp)
OBJ := $(SRCS:%.cpp=%.o)
COMPILER = g++

.PHONY = all run clean

all: main

main: ${OBJ}
	@echo "Linking files"
	$(COMPILER) $(CPPFLAGS) -o main ${OBJ} $(CPPFLAGS_END)
run: main
	@./main

main.o: main.cpp 
	$(COMPILER) $(CPPFLAGS) -c main.cpp $(CPPFLAGS_END)

clean: 
	@echo "Cleaning binary files"
	rm *.o
	rm main

#add all h files w/o cpp files
%.o: %.cpp %.h
	$(COMPILER) $(CPPFLAGS) -c $< $(CPPFLAGS_END)
