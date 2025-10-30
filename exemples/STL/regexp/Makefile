include ../make.inc

execs = regexp_exemple.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

regexp_exemple.exe: regexp_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
