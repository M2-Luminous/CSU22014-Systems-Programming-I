#include "infix.h"

// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char** args, int nargs) {
  // Write your code here
  
  struct double_stack* stack = double_stack_new(nargs);
  char** postfix;
  postfix = malloc(nargs*sizeof(char**));
  int post_index = 0;
  
  for(int i=0; i<nargs; i++) {              //for each token in the input string {
    if(is_operand(args[i])) {               //if(token is a number){append token to the output string}
      postfix[post_index] = args[i]; 
      post_index++;                         //postfix 即为所谓的output string, 因为程序在运行完infix之后要将结果再
    }                                       //放进postfix,并让程序运行出来实际数字结果
    else if(strcmp(args[i],"(")==0) {       //else if (token is a left bracket) {      使用了string compare, 因为左括号是个string
      double_stack_push(stack,i);           //push bracket to stack
    }
    else if(is_operator(args[i])) {         //else if ( token in an operator ) {
        while((top_stack_greater_op(args,stack ,args[i]))) { // while ( there is operator  op  on top of the stack  && op has equal or higher precedence than token ) {
            int r = double_stack_pop(stack);//pop off the stack
            postfix[post_index] = args[r];//append the op(r) to the output string(which is going ing to go through postfix file)
            post_index++;//index++
          }
    double_stack_push(stack,(double)i);//push token operator to stack
    }  
    else if(strcmp(args[i],")")==0) {//else if ( token is right bracket ) {
      while(is_left_bracket(args,stack)) {// while ( top of stack != left bracket ) {
         int r = double_stack_pop(stack);//pop operator from stack
         postfix[post_index] = args[r];//append to output string
         post_index++;
      }
      double_stack_pop(stack);//pop left bracket
    }
  } 
  while(stack->top > 0) {
    int r = double_stack_pop(stack);//pop remaining stack items 
    postfix[post_index] = args[r];//and append each of them to the end of your reverse Polish notation expression.
    post_index++;
  }  
  return evaluate_postfix_expression(postfix,post_index);
}


int top_stack_greater_op (char** args,struct double_stack* stack, char* current_operator){
  
  char current = current_operator[0];
  if(stack->top > 0){
    int top_item = stack->items[(stack->top)-1];  //double_stack_push 在循环内部有一个top++,导致在运行结束后top pointer指向\0,因此需要index--
    if( *args[top_item] == '(' ) {//higher precedence detection
      return 0;
    }
    else if( *args[top_item] == 'X' || *args[top_item] == '/' || *args[top_item] == '^') {//higher precedence detection
      return 1;
    }
    else if( current == '+'|| current == '-') {//higher precedence detection
      return 1;
    }
  }
  return 0;
}

int is_left_bracket (char** args,struct double_stack* stack) {
  if(stack->top > 0){
    int top_item = stack->items[(stack->top)-1];
    if( *args[top_item] == '(') {
      return 0;
    }
    else return 1;
  }
  return 0;
}



/*
for each token in the input string {
  if ( token is a number ) {
    append token to the output string
  }
  else if (token is a left bracket) {
    push bracket to stack
  }
  else if ( token in an operator ) {
    while ( there is operator  op  on top of the stack  AND op has equal or higher precedence than token ) {
      pop stack and append op to the output string
    }
    push token operator to stack
  }
  else if ( token is right bracket ) {
    while ( top of stack != left bracket ) {
      pop operator from stack and append to output string
    pop left bracket
  }
}
*/

















