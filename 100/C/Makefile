run: problem
	@cat sample_input.txt | ./problem

problem: problem.c
	gcc -Wall problem.c -o problem -O3

clean:
	rm -rf problem

.PHONY: run clean
