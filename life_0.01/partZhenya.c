#include <stdio.h>
#include <stdlib.h>
 

double **a;

 struct field **space_array;
 int vert_size = 100;
 int hor_size = 100;
 struct field **array_b;


    double gradient ( void )  // makes temperature gradient 
    {  int i,j;
          for (i=2,i<vert_size,i++)
	  {   
	      for (j=1,j<hor_size,j++)                  // takes averrage on th neighbours' content
                {   space_array[i][j]->temperature= (array_b[i-1][j-1]->temperature+arrya_b[i-1][j]->temperature+array_b[i-1][j+1]->temperature+array_b[i][j-1]->temperature+
	          array_b[i][j+1]->temperature+array_b[i+1][j-1]->temperature+array_b[i+1][j]->temperature+array_b[i+1][j+1]->temperature)/8;
                } 
          }  
    }
       



    int main (void)
  {   
  	int i;
  	
	a = realloc(NULL, sizeof(void*)*4);
  	
	for (i=1; i<=3; i++){
		
		a[i]=realloc(NULL, sizeof(double)*3);	
	};
	
        a[1][1]= 4;
	printf("OK\n");
	a[2][0]=3;
	printf("OK\n");
	a[3][1]=1;
	printf("OK\n");
 // gradient() ;

  printf("%f \n",/* a[0][0]);*/gradient()  );
  
  }



 /* int vert_size=5;
  int hor_size=5;
   double temperature_change ( double a[vert_size,hor_size] ) // makes temperature chanege in the whole field
  {
      int i,j; 
        for ()


  }*/
