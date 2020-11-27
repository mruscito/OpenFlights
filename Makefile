EXENAME = flight
OBJS = main.o projController.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm
# Custom Clang version enforcement logic:

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp projController.cpp
	$(CXX) $(CXXFLAGS) main.cpp

controller.cpp : projController.cpp projController.h
	$(CXX) $(CXXFLAGS) projController.cpp

clean :
	-rm -f *.o .txt $(EXENAME) test