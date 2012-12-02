#include <stdio.h>
#include <stdlib.h>
#include "shared.h"


int body_of_program (int argc, char **argv)
{

	
	
	//Забиваем всю границу - жизни нет

	//Копируем основной массив в дополнительный
	if (cp_array (space_array,array_b) < 0) {
		exit(-2);
		printf("Дело плохо \n");
	}	
	//Задаём климат на границе
	edge_condition_o(array_b);
	edge_condition_t(array_b);
	/*Устанавливаем текущее состояние температуры*/
	temperature_change(space_array, array_b);
	/*Устанавливаем текущее состояние кислорода*/
	oxygen_change(space_array, array_b);

	//Вызываем функцию, подсчитывающую очередное состояние "жизни"
	status(space_array);
	
	


	return 0;
}


