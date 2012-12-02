#include <math.h>

struct field {
	double temperature;
	double oxygen;
	int life_exist;
	int t_resistance;
	int o_resistance;
	double health;
	int gender;
	};


struct config_info
	{
	int life_exist;
	int random;
	int edge_conditions;
	int become_older;
	int p_limit;
	} info;
struct field **space_array;
struct field **array_b;
int cp_array(struct field **space_array, struct field **array_b);
int edge_condition (struct field **array_b);
int climate_change (struct field **space_array, struct field **array_b);
struct field **create_space_array (struct config_info *info);
struct field **create_array_b (void);
int status (struct field **space_array, struct field **array_b, struct config_info *info);
int body_of_program (struct field **space_array, struct field **array_b, struct config_info *info);
int red_color_t (double t);
int green_color_t (double t);
int blue_color_t (double t);
int red_color_o (double o);
int green_color_o (double o);
int blue_color_o (double o);
struct config_info *reading_from_file(void);
int health_color(double h);
int edge_cond_sample(struct field **array_b, long int info);




#define vert_size 100
#define hor_size 100
#define frand() ((double) rand() / (RAND_MAX + 1.0))
#define TEMP_MAX 50
#define TEMP_MIN -50
#define OXY_MAX 100
#define OXY_MIN 0

#define ec_function_t1() ((TEMP_MAX-TEMP_MIN)*frand()+TEMP_MIN)
#define ec_function_o1() ((OXY_MAX)*frand())
//#define ec_function_t_sin(arg) ((TEMP_MAX-TEMP_MIN)*(sin(#arg)+1)/2+TEMP_MIN)


#define SIZE_OF_CELL 4
#define SPEED 10000000

