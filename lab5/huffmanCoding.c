struct huffnode{
	int freq;
	int is_command;
	union{
		struct{
			struct huffnode * left;
			struct huffnode * right;
		}compound;
		unsigned char c;
	}u;
}

struct huffnode * build_huffman_tree(int * freqs, int nchars){
	struct huffnode ** list;
	list = malloc(sizeof(struct huffnode *) * nchars);
	for(int i = 0; i < nchars; i++){
		list[i] = huffnode_newleaf(i, freqs[i]);
	}
	int min1 = find_ least_frequent(list, nchars);
	struct huffnode * left = list[min1];
	list[min1] = NULL;
	int min2 = find_least_frequent(list, nchars);
	
	//int * vacant_p;
	//struct huffnode * left = find_least_frequent(list, nchars, vacant_p);
	//struct huffnode * right = find_least_frequent(list, nchars, vacant_p);
	
	//int vacant;
	//struct huffnode * left = find_least_frequent(list, nchars, &vacant);
	//struct huffnode * right = find_least_frequent(list, nchars, &vacant);
	//list[vacant] = huffnode_newcompond(left, right); for(int i = 0; i < nchars - 1; i++)
	
struct huffnode * huffnode_newleaf(unsigned char c, int freqs){
		struct huffnode * leaf;
		leaf = malloc(sizeof(struct huffnode));
		leaf -> freq = freq;
		leaf -> is_command = 0;
		leaf -> u * c = c;
		return leaf;
}

int find_least_frequent(struct huffnode ** list, int nchars){
	int min_idx = -1;
	int min_freq = INT_MAX;
	for(int i = 0; i < nchars; i++){
		if(list[i] != NULL){
			if(list[i] -> freq < min_freq){
				min_freq = list[i] -> freq;
				min_idx = i;
			}
		}
		struct huffnode * result = list[min_idx];
		list[min_idx] = NULL;
		return result;
	}
}

int find_least_frequent(struct huffnode ** list, int nchars, int * vacant_p){
	int min_idx = -1;
	int min_freq = INT_MAX;
	for(int i = 0; i < nchars; i++){
		if(list[i] != NULL){
			if(list[i] -> freq < min_freq){
				min_freq = list[i] -> freq;
				min_idx = i;
			}
		}
		vacant_p = &min_idx;
		struct huffnode * result = list[min_idx];
		list[min_idx] = NULL;
		return result;
	}
}

struct huffnode * huffnode_newcompound(struct huffnode * left, struct huffnode * right){
	stuct huffnode * fork;
	fork = malloc(sizeof(struct huffnode));
	fork -> u.command.left = left;
	fork -> u.command.right = right;
	fork -> is_command = 1;
	fork -> freq = left -> freq + right -> freq;
	return fork;
}

 
	