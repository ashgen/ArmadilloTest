
all:
	g++ arinverse.cpp  -o test_matrix_pseudoinverse -std=c++11 -larmadillo -lgomp -fopenmp -lopenblas -march=native -O3 -DARMA_NO_DEBUG -DNDEBUG -DHAVE_INLINE

