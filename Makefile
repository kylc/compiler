CXX=clang++
RM=rm -f

CXXFLAGS=-Wall -Wextra -std=c++11 -I/usr/include/boost -Iinclude/ -O2 -g -DBOOST_LOG_DYN_LINK
LDFLAGS=-pthread -lboost_system -lboost_log_setup -lboost_log -lboost_date_time -lboost_thread -lrt -lboost_filesystem -lboost_program_options

SRCS=$(shell find src/ -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o compiler $(OBJS) $(LDFLAGS)

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
