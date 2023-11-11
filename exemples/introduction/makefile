CXX = g++
CPPVERSION = 23
CXXFLAGS = -std=c++${CPPVERSION} -Wall -g

all: hello_world.exe caracteres.exe complexe.exe additionneur.exe \
     constantes.exe constexpr_fonctions.exe conversion.exe fichier.exe \
	 fonction_generique.exe forward_list.exe lambda_fonctions.exe \
	 list.exe map.exe named_parameters.exe string.exe structure.exe \
	 unordered_map.exe vector.exe

cleanall:
	@rm *.exe *.S *~

hello_world.exe: hello_world.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

caracteres.exe: caracteres.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

complexe.exe: complexe.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

additionneur.exe : additionneur.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

constantes.exe : constantes.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $<

constexpr_fonctions.exe : constexpr_fonctions.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $<

conversion.exe : conversion.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $<

fichier.exe : fichier.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

fonction_generique.exe : fonction_generique.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

forward_list.exe : forward_list.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

lambda_fonctions.exe : lambda_fonctions.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

list.exe : list.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

map.exe : map.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

named_parameters.exe : named_parameters.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

string.exe : string.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

structure.exe : structure.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

unordered_map.exe : unordered_map.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

vector.exe : vector.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
