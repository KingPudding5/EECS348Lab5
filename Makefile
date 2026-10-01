CXX = g++
CXXFLAGS = -Wall -std=c++17

matrices: matrices.cpp
	$(CXX) $(CXXFLAGS) matrices.cpp -o matrices

run: matrices
	./matrices

clean:
	rm -f matrices
