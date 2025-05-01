CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++17

TARGET = c3p1.out
LIB = libc3p1.a
SRCS = libc3p1.cpp string.cpp
OBJS = libc3p1.o string.o

all: $(LIB) $(TARGET) 

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(LIB)

$(LIB): $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.cpp string.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET) $(LIB)