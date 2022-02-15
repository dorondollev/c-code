/********************************************************************
*   File Name:		object.c        								*   
*   File Type:		source file										*
********************************************************************/

/*-------------------------------------------------------------------*/
/* object.c - builds the object (*.ob) file                          */
/*-------------------------------------------------------------------*/

#include "header.h"



extern int dc,ic,data_zone[DATA_ZONE],code_zone[DATA_ZONE],external[DATA_ZONE],
relocatable[DATA_ZONE];


/*********************************************************************/
/* function build_object_file builds the output object (*.ob) file   */
/*********************************************************************/

void build_object_file(char *argv)
{
  FILE *obj;
  char *object;
	object=build_new_file_name(argv,"ob");
	if ((obj=fopen(object,"w"))==NULL)
		printf("canno't open file %s\n\n",object);
	else
	{
		print_object_file(obj);
		fclose(obj);
	}
	
}	
		

/*********************************************************************/
/* function print_object_file writes all needed data into the ob file*/
/*********************************************************************/

void print_object_file(FILE* obj)
{
  int i;
  fprintf(obj,"   Octal           Octal               Absolute\n");
  fprintf(obj,"   Address:        machine             relocatable\n");
  fprintf(obj,"                   code:               or external\n");
  fprintf(obj,"\n");
  fprintf(obj,  "                    %o %o\n\n",ic,dc);
  for (i=0;i<ic;i++)
  { 
	fprintf(obj,"    ");
	if (i==0)
        add_zero(obj,64);
	else
	   add_zero (obj,(i*64)); 
	fprintf(obj,"%o            ",i);
	add_zero (obj,code_zone[i]);
	fprintf(obj,"%o              ",code_zone[i]);
	if (external[i])
		fprintf(obj,"e\n");
	else if(relocatable[i])
		fprintf(obj,"r\n");
         else fprintf(obj,"a\n");
  }

  for (i=0;i<dc;i++)
  { 
	fprintf(obj,"    ");
	add_zero (obj,((i+ic)*64));
	fprintf(obj,"%o            ",i+ic);
	add_zero (obj,data_zone[i]);
	fprintf(obj,"%o\n",data_zone[i]);
  }

}