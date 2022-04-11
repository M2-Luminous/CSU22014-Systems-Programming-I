#include "postfix.h"

// evaluate expression stored as an array of string tokens
double evaluate_postfix_expression(char ** args, int nargs) {   //初始化了一个双重pointer
  // Write your code here
	 double result;
	 struct double_stack * stack;
	 stack = double_stack_new(nargs);              //初始化stack, 最大memory为nargs
	 for(int i = 0; i < nargs; i++){
		 if(is_operator(args[i])){
		 double op2 = double_stack_pop(stack);
		 double op1 = double_stack_pop(stack);     //pop the top two items off the stack
			 if((*args[i]) == '+')
			 result = op1 + op2;
			 else if((*args[i]) ==  '-')
			 result = op1 - op2;
			 else if((*args[i]) == 'X')
			 result = op1 * op2;
			 else if((*args[i]) == '/')
			 result = op1 / op2;
			 else if((*args[i]) == '^')
			 result = pow(op1, op2);               //apply the operator to the two items

		 double_stack_push(stack, result);          //push the result onto the stack
                }
        else                                        //is a number
	 double_stack_push(stack, atof(args[i]));       //push token onto the stack
        }
 return result;
}

int is_operator(char * token){
	if(*token == '+' || *token == '-' || *token == 'X' || *token == '/' || *token == '^'){
		if(*(token + 1) == '\0'){//如果到达了末尾(null terminator)依旧没有找到操作符的话,那么返回true
		return 1;
		}
	}
return 0;//否则返回false
}

int is_operand(char * token){
	if(*token == '+' || *token == '-' || *token == 'X' || *token == '/' || *token == '^' || *token == '(' || *token == ')'){
		if(*(token + 1) == '\0'){
		return 0;
		}
	}
	return 1;//返回的值与上一个function相反
}
/*
for each token in the input string {
  if ( token is a number ) {
    push token onto the stack
  }
  else if ( token is an operator ) {
    pop the top two items off the stack
    apply the operator to the two items
    push the result onto the stack
  }
}
*/