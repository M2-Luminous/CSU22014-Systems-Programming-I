#include "bitset.h"
#include <stdlib.h>

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset * set = malloc(sizeof(struct bitset));   //建一个以bitset为大小的set memory
    set -> universe_size = size;                           //在set memory中设置一个变量,名为universe_size,大小为size
    int bits_per_word = sizeof(uint64_t)*8;                //每一个byte的word有8个bit,因此在获取bits_per_word时需要将uint64_t的size再乘以一个8
    if(size % bits_per_word == 0){                         //如果刚好整除,没有多余的bit空出来没地方去的话
	set -> size_in_words = (size / bits_per_word);         //就可以获得word size, 等于size / bits_per_word
    }
    else{                                                  //如果无法整除,则给多余的,大于0小于8的bits们再多准备一个memory用以存放他们
    	set -> size_in_words = (size / bits_per_word) + 1;
    }
    set -> bits = malloc(sizeof(uint64_t) * set -> size_in_words);//在set中allocate一个新的memory存放bits的数据,具体通过siezof(uint64_t) * size_in_words来获得
    for (int i = 0; i < set -> size_in_words; i++){
	set -> bits[i] = 0;
    }
    return set;//生成一共有size_in_words个empty 格子的set
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
    return this -> universe_size;      //直接获取universe_size,即size
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){ //这个cardinality可以理解为length或者count什么的
    int count = 0;
    for (int index = 0; index < this -> universe_size; index++){
		if(bitset_lookup(this,index)){
			count++;
		}
    }
    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
	int wordSize = sizeof(uint64_t) * 8;                        //其实也就是bits_per_word 
	int bitValue = item % wordSize;                             //获取剩余未到8的bits
    int wordValue = item / wordSize;                            //获取成对的8个bits的word
	uint64_t bitsetMask = 1ull << bitValue;                     //把1往左移动bitValue位
	uint64_t itemValue = this -> bits[wordValue] & bitsetMask;
	return itemValue >> bitValue;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
	int wordSize = sizeof(uint64_t) * 8;
	int bitValue = item % wordSize;
	int wordValue = item / wordSize;
  	uint64_t itemValue = this -> bits[wordValue];
	uint64_t bitsetMask = 1ull << bitValue;
  	this -> bits[wordValue] = itemValue | bitsetMask;        //用了logical shift来解决add和remove的问题
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
	int wordSize = sizeof(uint64_t) * 8;
	int bitValue = item % wordSize;
	int wordValue = item / wordSize;
  	uint64_t itemValue = this -> bits[wordValue];
	uint64_t bitsetMask = 1ull << bitValue;
  	this -> bits[wordValue] = itemValue & ~bitsetMask;       //"~"的意思为not
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2) {
	for (int i = 0; i < dest -> universe_size; i++){
		if((bitset_lookup(src1,i)) || (bitset_lookup(src2,i))){
        		bitset_add(dest,i);
    		}
  	}
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2) {
	for (int i = 0; i < dest -> universe_size; i++){
		if((bitset_lookup(src1,i)) && (bitset_lookup(src2,i))){
        		bitset_add(dest,i);
    		}
  	}
}
