include ../make.inc

execs = bernouilli_distribution_exemple.exe  uniform_distribution_exemple.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

bernouilli_distribution_exemple.exe : bernouilli_distribution_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

uniform_distribution_exemple.exe    : uniform_distribution_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
