#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


static int N_M, N_F;
static double o_resist_m, o_resist_f, t_resist_m, t_resist_f;


int neighbor (int i, int j, struct field **array_b)
{
	int k,l,N;
	double priority, priority_m, priority_f, current_priority;
	N = 0;
	N_M = 0;
	N_F = 0;
	priority = 0;
	priority_f = 0;
	priority_m = 0;
	for (k = i - 1; k <= (i + 1); k++)
	{
		for (l = j - 1; l <= (j + 1); l++)
		{
			if ((k!=i)||(l!=j))
				N = N + array_b[k][l].life_exist;

			current_priority = array_b[k][l].t_resistance*frand();

			if (array_b[k][l].gender == 1)
			{
				N_M++;

				if (current_priority > priority)
				{
					priority = current_priority;
					o_resist_m = array_b[k][l].o_resistance;
					t_resist_m = array_b[k][l].t_resistance;

				};

			}
			else if (array_b[k][l].gender == 2)
			{
				N_F++;
				if (current_priority > priority)
				{
					priority = current_priority;
					o_resist_f = array_b[k][l].o_resistance;
					t_resist_f = array_b[k][l].t_resistance;

				};
				//o_resist_f = o_resist_f + array_b[k][l].o_resistance;
				//t_resist_f = t_resist_f + array_b[k]l[].t_resistance;
			}


		}
	}
	return N;

};

int status_2 (struct field **space_array, struct field **array_b)
{
	int i, j;
	int N;
	double LIFE;


	cp_array (space_array,array_b);
	for (i = 2; i < (vert_size - 1); i++){
		for (j = 2; j < (hor_size - 1); j++)
		{
			N = neighbor (i,j,array_b);
			LIFE = fabs(space_array[i][j].temperature-
					space_array[i][j].t_resistance)+
				fabs(space_array[i][j].oxygen-
						space_array[i][j].o_resistance)+N+1;


			space_array[i][j].health = space_array[i][j].health - LIFE;
			if ((space_array[i][j].life_exist == 0)&&(N_M > 1)&&(N_F > 1))
			{	
				space_array[i][j].life_exist = 1;
				space_array[i][j].health = 100;
				space_array[i][j].t_resistance = 
					(t_resist_m + t_resist_f)/2;
				space_array[i][j].o_resistance = 
					(o_resist_m + o_resist_f)/2;
				if (frand() < 0.5)
					space_array[i][j].gender = 1;
				else space_array[i][j].gender = 2;
			}
			else if (space_array[i][j].health < 10)
			{
				space_array[i][j].life_exist = 0;
				space_array[i][j].health = 0;
				space_array[i][j].gender = 0;
			};			


		}
	};
	return 0;
}

int status (struct field **space_array, struct field **array_b)
{
	int i, j, k, l;
	int N, LIFE;

	cp_array (space_array,array_b);
	for (i = 2; i < (vert_size - 1); i++){
		for (j = 2; j < (hor_size - 1); j++)
		{
			N = 0;
			for (k = i - 1; k <= (i + 1); k++)
			{
				for (l = j - 1; l <= (j + 1); l++)
				{
					//if (k==l) array_b[k][l].life_exist=0;
					//printf("%i %i  %i %i \n",i,j,k,l);
					if ((k!=i)||(l!=j))
						N = N + array_b[k][l].life_exist;

				}
			}



			LIFE = frand() * array_b[i][j].oxygen * 
				(50 + array_b[i][j].temperature ) / 25;

			//Default combination
			/*if ( (LIFE < 1000) || (N < 3) || ( ( (9-N) * LIFE) < 250) )
			  space_array[i][j].life_exist = 0;
			  else space_array[i][j].life_exist = 1;*/


			//Gold combination
			if ((LIFE < 2000) || (N*frand()*10 < 14) || ( ( (9-N) * LIFE) < 500))
				space_array[i][j].life_exist = 0;		
			else 
				space_array[i][j].life_exist = 1;

			/*if (i=5)&&(j=5)*/ 
			/*if ((N>2)&&(N<8)) space_array[i][j].life_exist=1;
			  else space_array[i][j].life_exist=0;*/


		}
	};
	return 0;
}

struct field **create_space_array(void)
{
	int i,j;
	//Creating of Space, which will be array
	space_array = (struct field**)realloc(NULL, ((vert_size+1)*sizeof(struct field*)));
	if (space_array == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i = 1; i < vert_size; i++) {
		space_array[i]=(struct field*)realloc(NULL, ((hor_size+1)*sizeof(struct field)));
	}


	//Setting Life_exist field's value

	for (i = 1; i < vert_size; i++){
		for (j = 1; j < hor_size; j++) {
			space_array[i][j].life_exist = 1;
			space_array[i][j].temperature = 0;
			space_array[i][j].oxygen = 0;
			space_array[i][j].o_resistance = 0;
			space_array[i][j].t_resistance = 0;
			space_array[i][j].health = 100;
			if (((i % 2)+(j % 2)) == 0)
				space_array[i][j].gender = 1;
			else  space_array[i][j].gender = 2;

		}
	};
	return space_array;
}


struct field **create_array_b (void)
{
	int i;
	//initialisation of advanced array
	array_b = (struct field**)realloc(NULL, (vert_size*sizeof(void*)));
	if (array_b == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i = 1; i < vert_size; i++) {
		array_b[i] = (struct field*)realloc(NULL, (hor_size*sizeof(struct field)));
	}
	return array_b;
}



/*struct field ***global_array (void)
  {	
  struct field ***array;
  array = (struct field***)realloc(NULL, (3*sizeof(void**)));
  if (array == NULL)
  {
  printf("Memory error: in 'space_create'\n");
  exit(-2);
  }
  return array;
  }*/
/*int main (int argc, char **argv)
  {


  create_arrays();
//Забиваем всю границу - жизни нет


//printf("OK\n");

//Копируем основной массив в дополнительный

//printf("OK\n");
if (cp_array (space_array,array_b) < 0) {
exit(-2);
printf("Дело плохо \n");
}	
//printf("OK\n");
//Задаём климат на границе
edge_condition_o(array_b);
//printf("OK\n");
edge_condition_t(array_b);
//printf("OK\n");
//	Устанавливаем текущее состояние температуры
temperature_change(space_array, array_b);
//printf("OK\n");
//	Устанавливаем текущее состояние кислорода
oxygen_change(space_array, array_b);
//printf("OK\n");

//Вызываем функцию, подсчитывающую очередное состояние "жизни"
status(space_array);
//printf("OK\n");

graphics_function(argc,argv);


return 0;
}

*/
