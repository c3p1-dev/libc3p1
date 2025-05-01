CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = c3p1.out
SRCS = libc3p1.cpp string.cpp
OBJS = libc3p1.o string.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp string.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)