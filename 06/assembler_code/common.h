#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<ctype.h>
#include<inttypes.h>

FILE *input_stream;
int end_pos;
char curr_command[200];
int curr_command_len;

enum command_Type{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND,
	UNKNOWN_COMMAND
}curr_command_type;

int16_t binary_command;

//#define DEBUG_ENABLE
#ifdef DEBUG_ENABLE
	#define CODE_DEBUG(...) printf(__VA_ARGS__);
#else
	#define CODE_DEBUG(...)
#endif

// Functions in code.c
void code_dest(char *dest); 
void code_comp(char* comp);
void code_jump(char* jump);

//Functions in parser.c
void parser_initializer(char* input_file);
int hasMoreCommands();
void advance();
int currentCommand();
uint16_t symbol();

char* parser_dest();
char* parser_comp();
char* parser_jump();

// Stuff related to symbol table
struct symbol_table_entry{
    char symbol[50];
    uint16_t address;
};

struct symbol_table_t{
    struct symbol_table_entry entry[2000];
    int symbol_count;
}symbol_table;

void symbol_table_constructor();
void add_symbol_table_entry(char *symbol , uint16_t address);
int contains(char *symbol);
uint16_t get_address(char *symbol);
uint16_t rom_number;
uint16_t ram_number;
