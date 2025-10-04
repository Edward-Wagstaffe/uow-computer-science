CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCS = addedFeature.cpp citylocation.cpp configHandler.cpp globals.cpp \
       menu.cpp utils.cpp weatherData.cpp weatherSummary.cpp \
       main.cpp gridStruct.cpp cityStruct.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = csci251_a1.app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
