#include "code.h"

void code_dest(char *dest){
	int16_t mask = 0xffc7;
	int16_t a_mask = 0x0020;
	int16_t d_mask = 0x0010;
	int16_t m_mask = 0x0008;

	binary_command &= mask;
	if(dest){
		if(strcmp(dest , "AMD") == 0){
			binary_command = binary_command | a_mask | d_mask | m_mask;
			CODE_DEBUG("Given dest : AMD\n");
			return;
		}
		if(strcmp(dest , "AM") == 0){
			binary_command = binary_command | a_mask | m_mask;
			CODE_DEBUG("Given dest : AM\n");
			return;
		}
		if(strcmp(dest , "MD") == 0){
			binary_command = binary_command | m_mask | d_mask;
			CODE_DEBUG("Given dest : MD\n");
			return;
		}
		if(strcmp(dest,"AD") == 0){
			binary_command = binary_command | a_mask | d_mask;
			CODE_DEBUG("Given dest : AD\n");
			return;
		}
		if(strcmp(dest,"A") == 0){
			binary_command = binary_command | a_mask;
			CODE_DEBUG("Given dest : A\n");
			return;
		}
		if(strcmp(dest,"M") == 0){
			binary_command = binary_command | m_mask;
			CODE_DEBUG("Given dest : M\n");
			return;
		}
		if(strcmp(dest,"D") == 0){
			binary_command = binary_command | d_mask;
			CODE_DEBUG("Given dest : D\n");
			return;
		}

		fprintf(stderr, "Unrecognised destination.\n");
		return;
	} 
	CODE_DEBUG("No destination specified.\n");
	return;

}

void code_comp(char* comp){
	int16_t inital_mask = 0x003f;
	int16_t start_3bit_mask = 0xe000;

	binary_command = binary_command & inital_mask;
	binary_command = binary_command | start_3bit_mask;

	int comp_id = -1;
	for(int i=0 ; i < sizeof(comp_map)/sizeof(comp_map[0]) ; i++){
		//CODE_DEBUG("i=%d\t%s\n",i,comp_map[i].comp);
		if(strcmp(comp,comp_map[i].comp) == 0){
			comp_id = i;
			break;
		}
	}
	if(comp_id == -1){
		fprintf(stderr, "Not a valid comp command , comp = %s , comp_len = %ld\n" , comp , strlen(comp));
		return ;
	}

	binary_command = binary_command | comp_map[comp_id].comp_mask;
	//printf("Used mask : %04x\n" , comp_map[comp_id].comp_mask);

	return;



}

void code_jump(char* jump){
	int16_t inital_mask = 0xfff8;
	binary_command = binary_command & inital_mask;
	int jump_id = -1;

	if(!jump)
		return;

	for(int i=0; i < sizeof(jump_map)/sizeof(jump_map[0]) ; i++){
		if(strcmp(jump , jump_map[i].jump) == 0){
			jump_id = i;
			break;
		}
	}
	if(jump_id == -1){
		fprintf(stderr, "Not a valid jump command\n");
		return;
	}

	binary_command = binary_command | jump_map[jump_id].jump_mask;
	CODE_DEBUG("Used the mask : %4x\n", jump_map[jump_id].jump_mask );
	return;
}