//Mike Hanling
//list.h
//HEADER FILE FOR LAB10


typedef struct node node;

struct node{
  char data[128];
  node* next;
};


//adds string s to the front of linked list L
node* add2front(char* s, node* L);

//prints linked list L in current order (backwards from input)
void print_fwd(node* L);

//frees all elements of linked list L
void free_list(node* L);

//predicate function - 1 if string s is in linked list L
int contains(char* s, node* L);

//returns the value of linked list L at index i
char* get_ith(int i, node* L);

//returns the number of all chars in all strings in linked list L
int num_chars(node* L);

//prints linked list L in reverse order (original input)
void print_rev(node* L);

//removes element at index i from linked list L
node* remove_ith(int i, node* L);
