#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
	struct listset *result = malloc(sizeof(struct listset));        //直接memory allocate大小等同于listset的empty linked list set
	result -> size = 0;                                              //似乎每一次生成包括像stack,list,set此类的都要记得加一个size进去,即便本来没有
	return result;
}

struct listnode * listnode_new(char * str, struct listnode * next_node){ 
	struct listnode *node = malloc(sizeof(struct listnode));
	node -> str = str;
	node -> next = next_node;                                        //应该可以统一理解为在struct内部有的元素,在c源文件里面都要分配对应memory
	return node;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {             //lookup的最佳写法应该就是用strcmp,而不是用bit manipulation
	struct listnode *p = malloc(sizeof(struct listnode));
	p = this -> head;                                                //使pointer指向listset的head位置,从而从头到尾地遍历一遍查找有没有对应item
	while(p != NULL){                                                //不知道用while (p != '\0')可不可以达到一样的目的
		if(strcmp(item, p -> str) == 0){                             //strcmp本来应该是属于Boolean函数,不过0表示的是找到了对应string,大于0的任何数表示没找着
			return 1;
		}
		p = p -> next;                                               //pointer随循环往后移动一格
	}
	return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.如果已经有在set内部的话就不能再加进去
// New items that are not already in the set should
// be added to the start of the list如果并不在set内部的话得直接加在set的头部
void listset_add(struct listset * this, char * item) {
	if (listset_lookup(this,item) == 0) {                              //在的话return 1,不在的话return 0
		struct listnode * new_node = listnode_new(item, this -> head); //使用listnode来新建一个空白的node,或者应该可以直接写struct listnode * new_node = malloc(sizeof(struct listnode));
		new_node -> next = this -> head;                                //将新的node的下一位设置为当前的head
		this -> head = new_node;                                        //然后把当前的指向head的pointer指向new_node          这句话可能没必要写,因为引用listnode的时候已经设置了next为head
		new_node -> str = item;                                         //因为本质上new_node里面还是空的,什么都没装,所以现在要往里面加上我们本次add要加进去的item
		this -> size ++;                                                //add之后size++
	}
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
	struct listnode * p = malloc(sizeof(struct listnode));              //新建一个空白node pointer
	p = this -> head;                                                   //将node指向为head
	                                                                    //该if情况为当我们要删除的node在head处
	if (strcmp(p -> str, item) == 0) {                                  //如果找到了对应要删除的node
		  this -> head = this-> head -> next;                           //那么指向head的pointer直接指向head的下一个位置从而孤立head
		  this -> size --;
	}
	else if(listset_lookup(this, item) == 0){//if(this -> head == NULL) //该情况为listset一个元素都没有的情况,此时直接返回void即可
		return;
	}
	else {
		for (int i = 0; i < this -> size - 1; i ++) {
	 		 if (strcmp(p -> next -> str, item) == 0){           //寻找要删除的node的前一个位置,从而使得指向被删除的node的箭头指向下下格
		 		 p -> next = p -> next -> next;                  //正常的孤立中间被删除node的方法
				 this -> size --;
			  }
			  p = p -> next;
		}
	}
}
/*
	struct listset * p;
	if(listset_lookup(this, item)){
		if(strcmp(this -> head -> str, item) == 0);
			struct listnode * tmp = this -> head;
			this -> head = tmp -> next;
			free(tmp);
			return;
				
		for(p = this -> head; p -> next != NULL; p = p -> next){
			if(strcmp(p -> next -> str, item) == 0){
				struct listnode * tmp = p -> next;
				p -> next = tmp -> next;
				free(tmp);
				if(p -> next == NULL)
					return;
			}
		}
	}
*/
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1, struct listset * src2) {

}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1, struct listset * src2) {

}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
	return this -> size;                                 //直接返回size
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
