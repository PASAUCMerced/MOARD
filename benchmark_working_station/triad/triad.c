#include "triad.h"

void triad(double *a,double *b, double *c,double s){
	int i;
	for(i=0;i<NUM;i++){
		c[i] = a[i] + s*b[i];
	}
    for(i=0;i<NUM;i++){
        printf("the value is: %fl\n", c[i]);
    }
    for(i=0;i<NUM;i++){
        b[i] = s*c[i] - a[i];
    }
}

int main(){
	double *a, *b, *c;
    a = (double *) malloc (sizeof(double) * NUM);
    b = (double *) malloc (sizeof(double) * NUM);
    c = (double *) malloc (sizeof(double) * NUM);
	int i;
  //srand(time(NULL));
	for(i=0; i<NUM; i++){
		c[i] = 0;
		a[i] = 1.1;
		b[i] = 1.1;
	}

	triad(&a[0],&b[0],&c[0],-3.21);
  
  FILE *output;
  output = fopen("output.data", "w");
  for(i=0; i<NUM; i++)
    fprintf(output, "%fl,", c[i]);
  
  fprintf(output, "\n");
  fclose(output);
	return 0;
}
