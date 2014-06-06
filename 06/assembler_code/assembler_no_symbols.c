#include "common.h"
#include<inttypes.h>

FILE *output_stream;

void toBinary(uint16_t x)
{
const int bitsToDisplay = 16;
char s[bitsToDisplay+1];
int i=bitsToDisplay;
s[i--]=0x00;
do
{
s[i--]=(x & 1) ? '1':'0';
x>>=1;
} while( x > 0);
while(i>=0) s[i--]='0';

fprintf(output_stream, "%s\n", s);
printf("\tbinary_command = %s\n", s);
}


int main(int argc , char *argv[]){
	
	char outputfile[250];
	strcpy(outputfile , argv[1]);
	outputfile[strlen(argv[1]) -3] = '\0';
	strcat(outputfile , "hack");

	parser_initializer(argv[1]);
	output_stream = fopen(outputfile,"w");

	int loop_count = 1;
	char *dest = NULL , *comp = NULL , *jump=NULL;
	

	while(hasMoreCommands()){
		advance();
		
		curr_command_type = currentCommand();

		printf("loop number = %3d \t Command = %6s \t command_type = %d , command_len = %ld " , loop_count++ , curr_command , curr_command_type , strlen(curr_command));

		if(curr_command_type == A_COMMAND){
			binary_command = symbol();
		} else if (curr_command_type == C_COMMAND){
			//Calling the parser functions.
			CODE_DEBUG("Calling the parser functions\n");
	
			dest = parser_dest();
			CODE_DEBUG("dest = %s\n",dest);
			//printf("%d\n", strlen(dest));

			comp = parser_comp();
			CODE_DEBUG("comp = %s\n",comp);
			//printf("%d\n", strlen(comp));

			jump = parser_jump();
			//CODE_DEBUG("jump = %s\n",jump);

			//Calling the code functions
			CODE_DEBUG("Calling the code functions\n");
			code_dest(dest);
			code_comp(comp);
			code_jump(jump);
		}
		toBinary(binary_command);

	}

	return 0;
}