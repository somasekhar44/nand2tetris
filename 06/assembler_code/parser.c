#include "common.h"
#include<stdlib.h>

//This will initialize the input_stream by opening the input_file
void parser_initializer(char* input_file){
	if( (input_stream = fopen(input_file,"r")) == NULL){
		fprintf(stderr, "Cannot open the file %s\n",input_file);
	}
	fseek(input_stream , 0 , SEEK_END );
	end_pos = ftell(input_stream);
	fseek(input_stream , 0 , SEEK_SET);
	return;
}


//returns 1 if the file has still some more commands to be parsed , else returns 0
int hasMoreCommands(){
	int curr_pos = ftell(input_stream);
	if(curr_pos == end_pos)
		return 0;

	while(1){
		if(fgets(curr_command , 80 , input_stream) == NULL){
			return 0;
		}
		if((curr_command[0] == ' ') || (curr_command[0] == '\n') || (curr_command[0] == '\r')){
			CODE_DEBUG("empty line..\n");
		} else if(strncmp(curr_command , "//" , 2) == 0){
			CODE_DEBUG("Commented line..\n");
		} else{
			CODE_DEBUG("Has a valid command.. , len = %d , curr_command[0]= %d \n" , strlen(curr_command) , curr_command[0]);
			fseek(input_stream , curr_pos , SEEK_SET);
			return 1;
		}
		curr_pos = ftell(input_stream);
	}
	return 1;
}

//Loads the next command into curr_command.
void advance(){
	if(fgets(curr_command , 80 , input_stream) == NULL){
		fprintf(stderr, "Unable to read the next command.exiting\n" );
		exit(0);
	}
	curr_command_len = strlen(curr_command);
	if((curr_command[curr_command_len-2] == '\n') || ((curr_command[curr_command_len-2] == '\r')))
		curr_command[curr_command_len-2] = '\0';
	if((curr_command[curr_command_len-1] == '\n') || ((curr_command[curr_command_len-1] == '\r')))
		curr_command[curr_command_len-1] = '\0';	
	curr_command_len = strlen(curr_command);
}

//returns the current command type
int currentCommand(){
	switch(curr_command[0]){
		case '@':
			return A_COMMAND;
			break;
		case '(':
			printf("%d\n", curr_command_len);
			for(int i=0 ; i < curr_command_len ; i++){
				if(curr_command[i] == ')')
					return L_COMMAND;
			}
			break;
		default :
			return C_COMMAND;
			break;
	}
	return UNKNOWN_COMMAND;
}

// returns the symbol in the current command
uint16_t symbol(){
	/*char *curr_symbol = malloc(50);

	if(curr_command_type == A_COMMAND){
		strcpy(curr_symbol,curr_command+1);
	}else if(curr_command_type == L_COMMAND){
		strncpy(curr_symbol, curr_command+1,curr_command_len-2);
	}
	return curr_symbol;*/
	uint16_t curr_symbol = 0;
	if(curr_command_type == A_COMMAND){
		curr_symbol = (uint16_t)atoi(curr_command+1);
	}
	return curr_symbol;
}

// returns the current destination mentioned in the control command
char* parser_dest(){
	char* dest = malloc(4);
	int equals_index = 0;

	for(;(equals_index < curr_command_len) && (curr_command[equals_index] != '=') ; equals_index++);
	if(equals_index == curr_command_len){
		free(dest);
		return NULL;
	}
	strncpy(dest , curr_command , equals_index);
	return dest;
}

char* parser_comp(){
	char* comp = calloc(10,1);
	int equalto_index = -1 ,semi_colon_index= curr_command_len ;
	for(int i=0; i < curr_command_len ; i++){
		if(curr_command[i] == '=')
			equalto_index = i;
		else if(curr_command[i] == ';')
			semi_colon_index = i;
	}

	strncpy(comp , curr_command+equalto_index+1 , semi_colon_index - equalto_index - 1);
	//printf("%d , %d\n", end_index - start_index +1 , strlen(comp) );
	return comp;
}

char* parser_jump(){
	char* jump = malloc(4);
	int semi_colon_index = 0;
	for(;(semi_colon_index < curr_command_len) && (curr_command[semi_colon_index] != ';') ; semi_colon_index++);
	if(semi_colon_index == curr_command_len){
		free(jump);
		return NULL;
	}
	strcpy(jump , curr_command+semi_colon_index+1);
	return jump;
}
