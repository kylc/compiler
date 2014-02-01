CXX=clang++
RM=rm -f

CXXFLAGS=-Wall -Wextra -std=c++11 -I/usr/include/boost -Iinclude/ -O2

SRCS=$(shell find src/ -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(CPPFLAGS) -o tokenizer $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
