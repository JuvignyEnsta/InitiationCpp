include ../make.inc

execs = canonique_range.exe  range_pythagoricien_exemple.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

canonique_range.exe: canonique_range.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

range_pythagoricien_exemple.exe: range_pythagoricien_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
