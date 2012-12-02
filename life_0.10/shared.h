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

struct field **space_array;
struct field **array_b;
int cp_array(struct field **space_array, struct field **array_b);
int edge_condition_o (struct field **array_b);
int edge_condition_t (struct field **array_b);
int temperature_change (struct field **space_array, struct field **array_b);
int oxygen_change (struct field **space_array, struct field **array_b);
struct field **create_space_array (void);
struct field **create_array_b (void);
int status (struct field **space_array, struct field **array_b);
int status_2 (struct field **space_array, struct field **array_b);
int body_of_program (struct field **space_array, struct field **array_b);





#define vert_size 60
#define hor_size 60
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

