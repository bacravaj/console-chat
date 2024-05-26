.PHONY: run clean

source_dirs := . user conversation engine

search_wildcards := $(addsuffix /*.cpp,$(source_dirs)) 

console-chat: $(notdir $(patsubst %.cpp,%.o,$(wildcard $(search_wildcards))))
	g++ $^ -o $@ 

VPATH := $(source_dirs)

%.o: %.cpp
	g++ -c -MD $(addprefix -I,$(source_dirs)) $<

include $(wildcard *.d)

clean:	
	rm -rf *.o *.a *.d

run: console-chat
	./console-chat
