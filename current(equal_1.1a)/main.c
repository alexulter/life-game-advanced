#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


int body_of_program (struct field **space_array, 
			struct field **array_b, 
			struct config_info *info)
{

	
	
	if (cp_array (space_array,array_b) < 0) {
		exit(-2);
		printf("F*ck! \n");
	}	
	
	
	if (info->edge_conditions == 0)
		edge_condition(array_b);
	else edge_cond_sample(array_b,info->edge_conditions);

	
	climate_change(space_array, array_b);
	status(space_array, array_b,info);
	
	return 0;
}

int 
edge_cond_sample (	struct field **space_array, 
		long int info)
{

	int i,j;
	for (i = 1; i < vert_size; i++)
	{
		if (info == 1)
		{
			space_array[i][1].temperature = -50;
			space_array[i][hor_size-1].temperature = -50;
			space_array[i][1].oxygen = 0;
			space_array[i][hor_size-1].oxygen = 0;

		}
		else if (info == 2)
		{

			space_array[i][1].temperature = ((TEMP_MAX-TEMP_MIN)*
					(sin(i/15)+1)/2+
					TEMP_MIN);
			space_array[i][hor_size-1].temperature = 
				((TEMP_MAX-TEMP_MIN)*
				 (sin(i/15)+1)/2 + 
				 TEMP_MIN);
			space_array[i][1].oxygen = ((OXY_MAX-OXY_MIN)*
					(cos(i/5)+1)/2 + 
					OXY_MIN);

			space_array[i][hor_size-1].oxygen = 
				((OXY_MAX-OXY_MIN)*
				 (cos(i/5)+1)/2 + 
				 OXY_MIN);

		}
		else if (info == 3)
		{
			space_array[i][1].temperature = ec_function_t1();
			space_array[i][hor_size-1].temperature = 
				ec_function_t1();
			space_array[i][1].oxygen = 25;
			space_array[i][hor_size-1].oxygen = 25;


		}
		else if (info == 4)
		{
			space_array[i][1].temperature = 
				space_array[i][2].temperature;
			space_array[i][hor_size-1].temperature = 
				space_array[i][hor_size-2].temperature;
			space_array[i][1].oxygen = ec_function_o1();
			space_array[i][hor_size-1].oxygen = ec_function_o1();


		}
		else if (info == 5)
		{
			space_array[i][1].temperature = 
				space_array[i][2].temperature;
			space_array[i][hor_size-1].temperature = 
				space_array[i][hor_size-2].temperature;
			space_array[i][1].oxygen = space_array[i][2].oxygen;
			space_array[i][hor_size-1].oxygen = 
				space_array[i][hor_size - 2].oxygen;


		}


	}

	for (j = 1; j < hor_size; j++)
	{
		if (info == 1)
		{
			space_array[1][j].temperature = -50;
			space_array[vert_size-1][j].temperature = -50;
			space_array[1][j].oxygen = 1;
			space_array[vert_size-1][j].oxygen = 1;

		}
		else if (info == 2)
		{

			space_array[1][j].temperature = ((TEMP_MAX-TEMP_MIN)*
					(sin(j/15)+1)/2+
					TEMP_MIN);
			space_array[vert_size-1][j].temperature = 
				((TEMP_MAX-TEMP_MIN)*
				 (sin(j/15)+1)/2 + 
				 TEMP_MIN);
			space_array[1][j].oxygen = ((OXY_MAX-OXY_MIN)*
						(cos(j/5)+1)/2+
						OXY_MIN);
			space_array[vert_size-1][j].oxygen = 
					((OXY_MAX-OXY_MIN)*
					 (cos(j/5)+1)/2 + 
					 OXY_MIN);		

		}
		else if (info == 3)
		{
			space_array[1][j].temperature = ec_function_t1();
			space_array[vert_size-1][j].temperature = 
				ec_function_t1();

		}
		else if (info == 4)
		{
			space_array[1][j].temperature = 
				space_array[2][j].temperature;
			space_array[vert_size-1][j].temperature = 
				space_array[vert_size-2][j].temperature;

		}
		else if (info == 5)
		{
			space_array[1][j].temperature = 50;
			space_array[vert_size-1][j].temperature = -50;
			space_array[1][j].oxygen = 25;
			space_array[vert_size-1][j].oxygen = 25;

		}


	}
	if (info == 4)
	{
		space_array[vert_size/2][hor_size/2].temperature = 50;
		space_array[vert_size/2-1][hor_size/2-1].temperature = 50;
		space_array[vert_size/2+1][hor_size/2+1].temperature = 50;	
		space_array[vert_size/2-1][hor_size/2+1].temperature = 50;	
		space_array[vert_size/2+1][hor_size/2-1].temperature = 50;
		space_array[vert_size/2-5][hor_size/2-5].oxygen = 50;
		space_array[vert_size/2+5][hor_size/2+5].oxygen = 50;	
		space_array[vert_size/2-5][hor_size/2+5].oxygen = 50;	
		space_array[vert_size/2+5][hor_size/2-5].oxygen = 50;

	};
	if ((info == 1)||(info == 2)||(info == 3))
	{
		space_array[vert_size/2][hor_size/2].temperature = 50;
		space_array[vert_size/2-10][hor_size/2-10].temperature = 50;
		space_array[vert_size/2+10][hor_size/2+10].temperature = 50;	
		space_array[vert_size/2-10][hor_size/2+10].temperature = 50;	
		space_array[vert_size/2+10][hor_size/2-10].temperature = 50;
		space_array[vert_size/2-20][hor_size/2-20].temperature = 50;
		space_array[vert_size/2+20][hor_size/2+20].temperature = 50;	
		space_array[vert_size/2-20][hor_size/2+20].temperature = 50;	
		space_array[vert_size/2+20][hor_size/2-20].temperature = 50;

	};
	if (info == 1)
	{
		space_array[vert_size/2-5][hor_size/2-5].oxygen = 100;
		space_array[vert_size/2+5][hor_size/2+5].oxygen = 100;	
		space_array[vert_size/2-5][hor_size/2+5].oxygen = 100;	
		space_array[vert_size/2+5][hor_size/2-5].oxygen = 100;
		space_array[vert_size/2-30][hor_size/2].oxygen = 100;
		space_array[vert_size/2+30][hor_size/2].oxygen = 100;	
		space_array[vert_size/2][hor_size/2+30].oxygen = 100;	
		space_array[vert_size/2][hor_size/2-30].oxygen = 100;

	};

	return 0;
}


