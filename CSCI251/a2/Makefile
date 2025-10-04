CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = menu.cpp ShapeTwoD.cpp shapeManager.cpp utils.cpp Assn2.cpp Square.cpp Circle.cpp Cross.cpp Rectangle.cpp Point.cpp Ellipse.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = csci251_a2.app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
