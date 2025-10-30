include ../make.inc

execs = curryfication_exemple.exe  fonction_application.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

curryfication_exemple.exe: curryfication_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

fonction_application.exe: fonction_application.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
