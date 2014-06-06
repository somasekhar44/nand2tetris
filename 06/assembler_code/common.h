#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

FILE *input_stream;
int end_pos;
char curr_command[100];
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