#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


// arranges temperature gradient

int   temperature_change ( struct field **space_array , struct field **array_b)
{    
	int  i,j,k,l,s;
	{
		// loop for the whole field
		for (i = 2;i < vert_size-1; i++)                      
		{   
			// loop for th whole field
			for (j = 2; j < hor_size-1; j++)                 
			{ 
				s=0;
				// loop for the neighbour cells
				for ( k = i-1; k < i+2; k++)             
				{ 
					for (l = j-1; l < j+2; l++)       
					{
						// take average on the neighboerhood cells
						s = s +array_b[k][l].temperature;   
					} 
				}
				space_array[i][j].temperature = s/8;


			}
		}	   
	}   
	return 0;
} 



//arranges oxygen gradient
int   oxygen_change ( struct field **space_array , struct field **array_b)    
{       
	int  i,j,k,l,s;

	{
		//loop for the whole field
		for (i = 2; i < vert_size-1; i++)                         
		{   
			//loop for the whole field
			for (j = 2; j < hor_size-1; j++)                  
			{   
				s=0;
				// loop for the neighbour cells
				for ( k = i-1; k < i+2; k++)             
				{ 
					for (l = j-1; l < j+2; l++)       
					{
						s = s +array_b[k][l].oxygen;   
					} 
				}
				//take average on th  neihbourhood 
				space_array[i][j].oxygen = s/8;                 
				//cells

			} 
		}
	}   
	return 0;
}   



// makes copy of data in space_array into array_b
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



// generates field edge conditions on temperature ,
int edge_condition_t (struct field **space_array  )       
{           					       
	//using funcrions ,given in "shared.h"	
	int i,j;
	for (i = 1; i < vert_size; i++)
	{
		space_array[i][1].temperature = ec_function_t1();
		space_array[i][hor_size-1].temperature = ec_function_t1();
	}
	for (j = 1; j < hor_size; j++)
	{
		space_array[1][j].temperature = ec_function_t1(); 
		space_array[vert_size-1][j].temperature = ec_function_t1();
	}


	return 0;
}




//generates field edge conditions on oxygen,
int edge_condition_o (struct field **space_array  )            
{   	
	// using functions given in "shared.h"
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



