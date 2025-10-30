include ../make.inc

execs = calendrier_exemple.exe  duration_exemple.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

calendrier_exemple.exe: calendrier_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

duration_exemple.exe: duration_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
