CC = g++
CFLAGS = --std=c++11 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS = Universe.hpp CelestialBody.hpp
OBJECTS = Universe.o CelestialBody.o

PROGRAM = NBody

.PHONY: all clean lint

all: $(PROGRAM) test $(PROGRAM).a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(PROGRAM).a: $(OBJECTS)
	ar rcs $@ $^

test: test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM) $(PROGRAM).a test

lint:
	cpplint *.cpp *.hpp

