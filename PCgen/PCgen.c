/*******************************************************************************
* File Name          : PCgen.c
* Date First Issued  : 05/26/2024
* Board              : 
* Description        : Generate C code for inclusion in STM32 routine
*******************************************************************************/
/*
make && ./PCgen --file ../filters/CANbridge3x3.txt test.c
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

//#include "common_can.h"
#include "can-bridge-filter.h"
#include "can-bridge-filter-lookup.h"
#include "can-bridge-filter_test.h"
#include "CANid-hex-bin.h"


void psout(char* p);

FILE* fp;
FILE* fpout;

const char* pheader1 = "/****************************************\n";
const char* pheaderA = " * can-bridge-filter table generation file\n";
const char* pheader2 = " ***************************************** */\n";

const char* pincludes = "#include <stdint.h>\n#include \"can-bridge-filter.h\"\n";

/*******************************************************************************
 * int main(int argc, char **argv);
 * @brief   : Run some hard coded tests
*******************************************************************************/
int main(int argc, char **argv)
{
	struct CBF_TABLES* pcbf;
	struct CBFNxN* pbnn;
	int i,j,k;
	char pout[128];

	/* Command line:
   can-bridge -f <path/file>
*/
	if (argc < 3)
	{
		printf("Number of arguments err: %d\n",argc);
		exit(1);
	}
	if (strcmp(argv[1],"--file") != 0)
	{ 
		printf("ERR cmdline: 1st arg expected is --file\n");
		exit(1);
	}
	if ((fp=fopen(argv[2],"r")) == NULL)
	{
		printf("ERR cmdline: INPUT file %s did not open\n",argv[2]);
		exit(1);
	}
	if ((pcbf=can_bridge_filter_init(fp)) == NULL)
	{
		printf("ERR: bridging file %s set up failed\n",argv[2]);
		exit(1);
	}
/* Here, tables have been loaded. Start output file. */
	if ((fpout=fopen(argv[3],"w")) == NULL)
	{
		printf("ERR cmdline: OUTPUT file %s did not open\n",argv[3]);
		exit(1);
	}

/* Convert to C statements. */
	 sprintf(pout,"%s",pheader1); psout(pout);
	 sprintf(pout,"%s",pheaderA); psout(pout);
	 sprintf(pout," * %s\n",argv[3]); psout(pout);
	 sprintf(pout,"%s",pheader2); psout(pout);
	 sprintf(pout,"%s", pincludes); psout(pout);
	int N = pcbf->n;
	pbnn = pcbf->pnxn;
	struct CBF2C* p2c = pbnn->p2c;
	uint32_t* p1c = pbnn->p1c;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
//			 sprintf(pout,"cbfnn2c%i%i:\n",(i+1),(j+1)); psout(pout);
			if (pbnn->size_2c > 0)
			{
				 sprintf(pout,"const struct CBF2C cbfnn2c_%i%i[] = {\n",(i+1),(j+1)); psout(pout);
				for(k = 0; k < pbnn->size_2c; k++)
				{
					 sprintf(pout,"\t{ 0x%08X, 0x%08X},\n",p2c->in,p2c->out); psout(pout);
					p2c += 1;
				}
				 sprintf(pout,"};\n"); psout(pout);
			}
			if (pbnn->size_1c > 0)
			{
				 sprintf(pout,"const uint32_t cbfnn1c_%i%i[] = {\n",(i+1),(j+1)); psout(pout);
				for(k = 0; k < pbnn->size_1c; k++)
				{
					 sprintf(pout,"\t0x%08X,\n",*p1c); psout(pout);
					p1c += 1;
				}
				 sprintf(pout,"};\n"); psout(pout);
			}
			pbnn += 1;
			p2c = pbnn->p2c;
			p1c = pbnn->p1c;			
		}
	}
		/* All tables have been generated. Print struct array with pointers. */
	pbnn = pcbf->pnxn;
//	 sprintf(pout,"NxN:\n"); psout(pout);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			 sprintf(pout,"const struct CBFNxN cbnxn%i%i = ",(i+1),(j+1));psout(pout);
			if (pbnn->size_2c == 0)
			{ // Here, No entries in the 2c table
				if (pbnn->size_1c == 0)
				{
					 sprintf(pout," {        0,        0,"); psout(pout);
				}
				else
				{ 
					 sprintf(pout," {        0, cbfnn1c%i%i,",(i+1),(j+1)); psout(pout);
				}
			}
			else
			{
				if (pbnn->size_1c == 0)
				{
					 sprintf(pout," {cbfnn2c%i%i,        0,",(i+1),(j+1)); psout(pout);
				}
				else
				{
					 sprintf(pout," {cbfnn2c%i%i,cbfnn1c%i%i,",(i+1),(j+1),(i+1),(j+1)); psout(pout);
				}
			}
			 sprintf(pout,"  %i };\n",pbnn->type); psout(pout);
			pbnn += 1;
		}
		/* Print root struct. */
	}
	 sprintf(pout,"\nconst struct CBF_TABLES cbf = {&cbfnn[0], %i};\n",N); psout(pout);
	return 0;
}

void psout(char* p)
{
	printf("%s",p);
	fputs(p,fpout);
}
