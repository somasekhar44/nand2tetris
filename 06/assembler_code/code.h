#include "common.h"
struct compMapStruct
{
	char comp[10];
	int16_t comp_mask;
};

struct compMapStruct comp_map[] = {
	{	"0" 	, 	0x0a80	},
	{	"1"		,	0x0fc0	},
	{	"-1"	,	0x0e80	},
	{	"D"		,	0x0300	},
	{	"A"		,	0x0c00	},
	{	"!D"	,	0x0340	},
	{	"!A"	,	0x0c40	},
	{	"-D"	,	0x03c0	},
	{	"-A"	,	0x0cc0	},
	{	"D+1"	,	0x07c0	},
	{	"A+1"	,	0x0dc0	},
	{	"D-1"	,	0x0380	},
	{	"A-1"	,	0x0c80	},
	{	"D+A"	,	0x0080	},
	{	"D-A"	,	0x04c0	},
	{	"A-D"	,	0x01c0	},
	{	"D&A"	,	0x0000	},
	{	"D|A"	,	0x0540	},
	{	"M"		,	0x1c00	},
	{	"!M"	,	0x1c40	},
	{	"-M"	,	0x1cc0	},
	{	"M+1"	,	0x1dc0	},
	{	"M-1"	,	0x1c80	},
	{	"D+M"	,	0x1080	},
	{	"D-M"	,	0x14c0	},
	{	"M-D"	,	0x11c0	},
	{	"D&M"	,	0x1000	},
	{	"D|M"	,	0x1540	}
};

struct jumpMapStruct{
	char jump[10];
	int16_t jump_mask;
};

struct jumpMapStruct jump_map[] = {
	{	"JGT"	,	0x0001	},
	{	"JEQ"	,	0x0002	},
	{	"JGE"	,	0x0003	},
	{	"JLT"	,	0x0004	},
	{	"JNE"	,	0x0005	},
	{	"JLE"	,	0x0006	},
	{	"JMP"	,	0x0007	}
};

