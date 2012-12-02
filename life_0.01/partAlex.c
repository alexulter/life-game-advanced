#include <stdio.h>
#include <stdlib.h>

struct field {
int temperature;
int oxygen;
int life_exist;
};

struct field **space_array;
int vert_size = 100;
int hor_size = 100;
struct field **array_b;

int array_init (void)
{
	
	return 0;
}



int status (void)
{
	int i,j,k,l;
	int N;
	/*Здесь должно быть копирование основного массива в дополнительный*/

	for (i=1; i<99; i++){
		for (j=1; j<99; j++){
			N=0;
			for (k=i-1; k<i+1;i++){
				for (l=j-1;l<j+1;l++){
					N=N+array_b[k][l];
				}
			}
			
			space_array[i][j]=/*Функция от соседей и климата*/
		}
	};
	
	return 0;
}



int main (int argc, char **argv)
{
	
	
/*	struct field {
	int temperature;
	int oxygen;
	int life_exist;
	};
	
	struct field **space_array;
	int vert_size = 100;
	int hor_size = 100;*/
	int i;

	
	//Создаём пространство - массив
	space_array=(struct field**)realloc(NULL, (vert_size*sizeof(void*)));
	if (space_array == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i=1; i<100; i++) {
		space_array[i]=(struct field*)realloc(NULL, (hor_size*sizeof(struct field)));
	}
	//Инициализуем вспомогательный массив
	array_b=(struct field**)realloc(NULL, (vert_size*sizeof(void*)));
	if (array_b == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i=1; i<100; i++) {
		array_b[i]=(struct field*)realloc(NULL, (hor_size*sizeof(struct field)));
	}

	/*Устанавливаем текущее состояние температуры*/
	//temperature_change(space_array->temperature);


	/*Устанавливаем текущее состояние кислорода*/
	//oxygen_change(space_array->oxygen);
	

	//Вызываем функцию, подсчитывающую очередное состояние "жизни"
	status();
	
	
	



return 0;
}


