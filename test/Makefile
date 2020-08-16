CXX = g++
RM = rm -f
WARN = -Wall
DEBUG = -g
FLAGS = $(WARN) $(DEBUG)
CFLAGS = -c $(FLAGS)
PROG_NAME = music-dl-test
SRC_LIBS = -lboost_program_options -lboost_filesystem -lboost_system -lpthread -ltag
LIBS = -lboost_unit_test_framework $(SRC_LIBS)
SRC_PATH = ../src

src_objects := $(filter-out ${SRC_PATH}/main.o, $(wildcard ${SRC_PATH}/*.o))
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(objects) $(src_objects)
	$(CXX) $(FLAGS) $^ $(LIBS) -o $(PROG_NAME)

$(objects): %.o : %.cpp
	$(CXX) $(CFLAGS) $<

clean:
	$(RM) *.o

purge: clean
	$(RM) $(PROG_NAME)

remake: purge all