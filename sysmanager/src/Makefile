PREFIX_XENO := /usr/xenomai
EXECUTABLE := ../../RobotController
LIBDIR := ${PREFIX_XENO}/lib
LIBS := native xenomai pthread_rt
INCLUDES := ../tinyxml ${PREFIX_XENO}/include ../include ../../include
SRCDIR := ../tinyxml

CC = gcc
CXX = g++
CFLAGS := -std=c++11 

CPPFLAGS += $(CFLAGS) $(addprefix -I,$(INCLUDES))

RM-F := rm -f

SRCS := $(wildcard *.cc)  $(wildcard $(SRCDIR)/*.cpp)
OBJS :=  $(patsubst %.cc,%.o,$(patsubst %.cpp,%.cc,$(SRCS)))

.PHONY : all clean rebuild

all: $(EXECUTABLE)

clean:
	@$(RM-F) ${OBJS}

rebuild: clean all

$(EXECUTABLE) : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
