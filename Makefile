
# CFLAGS += -O2 -g
# CXXFLAGS += -O2 -g
CFLAGS += -O0 -g
CXXFLAGS += -O0 -g

CFLAGS += -Wall -I.
CXXFLAGS += -Wall -I.

all: psg_example

clean:
	rm -f psg_example ym7101psg.o driver/example.o

psg_example: ym7101psg.o driver/example.o
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
