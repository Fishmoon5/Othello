CC          = g++
CFLAGS      = -std=c++11 -Wall -pedantic -O3
OBJS        = player.o board.o
PLAYERNAME  = yoji_nectar

all: $(PLAYERNAME) testgame

$(PLAYERNAME): $(OBJS) wrapper.o
	$(CC) -o $@ $^

testgame: testgame.o
	$(CC) -o $@ $^

testminimax: $(OBJS) testminimax.o
	$(CC) -o $@ $^

testabsearch: $(OBJS) testabsearch.o
	$(CC) -o $@ $^

testtwosteps: $(OBJS) testtwosteps.o
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

java:
	make -C java/

cleanjava:
	make -C java/ clean

clean:
	rm -f *.o $(PLAYERNAME) testgame testminimax

.PHONY: java testminimax
