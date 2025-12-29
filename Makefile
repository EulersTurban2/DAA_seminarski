CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude `pkg-config --cflags opencv4`

SRC = main.cpp ./src/complex.cpp ./src/matrix.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)