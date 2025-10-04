CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = main.cpp menu.cpp utils.cpp processIOFile.cpp Point2D.cpp Point3D.cpp Line2D.cpp Line3D.cpp Sorting.cpp exceptionClass.cpp ConnectedLine2D.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = csci251_a3.app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
