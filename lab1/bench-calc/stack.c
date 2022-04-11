#include "stack.h"
struct double_stack * double_stack_new(int max_size) {
// create a new empty stack
struct double_stack * result;

struct double_stack{
  double * items;
  int max_size;
  int top;                           //double_stack中的top起到count的作用,检测当pointer指向至max时则因为空间不足而停止
};

  // allocate space for the stack header
  result = malloc(sizeof(struct double_stack));
  result -> max_size = max_size;                        //相当于在为result memory allocate出一定size的memory之后,往其中的max_size格内填入max_size的数据,同理,在top格内填入top的数据
  result -> top = 0;
  // allocate space for the data stored in the stack
  result -> items = malloc(sizeof(double)*max_size);    //在result的item格中再分配一次memory,生成double * max_size大小的memory,即返回一个新的,指向于一个新分配的stack
  //return a pointer to the newly-allocated stack       //这个新的stack为我们将要push或者pop的目标
  return result;
// end of code
}
// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
//push item on to the stack
  assert(this -> top < this -> max_size);        //等同于assert(double_stack -> top < double_stack -> max_size)      assert:如果条件返回错误,则终止当前function运行 比较像if-break
  this -> items[this -> top] = value;            //items的top为stack内部pointer,用于push或者pop对应内容
  this -> top ++;
}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
  assert(this -> top > 0);                       //如果top(count)小于等于0则终止function运行
  this -> top --;                                //相当于length--
  return this -> items[this -> top];
}


double double_stack_top(struct double_stack * this) {
  assert(this -> top > 0);
  return this -> items[this -> top];             //持续返回当前stack的top pointer指向在哪里
}