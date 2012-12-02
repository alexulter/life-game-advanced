#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

			space_array[i][j].health = 
				space_array[i][j].health - LIFE;
			if ((space_array[i][j].life_exist == 0)&&
					(N_M > 1)&&(N_F > 1))
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

int status (struct field **space_array, struct field **array_b, struct config_info *info)
{
	int i, j, k, l;
	int N, LIFE;
	long int random;

	cp_array (space_array,array_b);
	for (i = 2; i < (vert_size - 1); i++){
		for (j = 2; j < (hor_size - 1); j++)
		{
			N = 0;
			for (k = i - 1; k <= (i + 1); k++)
			{
				for (l = j - 1; l <= (j + 1); l++)
				{
					if ((k!=i)||(l!=j))
						N = N + array_b[k][l].life_exist;

				}
			}


			random = frand()*(info->random % 2) + 
				1 - (info->random % 2);
			LIFE = (random*0.2+0.8) *  array_b[i][j].oxygen * 
				(50 + array_b[i][j].temperature );
			random = frand()*(info->random % 2) + 
				1 - (info->random % 2);
			if (space_array[i][j].life_exist == 1)
			{
				if ((LIFE<2000) || (N<3) || ((N>7)&&
							(info->p_limit != 0)) ||
						(space_array[i][j].health < 10))
				{
					space_array[i][j].health = 0;
					space_array[i][j].life_exist = 0;
				}
				else if ((space_array[i][j].health != 0)&&
						(info->become_older != 0))
				{
					space_array[i][j].life_exist = 1;
					space_array[i][j].health = 
						space_array[i][j].health - 20;
				};
			}
			else if((N>=3)&&(LIFE>3000))
			{
				space_array[i][j].life_exist = 1;
				space_array[i][j].health = 100;
			};
		}
	};
	return 0;
}

struct field **create_space_array(struct config_info *info)
{
	int i,j;
	//Creating of Space, which will be array
	space_array = (struct field**)realloc(NULL, 
			((vert_size+1)*sizeof(struct field*)));
	if (space_array == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i = 1; i < vert_size; i++) {
		space_array[i]=(struct field*)realloc(NULL, 
				((hor_size+1)*sizeof(struct field)));
	}


	//Setting Life_exist field's value

	for (i = 1; i < vert_size; i++){
		for (j = 1; j < hor_size; j++) {
			space_array[i][j].life_exist = info->life_exist;
			space_array[i][j].temperature = 0;
			space_array[i][j].oxygen = 0;
			space_array[i][j].o_resistance = 0;
			space_array[i][j].t_resistance = 0;
			space_array[i][j].health = 0;
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
	array_b = (struct field**)realloc(NULL, 
			((vert_size+1)*sizeof(struct field*)));
	if (array_b == NULL){
		printf("Memory error: in 'space_create'\n");
		exit(-2);
	}
	for (i = 1; i < vert_size; i++) {
		array_b[i] = (struct field*)realloc(NULL, 
				((hor_size+1)*sizeof(struct field)));
	}
	return array_b;
}

struct config_info* reading_from_file(void)
{
	FILE *fd = NULL;
	struct config_info *info = NULL;
	char buffer[100];
	char word[100];
	char *value_c;
	long int value;
	char *retrn;
	char *endofstring;
	int i;
	
	info =(struct config_info*) malloc(sizeof(struct config_info*));
	if (info == NULL) exit(-2);
	
	info->life_exist = 0;
	info->random = 0;
	info->edge_conditions = 0;
	info->become_older = 0;
	info->p_limit = 0;


	fd = fopen("life.conf","r");
	if (fd == NULL)
	{
		printf("ERROR:Cannot open the file.\n");
		exit(-2);
	}
	//Get some information from file
	retrn = fgets(buffer,100,fd);

	if (retrn == NULL)
	{
		printf("Error. Wrong file.\n");
		exit(-2);
	}
	for (i = 0; retrn != 0; i++)
	{
		if ((buffer[0] != '#')&&(buffer[0] != '\n'))
		{

			value_c = strchr(buffer,' ');
			if (value_c != NULL)
				*value_c = '\0';
			value_c++;
			strcpy(word,buffer);
			value = strtol(value_c, &endofstring, 10);
			if ((endofstring == value_c) || (endofstring[0] != '\n'))
			{
				printf("Wrong configuration file!\n");
				exit(-2);
			}
			if (strcmp(word, "life_exist") == 0) 
				info->life_exist = value;
			if (strcmp(word, "random") == 0) 
				info->random = value;
			if (strcmp(word, "edge_conditions") == 0) 
				info->edge_conditions = value;
			if (strcmp(word, "become_older") == 0) 
				info->become_older = value;
			if (strcmp(word, "p_limit") == 0)
				info->p_limit = value;
		}
		retrn = fgets(buffer,100,fd);
	}
	fclose(fd);
	return info;
}

