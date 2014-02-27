CXX=clang++
RM=rm -f

CXXFLAGS=-Wall -Wextra -std=c++11 -I/usr/include/boost -Iinclude/ -O2

SRCS=$(shell find src/ -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(CXXPFLAGS) -o compiler $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

proftest.out: main
	./compiler proftest.in > proftest.out

include .depend
