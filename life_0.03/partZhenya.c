#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

       int   temperature_change ( struct field **space_array , struct field **array_b)    
          {    
    	    int  i,j;
	  
	
	    {
       	        for (i = 2;i < vert_size-1; i++)
	          {   
	              for (j = 2; j < hor_size-1; j++)                  // takes averrage on th neighbours' conteit
                           {   space_array[i][j].temperature= (array_b[i-1][j-1].temperature+array_b[i-1][j].temperature+array_b[i-1][j+1].temperature+array_b[i][j-1].temperature+
	           array_b[i][j+1].temperature+array_b[i+1][j-1].temperature+array_b[i+1][j].temperature+array_b[i+1][j+1].temperature)/8;
                           } 
                  }
             }   
            return 0;
          } 



      int   oxygen_change ( struct field **space_array , struct field **array_b)    
           {       
       	       int  i,j;
	  
	
		   {
      			    for (i = 2; i < vert_size-1; i++)
	  			 {   
	    				  for (j = 2; j < hor_size-1; j++)                  // takes averrage on th neighbours' conteit
               					 {   space_array[i][j].oxygen= (array_b[i-1][j-1].oxygen+array_b[i-1][j].oxygen+array_b[i-1][j+1].oxygen+array_b[i][j-1].oxygen+array_b[i][j+1].oxygen+array_b[i+1][j-1].oxygen+array_b[i+1][j].oxygen+array_b[i+1][j+1].oxygen)/8;
 		              			 } 
      	        	         }
	 	   }   
              return 0;
           }   
    
    
    
      int cp_array (struct field **space_array, struct field **array_b)
		{     int i,j;
			 for (i = 1; i < vert_size; i++)
				 {  
					 for (j = 1; j < hor_size; j++)
					   { 
				   		array_b[i][j].temperature=space_array[i][j].temperature;
	    				        array_b[i][j].oxygen=space_array[i][j].oxygen;
        			                array_b[i][j].life_exist=space_array[i][j].life_exist;
	   				    }
				 }
            
        

			return 0;
		}



     int edge_condition_t (struct field **space_array  )
 	   {   
   		 int i,j;
      			 for (i = 1; i < vert_size; i++)
  			        {
          				  space_array[i][1].temperature =  ec_function_t1();
				          space_array[i][hor_size-1].temperature = ec_function_t1();
  			        }
  				     for (j = 1; j < hor_size; j++)
   				        {
					           space_array[1][j].temperature = ec_function_t1(); 
					           space_array[vert_size-1][j].temperature = ec_function_t1();
				        }


     	 	 return 0;
 	   }




     int edge_condition_o (struct field **space_array  )
   	 {   
	    int i,j;
      		 for (i = 1; i < vert_size; i++)
       		   {
       			     space_array[i][1].oxygen =  ec_function_o1();
			     space_array[i][hor_size-1].oxygen =  ec_function_o1();
	           }
      			 for (j = 1; j<hor_size; j++)
     			 	   {
 				          space_array[1][j].oxygen =  ec_function_o1();
 				          space_array[vert_size-1][j].oxygen = ec_function_o1();
  			           }


	      return 0;
          }



 /*  int main (void)
  {   	int i;
  double **a;	
	a = realloc(NULL, sizeof(void*)*4);
  	
	for (i=1; i<=3; i++){
		
		a[i]=realloc(NULL, sizeof(double)*3);	
	};
	
        a[1][1]= 4;
//	printf("OK\n");
	a[2][0]=3;
//	printf("OK\n");
	a[3][1]=1;
//	printf("OK\n");
 // gradient() ;

//  printf("%f \n", a[0][0])  ; 
return 0;
 
  
  }
*/


