#include "common.h"

void symbol_table_constructor(){
	symbol_table.symbol_count = 0;
	
	add_symbol_table_entry("SP",0);
	add_symbol_table_entry("LCL",1);
	add_symbol_table_entry("ARG",2);
	add_symbol_table_entry("THIS",3);
	add_symbol_table_entry("THAT",4);
	add_symbol_table_entry("R0",0);
	add_symbol_table_entry("R1",1);
	add_symbol_table_entry("R2",2);
	add_symbol_table_entry("R3",3);
	add_symbol_table_entry("R4",4);
	add_symbol_table_entry("R5",5);
	add_symbol_table_entry("R6",6);
	add_symbol_table_entry("R7",7);
	add_symbol_table_entry("R8",8);
	add_symbol_table_entry("R9",9);
	add_symbol_table_entry("R10",10);
	add_symbol_table_entry("R11",11);
	add_symbol_table_entry("R12",12);
	add_symbol_table_entry("R13",13);
	add_symbol_table_entry("R14",14);
	add_symbol_table_entry("R15",15);

	add_symbol_table_entry("SCREEN",16384);
	add_symbol_table_entry("KBD",24576);
	return;
}

void add_symbol_table_entry(char *symbol , uint16_t address){
	//symbol_table.entry[symbol_table.symbol_count].symbol[49] = '\0';
	strcpy(symbol_table.entry[symbol_table.symbol_count].symbol,"");
	strncat(symbol_table.entry[symbol_table.symbol_count].symbol , symbol , 49);
	symbol_table.entry[symbol_table.symbol_count].address = address;
	symbol_table.symbol_count = symbol_table.symbol_count + 1;
	return;
}

int contains(char *symbol){
	int count = symbol_table.symbol_count;
	for(int i = 0; i < count ; i++){
		if(strcmp(symbol , symbol_table.entry[i].symbol) == 0){
			return 1;
		}
	}
	return 0;
}

uint16_t get_address(char *symbol){
	int count = symbol_table.symbol_count;
	uint16_t address = 0;
	for(int i = 0; i < count ; i++){
		if(strcmp(symbol , symbol_table.entry[i].symbol) == 0){
			address = symbol_table.entry[i].address;
			return address;
		}
	}
	return address;	
}