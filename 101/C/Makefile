run: problem
	@cat sample-input.txt | ./problem

problem: problem.c
	gcc -Wall problem.c -o problem

clean:
	rm -rf problem

.PHONY: run clean
