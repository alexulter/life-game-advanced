struct field {
	int temperature;
	int oxygen;
	int life_exist;
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
int body_of_program (struct field **space_array, struct field **array_b);




#define vert_size 20
#define hor_size 20
#define frand() ((double) rand() / (RAND_MAX + 1.0))
#define TEMP_MAX 50
#define TEMP_MIN -50
#define OXY_MAX 100
#define OXY_MIN 0
#define ec_function_t1() ((TEMP_MAX-TEMP_MIN)*frand()+TEMP_MIN)
#define ec_function_o1() ((OXY_MAX)*frand())
#define SIZE_OF_CELL 10

