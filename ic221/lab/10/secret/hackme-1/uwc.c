#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word{
  char str[1024];
  int count;
};

struct word_list{
  struct word * list;
  int last;
  int size;
};


struct word_list * new_word_list(int s){
  struct word_list * l = malloc(sizeof(struct word_list));
  l->list = malloc(sizeof(struct word)*s);
  l->last = 0;
  l->size = s;
  return l;
}

void add_word(char *s,struct word_list * l){
  int i;

  for(i=0;i<l->last;i++){
    if( strcmp(s,l->list[i].str) == 0){
      l->list[i].count++;
      return;
    }
  }

  if(l->last+1 == l->size){
    l->list = realloc(l->list, sizeof(struct word)*l->size*2);
    l->size*=2;
  }

  strcpy(l->list[l->last].str,s);
  l->list[l->last].count=1;
  l->last++;

}

int main(int argc, char * argv[]){
  if(argc < 2){
    fprintf(stderr,"%s: ERROR: require file\n",argv[0]);
    exit(1);
  }

  FILE * fin;
  if((fin = fopen(argv[1],"r")) == NULL){
    fprintf(stderr,"%s: ERROR: cannot open file '%s'\n",argv[0],argv[1]);
    exit(1);
  }

  struct word_list * l = new_word_list(10);

  char buf[1024];
  while (fscanf(fin,"%1024s",buf) != EOF){
    add_word(buf,l);
  }


  int pfd[2];
  
  pipe(pfd);

  if(fork() == 0){
    
    close(1);
    dup2(pfd[1],1);
    close(pfd[0]);
    
    int i=0;
    for( ; i < l->last ; i++){
      printf("%s %d\n",l->list[i].str,l->list[i].count);
    }
    close(pfd[1]);
    exit(0);
  }else{

    close(0);
    dup2(pfd[0],0);
    close(pfd[1]);

    char * cmd[] = {"sort", "-n", "-r", "-t", " ", "-k", "2", NULL};
    execvp(cmd[0],cmd);
    exit(1);
  }

  return 0;
}
