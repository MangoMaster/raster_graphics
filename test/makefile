SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
HEADERS=$(wildcard ../src/*.h)
TARGET=main
CONFIG=`pkg-config --cflags --libs opencv`

all: 
	@echo "Please select a test file"

line_bresenham: test_line_bresenham.o ../src/line_bresenham.o
	@echo "Now generating $@ to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

circle_midpoint: test_circle_midpoint.o ../src/circle_midpoint.o
	@echo "Now generating $@  to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

polylines_bresenham: test_polylines_bresenham.o ../src/polylines_bresenham.o ../src/line_bresenham.o
	@echo "Now generating $@  to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

fill_poly_scan_line: test_fill_poly_scan_line.o ../src/fill_poly_scan_line.o
	@echo "Now generating $@  to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

flood_fill_scan_line: test_flood_fill_scan_line.o ../src/flood_fill_scan_line.o ../src/fill_poly_scan_line.o
	@echo "Now generating $@  to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

flood_fill_scan_line_bresenham: test_flood_fill_scan_line_bresenham.o ../src/flood_fill_scan_line.o ../src/polylines_bresenham.o ../src/line_bresenham.o
	@echo "Now generating $@  to $(TARGET) ..."
	g++ $^ -o $(TARGET) $(CONFIG)

%.o: %.cpp $(HEADERS)
	@echo "Now compiling $< ..."
	g++ $< -c -std=c++11 -o $@ $(CONFIG)

.PHONY: clean
clean:
	rm $(TARGET) *.o ../src/*.o