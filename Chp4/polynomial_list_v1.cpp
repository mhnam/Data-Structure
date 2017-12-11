#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) ((x) < (y)? -1 : (x) == (y)? 0 : 1)
#defint IS_FULL(ptr) (!(ptr))

typedef struct poly* poly_pointer;
typedef struct{
  float coeff;
  int expon;
  poly_pointer link;
}poly;

poly_pointer padd(poly_pointer a, poly_pointer b);
void attach(float coefficient, int exponent, poly_pointer* ptr);
void erase(poly_pointer *ptr);

poly_pointer a, b, d;

void main(){
  FILE* fp_a, fp_b; fp_out;
  node_pointer temp;
  int status;
  fp_a = fopen("input_a.txt", "r");
  fp_b = fopen("input_b.txt", "r);
  fp_out = fopen("output.txt", "w");
  
  while(1){
    status = fscanf(fp_a, "%f %d", &a->);
    temp = (node_pointer

    a = a->link
    
    if(status == EOF) break;
  }
  while(EOF)
    fscanf(fp_b, "%f, %d", &b->
}

//adding function
poly_pointer padd(poly_pointer a, poly_pointer b){
  //initialise
  poly_pointer front = NULL; /* points the begining of the result list */
  poly_pointer rear = NULL; /* points the end of the result list */
  poly_pointer temp = NULL; /* NOT SURE; for temporary use to "free" front pointer */
  float temp_sum = 0;
  
  rear = (poly_pointer)malloc(sizeof(poly));
  if(IS_FULL(rear)){
    printf("The memory is full\n");
    exit(1);
  }
  
  front = rear;
  
  //compute
  while(a && b){/* while both a and b has left input */
    swith(COMPARE(a->expon, b->expon)){
      case -1: /* a->expon < b->expon */
        attach(b->coef, b->expon, &rear);
        b = b->link; break;
        
      case 0: /* a->expon == b->expon */
        temp_sum = a->coef + b->coef;
        if(sum) /* if sum is greater than 0 */
          attach(temp_sum, a->expon, &rear);
        a = a->link; b = b->link; break;
        
      case 1: /* a->expon > b->expon */
        attach(a->coef, a->expon, &rear);
        a = a->link; break;
    }
    
    //attach leftovers
    for(; a; a = a->link) attach(a->coef, a->expon, &rear);
    for(; b; b = b->link) attach(b->coef, b->expon, &rear);
    rear->link = NULL; /* purpose? */
    
    //free temp, prepare for return
    temp = front; front = front->link; free(temp);
    return front;
  }
};

//attach function
void attach(float coefficient, int exponent, poly_pointer* ptr){
  //initialise
  poly_pointer temp = NULL;
  temp = (poly_pointer)malloc(sizeof(poly));
  
  if(IS_FULL(temp)){
    printf("The memory is full");
    exit(1);
  }
  
  //assign the result
  temp->coef = coefficient;  temp->expon = exponent;
  (*ptr)->link = temp; /* existing rear->link points temp */
  *ptr = temp; /* temp become rear */ 
}

//erase function
void erase(poly_pointer *ptr){
  poly_pointer temp;
  while(*ptr){
    temp = ptr; /* save the current ptr */
    *ptr = (*ptr)->link; /* update ptr to next ptr */
    free(temp); /* free saved temp poly node */
  }
}
