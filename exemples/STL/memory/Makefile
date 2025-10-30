include ../make.inc

execs = alignas_alignof.exe  create_destroy_at_exemple.exe \
        shared_pointer_from_this_exemple.exe  span_exemple.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

alignas_alignof.exe: alignas_alignof.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

create_destroy_at_exemple.exe: create_destroy_at_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@ $(LIBS)

shared_pointer_from_this_exemple.exe: shared_pointer_from_this_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

span_exemple.exe: span_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
