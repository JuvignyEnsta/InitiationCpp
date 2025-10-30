include ../make.inc

execs = any_example.exe enable_if_exemple.exe format_example.exe introspection_simple.exe optional_example.exe source_location_example.exe \
		variant_example.exe

default:
	@echo $(execs)

all: $(execs)

clean:
	@rm -fr *.exe *~ *.o

any_example.exe: any_example.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

enable_if_exemple.exe: enable_if_exemple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

format_example.exe: format_example.cpp
	@echo "Aucun compilateur capable de compiler format_exemple.cpp"
#	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

introspection_simple.exe: introspection_simple.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

optional_example.exe: optional_example.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

source_location_example.exe: source_location_example.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@

variant_example.exe: variant_example.cpp
	$(CXX) $(CCOPT) $(CCOPTIM) $< -o $@
