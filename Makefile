CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = src/JsonNode.cpp \
      src/JsonArray.cpp \
      src/JsonParser.cpp \
      src/JsonPrinter.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = json

all: $(TARGET)

$(TARGET): $(OBJ) main.o
	$(CXX) $(OBJ) main.o -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) main.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run