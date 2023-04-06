CC = g++
STDFLAGS = -std=c++11
LDLIBS = -pthread

all: program1

program1:
	$(CC) $(STDFLAGS) $(LDLIBS) program1.cpp bsd_sender.cpp thread_tasks.cpp -o program_1

.PHONY: clean
clean:
	@rm program_1

.PHONY: purge
purge: clean
	@rm -rf program_1