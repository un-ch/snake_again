
enum { symbol_target = '+' };
enum { symbol_snake = '*' };
enum { symbol_barrier_pipe = '|' };
enum { symbol_barrier_plus = 'x' };
enum { symbol_blank = ' ' };
enum { symbol_comma = ',' };
enum { symbol_parenthesis_left = '(' };
enum { symbol_parenthesis_right = ')' };
enum { key_escape = 27 };
enum { key_spacebar = ' ' };
enum { key_yes = 121 };
enum { key_no = 110 };

enum { max_snake_length = 5 };
enum { max_target_amount = 20 };
enum { max_round_num = 5 };

enum { snake_speed = 120 };

static const char greeting_message[] = "Simple Snake Game";
static const char question_on_game_continue[] = "would you like to continue the game?";
static const char str_name_target[] = "target";
static const char str_name_snake[] = "snake";
static const char str_name_barrier[] = "barrier";


#define TRUE 1
#define FALSE 0

struct coordinate {
	int x,y;
};

struct coordinate_list {
	struct coordinate coord;
	struct coordinate_list *next;
};

struct coordinate_doubly_list {
	struct coordinate coord;
	struct coordinate_doubly_list *next, *prev;
};

struct coordinate_deque {
	struct coordinate_doubly_list *first, *last;
};

struct game_level_settings {
	int round_num;
	int current_snake_length;
	int snake_speed;
	int max_barrier_amount;
};
