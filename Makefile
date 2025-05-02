# Compiler and options
CXX=c++
CXXFLAGS=-O2 -Wall -std=c++17

# Output filenames
LIB=libc3p1.a
OUT=c3p1.out

# Lists src and obj files
#SRCS = $(wildcard *.cpp)
SRCS!=ls *.cpp
OBJS=$(SRCS:.cpp=.o)

# Manage separate targets for test binary and library archive
MAIN_OBJ=main.o
LIB_OBJS=$(filter-out $(MAIN_OBJ), $(OBJS))

# Default rule
all: $(OUT) $(LIB)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create library archive
$(LIB): $(LIB_OBJS)
	ar rcs $@ $^

# Create test binary
$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Cleaning
clean:
	rm -f $(OBJS) $(LIB) $(OUT)
