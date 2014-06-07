#include "common.h"
#include<inttypes.h>

FILE *output_stream;

void toBinary(uint16_t x)
{
	const int bitsToDisplay = 16;
	char s[bitsToDisplay+1];
	int i=bitsToDisplay;
	s[i--]=0x00;
	do{
		s[i--]=(x & 1) ? '1':'0';
		x>>=1;
	} while( x > 0);
	while(i>=0) s[i--]='0';

	fprintf(output_stream, "%s\n", s);
	printf("\tcommand=%15s\tbinary_command = %s\n",curr_command, s);
}


int main(int argc , char *argv[]){
	
	char outputfile[250];
	strcpy(outputfile , argv[1]);
	outputfile[strlen(argv[1]) -3] = '\0';
	strcat(outputfile , "hack");

	parser_initializer(argv[1]);
	output_stream = fopen(outputfile,"w");

	if(output_stream == NULL){
		printf("Unable to open file %s\n",outputfile );
		return 0;
	}
	int loop_count = 0;
	char *dest = NULL , *comp = NULL , *jump=NULL;

	char l_address[50] ;

	rom_number = 0;
	ram_number = 16;
	
// First pass for building symbol table
	printf("BEGINNING THE FIRST PASS.\n");
	symbol_table_constructor();
	while(hasMoreCommands()){
		advance();
		curr_command_type = currentCommand();

		if((curr_command_type ==  A_COMMAND) || (curr_command_type == C_COMMAND)){
			printf("command_type = %4d\t,command=%15s\t,rom_number=%3d\n",curr_command_type,curr_command,rom_number);
			rom_number = rom_number + 1;
			continue;
		}
		if(curr_command_type == L_COMMAND){
			strcpy(l_address,"");
			strncat(l_address , curr_command+1 , strlen(curr_command)-2);
			if(!contains(l_address)){
				printf("command_type = %4d\t,command=%15s\t,rom_number=%3d\n",curr_command_type,curr_command,rom_number);
				add_symbol_table_entry(l_address , rom_number);
			}
		}
	}
	printf("END OF THE FIRST PASS\n");

	fseek(input_stream , 0 , SEEK_SET);
	while(hasMoreCommands()){
		advance();
		
		curr_command_type = currentCommand();

		//printf("loop number = %3d \t Command = %6s \t command_type = %d , command_len = %ld " , loop_count++ , curr_command , curr_command_type , strlen(curr_command));

		if(curr_command_type == A_COMMAND){
			binary_command = symbol();
		} else if (curr_command_type == C_COMMAND){
			//Calling the parser functions.
			//printf("Calling the parser functions\n");
	
			printf("curr_command = %15s\tcurr_command_len=%2d\t",curr_command, curr_command_len );
			dest = parser_dest();
			printf("dest = %s\t",dest);
			//printf("%d\n", strlen(dest));

			comp = parser_comp();
			printf("comp = %s\t",comp);
			//printf("%d\n", strlen(comp));

			jump = parser_jump();
			printf("jump = %s\n",jump);

			//Calling the code functions
			CODE_DEBUG("Calling the code functions\n");
			code_dest(dest);
			code_comp(comp);
			code_jump(jump);

			free(dest);
			free(comp);
			free(jump);
		} else if (curr_command_type == L_COMMAND){

			continue;
		}

		toBinary(binary_command);

	}

	return 0;
}