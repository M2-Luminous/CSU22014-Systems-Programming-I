#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "postfix.h"

double evaluate_infix_expression(char ** expr, int nterms);
int is_operator(char*token);
int is_operand(char*token);
void double_stack_push(struct double_stack * this, double value);
double double_stack_pop(struct double_stack * this);
int top_stack_greater_op (char** args,struct double_stack* stack, char* current_operator);
int is_left_bracket (char** args,struct double_stack* stack);
#endif
