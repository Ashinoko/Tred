CC = g++

all: program1

program1:
	$(CC) program2.cpp bsd_reciever.cpp -o program_2

.PHONY: clean
clean:
	@rm program_2

.PHONY: purge
purge: clean
	@rm -rf program_2