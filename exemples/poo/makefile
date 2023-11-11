CXX = g++
CPPVERSION = 23
CXXFLAGS = -std=c++${CPPVERSION} -Wall -g

all: test_alg_vecteur.exe test_geom_vecteur.exe test_heritage_matrix.exe \
     test_plain_matrix.exe test_sparse_matrix.exe

cleanall:
	@rm *.exe *.o *.S *~

alg_vecteur.o : alg_vecteur.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

geom_vecteur.o : geom_vecteur.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

plain_matrix.o : plain_matrix.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sparse_matrix.o : sparse_matrix.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test_alg_vecteur.exe : test_alg_vecteur.cpp alg_vecteur.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_geom_vecteur.exe : test_geom_vecteur.cpp geom_vecteur.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_heritage_matrix.exe : test_heritage_matrix.cpp alg_vecteur.o plain_matrix.o sparse_matrix.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_plain_matrix.exe : test_plain_matrix.cpp alg_vecteur.o plain_matrix.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_sparse_matrix.exe : test_sparse_matrix.cpp alg_vecteur.o sparse_matrix.o
	$(CXX) $(CXXFLAGS) -o $@ $^
