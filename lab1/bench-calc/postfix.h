#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stack.h"


double evaluate_postfix_expression(char ** expr, int nterms);
int is_operator(char*token);
int is_operand(char*token);
void double_stack_push(struct double_stack * this, double value);
double double_stack_pop(struct double_stack * this);


#endif
