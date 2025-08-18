CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c++20 $(shell pkg-config --cflags freetype2)
LIBS  =  -lglfw -ldl $(shell pkg-config --libs freetype2)
INCLUDES = -Iinclude -Ithird_party/freetype2
SRC_DIR = src
OBJS_DIR = build

TARGET = edit

SRCS = $(wildcard $(SRC_DIR)/*.cpp) editor/glad/glad.c
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS)) 

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

run: $(TARGET)
	./$(TARGET)


clean:
		rm -rf $(OBJS_DIR) $(TARGET)

