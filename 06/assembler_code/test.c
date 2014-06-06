#include "common.h"
#include<inttypes.h>

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
printf("Binary representation : %s\n", s);
}

int main(int argc , char* argv[]){
	code_comp(argv[1]);
	//printf("Hex representation :  ");
	toBinary(binary_command);
	return 0;
}