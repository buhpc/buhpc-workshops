CC=g++
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bench
LIN_FLAGES=-fopenmp
MAC_FLAGES=-Xpreprocessor -fopenmp -lomp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LIN_FLAGES) $(OBJECTS) -o $@ -lm

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
