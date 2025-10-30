include ../make.inc

execs = numbers_exemples.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

numbers_exemples.exe: numbers_exemples.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
