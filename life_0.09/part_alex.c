#include <stdio.h>
#include <stdlib.h>
#include "shared.h"





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
			/*if ( (LIFE < 30) || (N < 3) || ( ( (9-N) * LIFE) < 250) )
				space_array[i][j].life_exist = 0;
			else 
				space_array[i][j].life_exist = 1; */
				/*if (i=5)&&(j=5)*/ 
				if ((N>2)&&(N<8)) space_array[i][j].life_exist=1;
				else space_array[i][j].life_exist=0;


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
			space_array[i][j].life_exist = 0;
			space_array[i][j].temperature = 0;
			space_array[i][j].oxygen = 0;

		}
	};
	return space_array;
}


struct field **create_array_b (void)
{
	int i,j;
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
