#include "bloom.h"
#include <stdlib.h>

// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char * string, int seed, int range)
{
  int i;
  int hash = 0;

  // simple loop for mixing the input string
  for ( i = 0; string[i] != '\0'; i++ ) {
    hash = hash * seed + string[i];
  }
  // check for unlikely case that hash is negative
  if ( hash < 0 ) {
    hash = -hash;
  }
  // bring the hash within the range 0..range-1
  hash = hash % range;

  return hash;
}


// create a new, empty Bloom filter of 'size' items
struct bloom * bloom_new(int size) {
  struct bloom * filter= malloc(sizeof(struct bloom));
  filter -> bitset = bitset_new(size);
  filter -> size = size;
  return filter;
}

// check to see if a string is in the set
int bloom_lookup(struct bloom * this, char * item) {
  int first_hash = hash_string(item, 17, this -> size);
  int second_hash = hash_string(item, 29, this -> size);
  if((bitset_lookup(this -> bitset, first_hash) == 0) 
	  && (bitset_lookup(this -> bitset, second_hash) == 0)){
    return 1;
  }
  return 0;
}

// add a string to the set
// has no effect if the item is already in the set
void bloom_add(struct bloom * this, char * item) {
  int first_hash = hash_string(item, 17, this -> size);
  bitset_add(this -> bitset, first_hash);  
  int second_hash = hash_string(item, 29, this -> size);
  bitset_add(this -> bitset, second_hash);
}

// place the union of src1 and src2 into dest
void bloom_union(struct bloom * dest, struct bloom * src1, struct bloom * src2) {
  bitset_union(dest -> bitset, src1 -> bitset, src2 -> bitset);
}

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1, struct bloom * src2) {
  bitset_intersect(dest -> bitset, src1 -> bitset, src2 -> bitset);
}
