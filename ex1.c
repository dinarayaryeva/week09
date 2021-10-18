#include <stdio.h>
#include <stdint.h>

struct page{
  int id;
  uint16_t age;
};

int findID(struct page* p, int size, int id){
int index = -1;
  for (int i=0; i<size; i++){
    if (p[i].id == id) return i;
  }
  return index;
}

int findFree(struct page* p, int size){
  int index = -1;
  for (int i=0; i<size; i++){
    if (p[i].id == -1) return i;
  }
  return index;
}

int findMin(struct page* p, int size){
  int index = -1;
  int min = 65536;
  for (int i=0; i<size; i++){
    if (p[i].age < min){
      index = i;
      min = p[i].age;
    }
  }
  return index;
}

void print(struct page* p, int size, int id){
  for (int i=0; i<size; i++){
    printf("%d id=%d %u \n", i, p[i].id, p[i].age);
  }
  printf("current page number: %d\n\n", id);
}

int main(void) {
  
  int n;
  printf("Type the value of n \n");
  scanf("%i", &n);

  struct page p[n];

  for (int i = 0 ; i<n; i++){ //page initialization
    p[i].id = -1;
    p[i].age = 0;
  }

  FILE *f;
  f = fopen("input.txt", "r" );

  int c = 0; // current page number
  int hit = 0; //number of hites & misses respectively
  int miss = 0;

  while(EOF!=fscanf(f, "%i", &c)){

    print(p, n, c); //formated output of the state

    for (int i = 0 ; i<n; i++){ //aging process

      if (p[i].id!=c) p[i].age >>= 1; //not referenced this time

      else { //referenced page
        hit ++;
        p[i].age = 32768 + (p[i].age>>1);
        }
    }

    int index; //index for inserting

    if ((index = findID(p, n, c))==-1){ //if miss then
      miss ++;
      index = findFree(p, n); //firstly find free spot
      if (index==-1) index = findMin(p, n); //if no such then swap
      p[index].id = c;
      p[index].age = 32768; //2^15
    }
  }
  printf("hit=%d miss=%d ratio=%f", hit, miss, ((double)hit)/miss);
  fclose(f);
  return 0;
}