#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


// arranges temperature gradient

int   temperature_change ( struct field **space_array , struct field **array_b)
{    
	int  i,j,k,l;
	double s;
	
	//double s;
	{
		// loop for the whole field
		for (i = 2;i < vert_size-1; i++)                      
		{   
			// loop for th whole field
			for (j = 2; j < hor_size-1; j++)                 
			{ 
			  
			/*		space_array[i][j].temperature = 	
					(array_b[i+1][j].temperature + 
					array_b[i-1][j].temperature + 
				    	array_b[i][j+1].temperature + 
					array_b[i][j-1].temperature - 
				   	 4 * array_b[i][j].temperature)*0.1 + 
					 array_b[i][j].temperature;*/
			//	space_array[i][j].temperature = space_array[i][j].temperature + dt;
				// loop for the neighbour cells
			  s=0;
				for ( k = i-1; k < i+2; k++)             
				{ 
					for (l = j-1; l < j+2; l++)       
					{
						// take average on the neighboerhood cells
						s = s +(array_b[k][l].temperature);
						//fabs(array_b[k][l].temperature);
						//s1 = fabs(array_b[k][l].temperature);
					} 
				}
				space_array[i][j].temperature = s/9; 


			}
		}	   
	}   
	return 0;
} 



//arranges oxygen gradient
int   oxygen_change ( struct field **space_array , struct field **array_b)    
{       
	int  i,j,k,l;
	double s;
	

	{
		//loop for the whole field
		for (i = 2; i < vert_size-1; i++)                         
		{   
			//loop for the whole field
			for (j = 2; j < hor_size-1; j++)                  
		      {   
			 /*     space_array[i][j].oxygen=(array_b[i+1][j].oxygen + 
			      array_b[i-1][j].oxygen + 
				  array_b[i][j+1].oxygen + array_b[i][j-1].oxygen - 
				  4 * array_b[i][j].oxygen) * 0.1 + array_b[i][j].oxygen;
			*/	

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
				space_array[i][j].oxygen = s/9;                 
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
			array_b[i][j].t_resistance=space_array[i][j].t_resistance;
			array_b[i][j].o_resistance=space_array[i][j].o_resistance;
			array_b[i][j].gender = space_array[i][j].gender;
			array_b[i][j].health = space_array[i][j].health;


		}
	}



	return 0;
}



// generates field edge conditions on temperature ,
int edge_condition_t (struct field **space_array, long int info)       
{           					       
	//using funcrions ,given in "shared.h"	
	int i,j;
	for (i = 1; i < vert_size; i++)
	{
		space_array[i][1].temperature = -50;/*((TEMP_MAX-TEMP_MIN)*(sin(i/30)+1)/2+
						TEMP_MIN);*///ec_function_t1();
		space_array[i][hor_size-1].temperature = 50;/*((TEMP_MAX-TEMP_MIN)*(sin(i/30)+1)/2+
							TEMP_MIN);*///ec_function_t1();
	}
	for (j = 1; j < hor_size; j++)
	{
		space_array[1][j].temperature = /*((TEMP_MAX-TEMP_MIN)*(sin(j/30)+1)/2+
							TEMP_MIN);*/25; 
		space_array[vert_size-1][j].temperature = 50;/*((TEMP_MAX-TEMP_MIN)*(sin(j/30)+1)/2+
							TEMP_MIN);*///ec_function_t1();
	}


	return 0;
}




//generates field edge conditions on oxygen,
int edge_condition_o (struct field **space_array, long int info)            
{   	
	// using functions given in "shared.h"
	int i,j;
	for (i = 1; i < vert_size; i++)
	{
		space_array[i][1].oxygen =100;  //ec_function_o1();
		space_array[i][hor_size-1].oxygen =0;  //ec_function_o1();
	}
	for (j = 1; j<hor_size; j++)
	{
		space_array[1][j].oxygen =  ec_function_o1();
		space_array[vert_size-1][j].oxygen = ec_function_o1();
	}


	return 0;
}
 
int antie (double x)
{
	int y;
	y= (int)x;
	return y;
}

int blue_color_t(double T)
{
	double t,r;
	int R;
	t = T / (TEMP_MAX - TEMP_MIN) * 4;
	r = ( 1 - antie(t/2) ) * ( 1 - antie(t) * (1 + (t - antie(t) ) ) );
	R= antie (65535 * r);
	return R;
}

int green_color_t (double T)
{
	double t,g;
	int G;
	t = T / (TEMP_MAX - TEMP_MIN) * 4; 
	g = (1 - antie(t/2)) * ((1 - antie(t)) * (t - antie(t)) + antie(t) ) + 
	antie (t/2)*(1 - antie(t/3)) - (t - antie (t) )*antie(t/3); 
	G = antie (65535 * g);
	return G;
}

int red_color_t (double T)
{
	double t,b;
	int B;
	t = T / (TEMP_MAX - TEMP_MIN) * 4;
	b = antie(t/3) + (t - antie (t))*antie(t/2) - (t- antie(t))* antie(t/3) ;
	B = antie (65535 * b);
	return B;
}


int blue_color_o(double O)
{
	double o,r;
	int R;
	o = O /(OXY_MAX -OXY_MIN);
	r = 1;
	R= antie (65535 * r);
	return R;
}
int green_color_o(double O)
{
	double o,r;
	int R;
	o = O /(OXY_MAX -OXY_MIN);
	r =1 - o ;
	R= antie (65535 * r);
	return R;
}
int red_color_o(double O)
{
	double o,r;
	int R;
	o = O /(OXY_MAX -OXY_MIN);
	r = 1 - o ;
	R= antie (65535 * r);
	return R;
}
 
int health_color (double h)
{
  int H;
  H = antie(65535 *( h / 100) );
  return H;

}


