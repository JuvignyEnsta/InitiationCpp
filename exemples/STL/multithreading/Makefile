include ../make.inc

execs = acquire_and_release_exemples.exe bitfield_race_condition.exe manythreads_exemple.exe plain_vs_atomic_vs_volatile.exe \
		thread_arguments_exemple.exe async_deferred_exemple.exe dictionnaire_partage.exe parallel_execution_exemple.exe      \
		simple_mutex_exemple.exe true_false_sharing.exe shared_future_exemple.exe


default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

acquire_and_release_exemples.exe: acquire_and_release_exemples.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

bitfield_race_condition.exe     : bitfield_race_condition.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

manythreads_exemple.exe         : manythreads_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

plain_vs_atomic_vs_volatile.exe : plain_vs_atomic_vs_volatile.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

thread_arguments_exemple.exe    : thread_arguments_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

async_deferred_exemple.exe      : async_deferred_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

dictionnaire_partage.exe        : dictionnaire_partage.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

parallel_execution_exemple.exe  : parallel_execution_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@ $(LIBS)

simple_mutex_exemple.exe        : simple_mutex_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

true_false_sharing.exe          : true_false_sharing.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

shared_future_exemple.exe       : shared_future_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

