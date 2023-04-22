#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 1024

/* Stack node struct */
typedef struct Node {
    char line[MAX_LINE_LENGTH];
    struct Node* next;
} Node;

/* Stack struct */
typedef struct Stack {
    Node* top;
} Stack;

/* Initialize stack */
void init_stack(Stack* stack) {
    stack->top = NULL;
}

/* Push a line onto the stack */
void push(Stack* stack, char* line) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(1);
    }
    strncpy(new_node->line, line, MAX_LINE_LENGTH);
    new_node->next = stack->top;
    stack->top = new_node;
}

/* Pop a line off the stack */
void pop(Stack* stack, char* line) {
    if (stack->top == NULL) {
        fprintf(stderr, "error: stack is empty\n");
        exit(1);
    }
    Node* temp = stack->top;
    stack->top = temp->next;
    strncpy(line, temp->line, MAX_LINE_LENGTH);
    free(temp);
}

int is_empty(Stack* stack) {
  if (stack->top == NULL) {
    return 1; // emtpy
  } else {
    return 0; // not empty
  }
}

int main(int argc, char *argv[]) {
  if (argc > 3) {
    fprintf(stderr, "usage: reverse <input.txt> <output.txt>\n");
    exit(1);
  }
  if (argc == 3) {
    char *input_file = argv[1];
    char *output_file = argv[2];
    if (strcmp(input_file, output_file) == 0) {
      fprintf(stderr, "input and output file must differ\n");
      exit(1);
    }
    FILE *input_fp = fopen(input_file, "r");
    if (input_fp == NULL) {
      fprintf(stderr, "error: cannot open file '%s'\n", input_file);
      exit(1);
    }
    FILE *output_fp = fopen(output_file, "w");
    if (output_fp == NULL) {
      fprintf(stderr, "error: cannot open file '%s'\n", output_file);
      exit(1);
    }

    char *line_buffer = malloc(BUFFER_SIZE);
    if (line_buffer == NULL) {
      fprintf(stderr, "malloc failed\n");
      exit(1);
    }

    // read input file line by line feed to stack
    size_t buffer_size = BUFFER_SIZE;
    ssize_t line_size;
    char *line = NULL;
    // define and initialize the stack
    Stack stack;
    init_stack(&stack);
    
    while ((line_size = getline(&line, &buffer_size, input_fp)) != -1) {
      // allocate memory for each line
      char *new_line = malloc(line_size);
      if (new_line == NULL) {
	fprintf(stderr, "malloc failed\n");
	exit(1);
      }
      strncpy(new_line, line, line_size);
      push(&stack, new_line);
    }
    free(line);

    // print from the stack in for reverse order effect to output file
    while (!is_empty(&stack)) {
      char line[MAX_LINE_LENGTH];
      pop(&stack, line);
      fprintf(output_fp, "%s", line);
    }
      fclose(input_fp);
      fclose(output_fp);
  }

  return 0;
}
  

