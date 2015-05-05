#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size;
struct stack* grid;
int* where_is_everyone;

struct stack_element {
    struct stack_element* next;
    int value;    
};

struct stack {
    struct stack_element* top;
};

void stack_push(struct stack* stack, int value) {
    struct stack_element* e = malloc(sizeof(struct stack_element));
    e->value = value;
    e->next = stack->top;
    stack->top = e;
}

int stack_pop(struct stack* stack) {
    if (stack->top == NULL) { return -1; }
    struct stack_element* e = stack->top;
    stack->top = e->next;
    int value = e->value;
    free(e);
    return value;
}

void stack_destroy(struct stack* stack) {
    int value;
    do {
        value = stack_pop(stack);
    } while (value >= 0);
}

int stack_top(struct stack* stack) {
    if (stack->top == NULL) { return -1; }
    return stack->top->value;
}

void move_to_initial_positions(int target) {
    struct stack* stack = grid + where_is_everyone[target];

    int value;
    for (;;) {
        value = stack_pop(stack);
        if (value < 0 || value == target) {
            break;
        }
        stack_push(grid + value, value);
        where_is_everyone[value] = value;
    };
}

void move_onto(int a, int b) {
    struct stack* b_stack = grid + where_is_everyone[b];
    move_to_initial_positions(a);
    move_to_initial_positions(b);
    stack_push(b_stack, b);
    stack_push(b_stack, a);
    where_is_everyone[a] = where_is_everyone[b];
}

void move_over(int a, int b) {    
    move_to_initial_positions(a);
    stack_push(grid + where_is_everyone[b], a);
    where_is_everyone[a] = where_is_everyone[b];
}

void pile_over(int a, int b) {
    struct stack* a_stack = grid + where_is_everyone[a];
    struct stack* b_stack = grid + where_is_everyone[b];

    struct stack* temporary_stack = malloc(sizeof(struct stack));
    
    int value;
    for (;;) {
        value = stack_pop(a_stack);
        if (value < 0) {
            break;
        }
        stack_push(temporary_stack, value);
        if (value == a) {
            break;
        }
    }
    for (;;) {
        value = stack_pop(temporary_stack);
        if (value < 0) {
            break;
        }
        stack_push(b_stack, value);
        where_is_everyone[value] = where_is_everyone[b];
    }
    
    free(temporary_stack);
}

void pile_onto(int a, int b) {
    struct stack* b_stack = grid + where_is_everyone[b];
    
    int value;
    for (;;) {
        value = stack_pop(b_stack);
        if (value < 0 || value == b) {
            break;
        }
        stack_push(grid + value, value);
        where_is_everyone[value] = value;
    };

    pile_over(a, b);
}

void initialize_grid() {

    grid = malloc(sizeof(struct stack) * size);
    where_is_everyone = malloc(sizeof(int) * size);

    int i;
    for (i = 0; i < size; i += 1) {
        grid[i].top = NULL;

        stack_push(grid + i, i);
        where_is_everyone[i] = i;
    }
}

void release_resources() {
    
    int i;    
    for (i = 0; i < size; i += 1) {
        stack_destroy(grid + i);
    }
    free(grid);
    free(where_is_everyone);
}

void parse_and_execute_commands() {
    
    char cmd1[5], cmd2[5];
    int a, b;
    
    for (;;) {
        int result = scanf("%4s %d %4s %d", cmd1, &a, cmd2, &b);
        if (result == EOF) {
            /* end of file */
            break;
        }
        if (result == 1 && strncmp("quit", cmd1, 4) == 0) {
            /* exactly the quit command */
            break;
        }
        if (result != 4) {
            /* not a proper command */
            continue;
        }
        if (a == b || a < 0 || b < 0 || a >= size || b >= size) {
            /* illegal command, ignored */
            continue;
        }
        if (strncmp("move", cmd1, 4) == 0) {
            if (strncmp("onto", cmd2, 4) == 0) {
                move_onto(a, b);
            } else if (strncmp("over", cmd2, 4) == 0) {
                move_over(a, b);
            }
        } else if (strncmp("pile", cmd1, 4) == 0) {
            if (strncmp("onto", cmd2, 4) == 0) {
                pile_onto(a, b);
            } else if (strncmp("over", cmd2, 4) == 0) {
                pile_over(a, b);
            }
        }
    }
}

void print_next(struct stack_element* current) {
    if (current == NULL) {
        return;
    }
    print_next(current->next);
    printf(" %d", current->value);
}

void print_grid() {
    int i;
    for (i = 0; i < size; i += 1) {
        printf("%d:", i);
        print_next(grid[i].top);
        printf("\n");
    }
}

int main(void) {
    if (scanf("%d", &size) != 1) {
        return 1;
    }
    initialize_grid();
    parse_and_execute_commands();
    print_grid();
    release_resources();
    return 0;
}
