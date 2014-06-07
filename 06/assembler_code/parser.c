#include "common.h"
#include<stdlib.h>

size_t trimwhitespace(char *out, size_t len, const char *str)
{
  if(len == 0)
    return 0;

  const char *end;
  size_t out_size;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
  {
    *out = 0;
    return 1;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;
  end++;

  // Set output size to minimum of trimmed string length and buffer size minus 1
  out_size = (end - str) < len-1 ? (end - str) : len-1;

  // Copy trimmed string and add null terminator
  memcpy(out, str, out_size);
  out[out_size] = 0;

  return out_size;
}


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

	char *temp_command =  calloc(200,1);

	while(1){
		if(fgets(curr_command , 200 , input_stream) == NULL){
			free(temp_command);
			return 0;
		}
		// New code to parse the command
		strcpy(temp_command , curr_command);
		trimwhitespace(temp_command, strlen(curr_command), curr_command);
		if(strlen(temp_command) == 0){
			curr_pos = ftell(input_stream);
			continue;
		}
		char *slash_pointer = strchr(temp_command , '/');
		if(slash_pointer == NULL){
			strcpy(curr_command , temp_command);
			fseek(input_stream , curr_pos , SEEK_SET);
			free(temp_command);
			return 1;
		} else if(slash_pointer == temp_command){
			//printf("Commented line : %s\n", curr_command);
			//continue;
		} else {
			temp_command[slash_pointer -  temp_command] = '\0';
			trimwhitespace(curr_command, strlen(temp_command), temp_command);

			fseek(input_stream , curr_pos , SEEK_SET);
			free(temp_command);
			return 1;
		}
		curr_pos = ftell(input_stream);
	}
	free(temp_command);
	return 1;
}

//Loads the next command into curr_command.
void advance(){
	char *temp_command =  calloc(200,1);
	if(fgets(curr_command , 200 , input_stream) == NULL){
		fprintf(stderr, "Unable to read the next command.exiting\n" );
		exit(0);
	}
	strcpy(temp_command , curr_command);
	trimwhitespace(temp_command, strlen(curr_command), curr_command);
	char *slash_pointer = strchr(temp_command , '/');
	//printf("Line read : %s\n", curr_command);
	if(slash_pointer == NULL){
		strcpy(curr_command , temp_command);
		curr_command_len = strlen(curr_command);
		//printf("Current command in advance : %s\n", curr_command);
	} else {
		temp_command[slash_pointer -  temp_command] = '\0';
		trimwhitespace(curr_command, strlen(temp_command), temp_command);
		//printf("Current command in advance : %s\n", curr_command);
		curr_command_len = strlen(curr_command);
	}
	free(temp_command);
	return;
}

//returns the current command type
int currentCommand(){
	switch(curr_command[0]){
		case '@':
			return A_COMMAND;
			break;
		case '(':
				return L_COMMAND;
			break;
		default :
			return C_COMMAND;
			break;
	}
	return UNKNOWN_COMMAND;
}

// returns the symbol in the current command
uint16_t symbol(){
	uint16_t curr_symbol = 0;
	
	if(curr_command_type == A_COMMAND){
		if(isdigit(curr_command[1])){ // Implies that the given command does not have any symbol
			curr_symbol = (uint16_t)atoi(curr_command+1);
			//printf("Does not have any symbols.\n");
		} else {
			//printf("Has symbols.\n");
			if(contains(curr_command+1)){
				return get_address(curr_command+1);
			} else {
				//printf("adding symbol : %s, value : %" PRId16 "\n",curr_command+1 , ram_number );
				add_symbol_table_entry(curr_command+1 , ram_number);
				ram_number = ram_number+1;
				return ram_number-1;
			}
		}
		
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
	strcpy(dest,"");
	strncat(dest , curr_command , equals_index);
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

	strcpy(comp,"");
	strncat(comp , curr_command+equalto_index+1 , semi_colon_index - equalto_index -1);
	//printf("%d , %d\n", end_index - start_index +1 , strlen(comp) );
	//printf("curr_command = %s , comp = %s\t",curr_command ,comp );
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
	strcpy(jump,"");
	strcat(jump , curr_command+semi_colon_index+1);
	return jump;
}
