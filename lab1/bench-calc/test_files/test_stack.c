#include "stack.h"
#include <string.h>

int main(int argc, char ** argv) {
  struct double_stack * stack = double_stack_new(argc -1);
  memset(stack->items, 0, (argc -1) * sizeof(double));
  double element;
  for (int i=1; i<argc; i++) {
    element = atof(argv[i]);
    double_stack_push(stack, element);
    printf("Pushed %f to stack\n", element);
  }
  for (int i=argc-1; i>0; i--) {
    element = double_stack_pop(stack);
    printf("Popped %f from stack\n", element);
    if (atof(argv[i]) != element) exit(-1);
  }
  exit(0);
}
/*
// simple main function to demonstrate the use of command-line parameters.
int main(int argc, char ** argv) { 
   int i; 
   if ( argc == 1 ) { 
     printf("Please try adding some command-line parameters\n"); 
     printf("Usage: %s <param1> <param2> ...\n", argv[0]); 
     exit(1); 
   } 
   printf("The number of command line parameters is stored in argc: %d\n", argc); 
   printf("The value of argc counts the name of the program itself as a parameter\n"); 
   printf("The name of the program is stored in argv[0]: %s\n", argv[0]); 
   printf("The parameters are:\n");
   for ( i = 1; i < argc; i++ ) {
     printf("%s\n", argv[i]);
   }
   return 0; 
} // end of main
*/
