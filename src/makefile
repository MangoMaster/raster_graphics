SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
HEADERS=$(wildcard *.h)
TARGET=main
CONFIG=`pkg-config --cflags --libs opencv`

all: $(TARGET)

$(TARGET): $(OBJECTS) $(HEADERS)
	@echo "Now generating $(TARGET) ..."
	g++ $(OBJECTS) -o $(TARGET) $(CONFIG)

%.o: %.cpp $(HEADERS)
	@echo "Now compiling $< ..."
	g++ $< -c -std=c++11 -o $@ $(CONFIG)

.PHONY: clean
clean:
	rm $(TARGET) *.o