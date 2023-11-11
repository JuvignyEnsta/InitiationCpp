CXX = g++
CPPVERSION = 23
CXXFLAGS = -std=c++${CPPVERSION} -Wall -g

all: fonctions_templates.exe classe_template.exe variadic_templates.exe \
     algebric_vector.exe rationnel_test.exe introspection.exe

cleanall:
	@rm *.exe *.o *.S *~

rationnel.o : rationnel.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

fonctions_templates.exe : fonctions_templates.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

classe_template.exe : classe_template.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

variadic_templates.exe : variadic_templates.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

algebric_vector.exe : algebric_vector.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

rationnel_test.exe : rationnel_test.cpp  rationnel.o
	$(CXX) $(CXXFLAGS) -o $@ $^

introspection.exe : introspection.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
