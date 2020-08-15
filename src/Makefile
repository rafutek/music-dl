CXX = g++
RM = rm -f
WARN = -Wall
DEBUG = -g
FLAGS = $(WARN) $(DEBUG)
CFLAGS = -c $(FLAGS)
PROG_NAME = music-dl
LIBS = -lboost_program_options -lboost_filesystem -lboost_system -lpthread -ltag

objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(objects)
	$(CXX) $(FLAGS) $^ $(LIBS) -o $(PROG_NAME)

$(objects): %.o : %.cpp
	$(CXX) $(CFLAGS) $<

clean:
	$(RM) *.o

purge: clean
	$(RM) $(PROG_NAME)

remake: purge all

install: all
	cp $(PROG_NAME) ~/.local/bin