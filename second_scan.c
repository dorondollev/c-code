/****************************************************************
*   File Name:		second_scan.c                   	 		*   
*   File Type:		source file				                    *
*****************************************************************/


/*-------------------------------------------------------------------*/
/* The function performs the second scan according to the algorithm  */
/* and creates the as file                                           */
/*-------------------------------------------------------------------*/


#include "header.h"


extern int dc,ic,                      //data instruction counters
end_ic,                                //last ic line
ERROR;
extern char label_name[LABEL_LENGTH ];        //holds the label names
extern int ind,tmp,
data_zone[DATA_ZONE],code_zone[DATA_ZONE];     //data and code zones
extern int there_is_extern,there_is_entry,
		   good_line[MAXLINES],                  //legal lines
		   flag[MAXLINES],           //indicates that a line has a label
		   line_address[MAXLINES];               //lines address
extern char colon;



enum {no_exist=-200,fn_register,bad_num_oper,bad_for_one,bad_for_one2,fn_direct_for_one,
            fn_number_for_one,bad_for_two,fn_number_for_two,bad_second,fn_reg_leb_for_one
			,fn_lab_for_one,fn_direct_for_two};


extern char *register_table[],*ex;

extern struct commands {
	char *code;
	char *command;
	int num_of_operands;
	int L;
} command_list[];

extern struct label *root;
int exist                             //used to check if a label exists
,f,
external[DATA_ZONE],                    //external commands
relocatable[DATA_ZONE];                       //realocatable parameters
extern FILE *ext;
char *is_data;

/*********************************************************************/
/*      performs the second scan according to the algorithm          */
/*********************************************************************/

void second_scan(FILE *ifp)
{
	 
  char *found_label,
	  line[LINE_LENGTH];
  int command_ind,
	  line_counter=0,//line counter
	  answer_type,two,one,i,l=0,a1;
  struct label *root1=root; 

  for (i=0;i<DATA_ZONE;external[i]=relocatable[i]=0,i++);
                                             //perform the second scan
	is_data=NULL;
	ic=0;          //first line in algorithm                                       
  while (fgets(line,LINE_LENGTH,ifp)!=NULL)   //while it`s not end of file                        
  {
	    
	    if (strchr(line,'\n')!=NULL)             //if '\n' is found, replace with '\0'
			*(strchr(line,'\n'))='\0';

		++line_counter;
		ind=0;

		if (line[ind]=='\0')					//no information
			continue;
		if (line[ind]==';')						//remarks->skip
			continue;
		
		while (line[ind]!='\0')
		{
			if (isspace(line[ind]))             //this is an empty line
			ind++;
			else 
				break;
		}
		if (line[ind]=='\0')					//line contains only white spaces->skip
			continue;                                               
		
		if ((good_line[line_counter])!=yes)		//an error was found during first scan
		{
			if (good_line[line_counter]!=different_type && good_line[line_counter]!=label_already_exists)
			{         // the error is not because of a reoccurring type 
				if ((command_ind=find_command(line,line_counter))!=bad)
				{                         //continue with increasing ic
		 			if(command_list[command_ind].L==1)
			           ic=ic+1;
		        	else 
				        ic=ic+how_many_lines_to_save(line);
				}
								          //command is unknown
				print_error(line_counter,good_line[line_counter]);
				continue;
			}		
		}

		if (has_data_or_string(line)) //line #4 in algorithm
			continue;                                              
		
		answer_type = check_if_extrn_or_entry(line);

		if (answer_type==extrn || answer_type==entry) //line #5 in algorithm    
			                                       //extern  or entry
	  {
			if (answer_type==entry)    //line #6 in algorithm 
			{
				there_is_entry=yes;
				ind=strstr(line,".entry")-line+7;
				while (isspace(line[ind]))
				ind++;
				tmp=ind;
				colon='\0';
				found_label=exclude_label_from_line(line);
				exist=yes;
				root=does_entry_label_exist(found_label,root);
				if (!exist)
					print_error(line_counter,no_exist);
			}
			continue;               //end of line 6 in second algorithm
		}                                     //if there is a command
		
		if ((command_ind=find_command(line,line_counter))==bad)		
			continue;				//end of third line in algorithm	                           
        
		code_zone[ic]=command_ind*8*8*8*8;                  
	
		if (num_of_operands(command_ind,line)==bad_num_oper)   
		{//number of operands found does not match the num of operands required by this command
			print_error(line_counter,bad_num_oper);
			if(command_list[command_ind].L==1)
			   ic=ic+1;
			else 
				ic=ic+how_many_lines_to_save(line);
			                                  // line #9 in algorithm
			continue;
		}
	
		if (command_list[command_ind].num_of_operands==1)
			                                    //a one operand command
		{
			one=one_oprand(command_ind,line);	
			if (one<no)							//an error was found
				print_error(line_counter,one);
		}
	
		if (command_list[command_ind].num_of_operands==2)
			                                     //a two operand command
		{
			a1=ind;
			two=two_oprand(command_ind,line);
			ind=a1;
			if (two<no)							//an error was found
				print_error(line_counter,two);
		}
		if (flag[line_counter]==yes)
			                                //line #11 in algorithm
		{
			if (good_line[line_counter]==different_type || good_line[line_counter]==label_already_exists)
			print_error(line_counter,good_line[line_counter]);
		}
		if(command_list[command_ind].L==1)
			   ic=ic+1;
		else 
			ic=ic+how_many_lines_to_save(line);   
		                                       // line #9 in algorithm
			                                                      
	} 
}

/*********************************************************************/
/*      function build_entries_file builds an entry file (*.ent)     */	
/*********************************************************************/

void build_entries_file(char *argv)
{
  FILE *ent;	
  char *entries;
	if (there_is_entry)
  {
	entries=build_new_file_name(argv,"ent");
		if ((ent=fopen(entries,"w"))==NULL)
			printf("Can not open file %s,for the entries \n",entries);
		else
		{
			print_entries_file(root,ent);        //write into the file
			fclose(ent);
		}
  }
}

/*********************************************************************/
/* function print_entries_file writes the entry information into     */
/* the entry file built by the previous function build_entries_file  */
/*********************************************************************/


void print_entries_file(struct label*p,FILE* fp)
{
	if (p!=NULL)
	{
	  if (p->entry)
		{		
			if (!(strncmp(p->type,"data",4)))
				fprintf(fp,"%-30s %4o\n",p->label_name,p->address+end_ic);
			else
				fprintf(fp,"%-30s %4o\n",p->label_name,p->address);
		}
		print_entries_file(p->next,fp);
	}
}

/*********************************************************************************/
/* print_externals_file writes information into the external labels file (*.ext) */
/*********************************************************************************/



void print_externals_file(char* name_of_ext)
{
	if (ext!=NULL)
		fprintf(ext,"  %-30s     %4o\n",name_of_ext,ic+1);
		
	
}

/*********************************************************************/
/* function does_entry_label_exist checks if an entry label exists   */
/*********************************************************************/

struct label* does_entry_label_exist (char* ll,struct label*p)
{
  if (p==NULL)
	exist=no;
  else
	if(strcmp(p->label_name,ll))
	  p->next=does_entry_label_exist(ll,p->next);
	else
	  p->entry=yes;
	return p;
}

/*********************************************************************/
/* function num_of_operands counts the number of operands by counting*/
/* the number of commas between the operands                         */
/*********************************************************************/

int num_of_operands(int found,char* line)
{
  int a1;
  int commas=0,                                          //counts the ','
	  there_is_operand=no,                      //check operand after ','
	  oper=no;                                         //num of operands
  a1=strstr(line,command_list[found].command)-line+strlen(command_list[found].command);
  while (line[a1]!='\0')
  {
  	if  (line[a1]==',')
	  commas++;
	if (!isspace(line[a1]))
	  there_is_operand=yes;
	a1++;
  }
  oper=commas+there_is_operand;
  if (command_list[found].num_of_operands!=oper)
	return bad_num_oper;
  else
	return oper;
}

/**********************************************************************/
/*function add_zero prints zeros at the number prefix to adjust length*/                                              
/**********************************************************************/

void add_zero (FILE *out,int n)
{
  if (n<8)
	  fprintf(out,"00000");
	else if (n<8*8)
	  fprintf(out,"0000");
	else if (n<8*8*8)
	  fprintf(out,"000");
    else if (n<8*8*8*8)
	  fprintf(out,"00");
	else if (n<8*8*8*8*8)
	  fprintf(out,"0");
}

/*********************************************************************/
/* function one_operand handles one operand commands in source file. */
/* The function identifies the addressing type and the data and puts */
/* them in the code zone                                             */
/*********************************************************************/
	  

int one_oprand (int found,char* line)
{
  int b,r,n=ind;
  char operand_name[LINE_LENGTH ];                      //operand name
  n=strstr(line,command_list[found].command)-line+strlen(command_list[found].command);
  //find operand location
  while (isspace(line[n]))
	n++;
  switch(line[n]){
  
  case '#':                                      //immediate addressing     
	if (!strcmp (command_list[found].command,"inc")||
	    !strcmp (command_list[found].command,"dec")|| 
	    !strcmp (command_list[found].command,"jmp")||
		!strcmp (command_list[found].command,"bne")||
		!strcmp (command_list[found].command,"prn")||
		!strcmp (command_list[found].command,"jsr")) 
		return fn_direct_for_one;                            
	n++;                                                               
	b=0;
	while(line[n]!='\0')
	  operand_name[b++]=line[n++];
	  operand_name[b]='\0';
	if (!is_legal_number(operand_name))
	  return fn_number_for_one;
	code_zone[ic+1]=atoi(operand_name);
	return yes;
    break;
  case '@'://indirect addressing or indirect register addressing 2,5                                                 
	n++;                                                                 
	b=0;
	while(line[n]!='\0' && line[n]!=' ')
	  operand_name[b++]=line[n++];
	  operand_name[b]='\0';
	r=find_number_of_registers(operand_name);
	if (r==bad)                                 //it is not a register                                                          
	{
	  f=bad;                                                          
	  is_data=NULL;
	  found_label(operand_name,root);             
	  if (f==bad)
		return bad_for_one2;
	  code_zone[ic]=code_zone[ic]+2*8;
	  code_zone[ic+1]=f;
	  if (external[ic+1])
			print_externals_file(operand_name);
	  else
			relocatable[ic+1]=yes;
	
	  if (is_data)
		  code_zone[ic+1]=code_zone[ic+1]+end_ic;
	  return yes;
	}                                         //if this is a register
	else{
	      code_zone[ic]=code_zone[ic]+5*8+r;        
	      code_zone[ic+1]=r;
	      return yes;
	      break;
	}
  case'*':                                     // rational addressing 3
	  n++;
	  b=0;
      while(line[n]!='\0' && line[n]!=' ')
	      operand_name[b++]=line[n++];
	  operand_name[b]='\0';
	  f=bad;
	  found_label(operand_name,root);             
	  if (f==bad)
		  return bad_for_one;
	  code_zone[ic]=code_zone[ic]+3*8;
	  code_zone[ic+1]=f-ic;
	  if (external[ic+1])           
			print_externals_file(operand_name);
	  else                              
			relocatable[ic+1]=yes;
      return yes;
	  break;

  default:         //direct register addressing or direct addressing 1,4
	b=0;
	while(line[n]!='\0' && !isspace(line[n]))
	 operand_name[b++]=line[n++];
	operand_name[b]='\0';
	r=find_number_of_registers(operand_name);
	if (r==bad)                                  // direct addressing 1
	{
		is_data=NULL;
	  f=bad;
	  found_label(operand_name,root);
	  if (f==bad)
	  	return bad_for_one2;
	  
		code_zone[ic]=code_zone[ic]+1*8;
	    code_zone[ic+1]=f;
	 	if (external[ic+1])
			print_externals_file(operand_name);
		else
			relocatable[ic+1]=yes;
	  if (is_data)
		  code_zone[ic+1]=code_zone[ic+1]+end_ic;
	  return yes;
	}
	                                             // direct addressing 4
	if (!strcmp (command_list[found].command,"inc") ||
		!strcmp (command_list[found].command,"dec") ||
		!strcmp (command_list[found].command,"jmp") ||
        !strcmp (command_list[found].command,"bne") ||
		!strcmp (command_list[found].command,"prn") ||
		!strcmp (command_list[found].command,"jsr") )
	{                                                              
		code_zone[ic]=code_zone[ic]+4*8+r;	
	    return yes;
    }
	else
		return fn_register;
	break;
  }

}

/*********************************************************************/
/* function set_second_operand handles the second operand in the two */
/* operand commands                                                  */
/*********************************************************************/                                     
                                                                                      																						  //

int set_second_operand(int found,char* line)       
{      
int b,r2;
char ttt[80];
    while(isspace(line[ind])) 
	    ind++;
	         
	ind++;                                                                 
              
    switch(line[ind]){                 
           
	      case '#':      //immediate addressing to the second operand
	              if (strcmp(command_list[found].command,"cmp")) 
		              return fn_direct_for_two;
	              ind++;                                                  
	              b=0;
	              while(line[ind]!='\0')
	                    ttt[b++]=line[ind++];
	                    ttt[b]='\0';
	                    if (!is_legal_number(ttt))
	                        return fn_number_for_two;
	                    code_zone[ic+2]=atoi(ttt);
	                    return yes;
	                    break;
                              
		case '@': //indirect addressing or indrect register addressing
	              ind++;                                                    
	              b=0;
	              while(line[ind]!='\0' && line[ind]!=' ')
	                    ttt[b++]=line[ind++];
	              ttt[b]='\0';
	              r2=find_number_of_registers(ttt); 
	              if (r2==bad)               //this is not a register            
				  {
	                  is_data=NULL;  
	                  f=bad;
	                  found_label(ttt,root);
	                  if (f==bad)
		                 return bad_for_two;
	                  code_zone[ic]=code_zone[ic]+2*8;
	                  code_zone[ic+2]=f+end_ic;
	                  if (external[ic+2])
			              print_externals_file(ttt);
		              else
			              relocatable[ic+2]=yes;
	                  if (is_data)
		                  code_zone[ic+2]=code_zone[ic+2]+end_ic;
	                  return yes;
				  }
	              code_zone[ic]=code_zone[ic]+5*8+r2;
	              return yes;
	              break;
		case '*':                               //rational addressing
	              ind++;			 
 	              b=0;
	              while(line[ind]!='\0' && line[ind]!=' ')
			      ttt[b++]=line[ind++];
				  ttt[b]='\0';
	              is_data=NULL;  
			      f=bad;
				  found_label(ttt,root);
				  if (f==bad)											  
					  return bad_second;
				  code_zone[ic]=code_zone[ic]+3*8;
			      code_zone[ic+2]=f-ic;
				  if (external[ic+2])
					  print_externals_file(ttt);
	              if (is_data)
					  code_zone[ic+2]=code_zone[ic+2]+end_ic;
				  return yes;
				      break;
        default://direct addressing or direct register addressing 1,4
				  b=0;
			      while(line[ind]!='\0' && !isspace(line[ind]))
					  ttt[b++]=line[ind++];
				  ttt[b]='\0';
				  r2=find_number_of_registers(ttt);
				  if (r2==bad)
				  {
					  f=bad;
					  is_data=NULL;
					  found_label(ttt,root);
					  if (f==bad)
						  return bad_for_two;
					  code_zone[ic]=code_zone[ic]+1*8;
					  code_zone[ic+2]=f;
					  if (external[ic+2])
						  print_externals_file(ttt);
					  else
						  relocatable[ic+2]=yes;
	                  if (is_data)
						  code_zone[ic+2]=code_zone[ic+2]+end_ic;
					  return yes;
				  }
							
				  code_zone[ic]=code_zone[ic]+4*8+r2;
					  return yes;
                  break;
	}
}


/*********************************************************************/
/* function two_operand deals with with two operand commands.it      */
/* identifies the addressing type and the data and puts them in the  */
/* code zone                                                         */
/*********************************************************************/

int two_oprand (int found,char* line)
{
  int b,r2;
  char tmp_operand[LINE_LENGTH];
    ind=strstr(line,command_list[found].command)-line+strlen(command_list[found].command);
    while (isspace(line[ind]))
	       ind++;

    b=0;     
	switch(line[ind]){
                
    case '#':           //immediate addressing for the first operand '0'  
              ind++;                                                        
	          if (!strcmp (command_list[found].command,"lea"))
	              return fn_direct_for_one;
	
              while ((line[ind]!=',') && (!isspace(line[ind])))
	                tmp_operand[b++]=line[ind++];
              tmp_operand[b]='\0';
	          if (!is_legal_number(tmp_operand))
	                 return fn_number_for_one;
 	          code_zone[ic+1]=atoi(tmp_operand);
     
              while (isspace(line[ind])) 
  	               ind++;			
			  return (set_second_operand(found,line));
               
	case '@': // indirect addressing or indirect register addressing 2,5          
                                                                          
	        ind++;
	        b=0;
	        if (!strcmp (command_list[found].command,"lea"))
	              return fn_reg_leb_for_one;
	        while ((line[ind]!=',') && (!isspace(line[ind])))
	              tmp_operand[b++]=line[ind++];
                  tmp_operand[b]='\0';
                  r2=find_number_of_registers(tmp_operand); 
	        if (r2==bad)                    //this is not a register            
			{
	              is_data=NULL;  
	              f=bad;
	              found_label(tmp_operand,root);
	              if (f==bad)
		              return bad_for_one2;
	              code_zone[ic]=code_zone[ic]+2*8*8*8;
	              code_zone[ic+1]=f;
	              if (external[ic+1])
			          print_externals_file(tmp_operand);
	              else
			          relocatable[ic+1]=yes;
	              if (is_data)
		              code_zone[ic+1]=code_zone[ic+1]+end_ic;
			}
	        else code_zone[ic]=code_zone[ic]+5*8*8*8+r2*8*8;
            return (set_second_operand(found,line));	
    case '*':                   //first operand - rational addressing  3
          ind++;    
	      if (!strcmp (command_list[found].command,"lea"))
	            return fn_lab_for_one;
	      while ((line[ind]!=',') && (!isspace(line[ind])))
	            tmp_operand[b++]=line[ind++];
          tmp_operand[b]='\0';
	      
		  is_data=NULL;  
	      f=bad;
	      found_label(tmp_operand,root);
	      if (f==bad)
		     return bad_for_one;
	      code_zone[ic]=code_zone[ic]+3*8*8*8;
	      code_zone[ic+1]=f-ic;    
	      if (external[ic+1])
			  print_externals_file(tmp_operand);
	      if (is_data)
		      code_zone[ic+1]=code_zone[ic+1]+end_ic;
           return (set_second_operand(found,line));
   default://first operand - direct addressing 1 or direct register addressing 4 
	      
	      b=0;
	      while(line[ind]!=',' && !isspace(line[ind]))
	      tmp_operand[b++]=line[ind++];
	      tmp_operand[b]='\0';
	
	      r2=find_number_of_registers(tmp_operand);
	      if (r2==bad)                             //direct addressing
		  {
	           f=bad;
	           is_data=NULL;
	           found_label(tmp_operand,root);
	           if (f==bad)
	  		       return bad_for_one2;
	           code_zone[ic]=code_zone[ic]+1*8*8*8;
	           code_zone[ic+1]=f;
	           if (external[ic+1])
			        print_externals_file(tmp_operand);
		       else
			        relocatable[ic+1]=yes;
	           if (is_data)
		            code_zone[ic+1]=code_zone[ic+1]+end_ic;
	 
		  }
          else                            // direct register addressing
		  {
	          if (!strcmp (command_list[found].command,"lea"))
	                return bad_for_one;
	          code_zone[ic]=code_zone[ic]+4*8*8*8+r2*8*8;
		  }
            return (set_second_operand(found,line));
    }
}

/*********************************************************************/
/* function found_label finds the label location and updates if it is*/
/* a part of data or external                                        */
/*********************************************************************/
void found_label (char* ll,struct label*p)
{
char*r=p->type;  
if (p!=NULL)
  {
    
	if (!(strcmp(p->label_name,ll)))
	{
		f=p->address;
		external[ic+1]=(!(strcmp(p->type,"extr")));
		is_data=(strstr(p->type,"data"));
	}
    found_label(ll,p->next);                        //recursive call
  }
  
}

/*********************************************************************/
/*   function find_number_of_registers                               */
/*********************************************************************/

int find_number_of_registers(char* temp)
{
  int i;
  for(i=0;i<=7;i++)
  {
	if(!strcmp(register_table[i],temp))
	  return i;
  }
  return bad;
}

/*********************************************************************/
/* function print_error prints error messages into the as file       */
/*********************************************************************/

void print_error(int line_counter,int x)
{
	printf("**Error** %s(%d) - ",ex,line_counter);
	good_line[line_counter]=x;
	ERROR=yes;
	switch(x) {
		case illegal_first_char :
		  printf("First char in label is illegal\n");
			break;
		case label_too_long :
		  printf("Length of label is more than 30 characters\n");
			break;
		case Illegal_chars_in_label :
		    printf("Label has non alfa characters\n");
			break;
		case nftfc :
		    printf("Colon is not in the first column\n");
			break;
		case different_type:
			printf("Label already exists with a different type \n");
			break;
		case label_already_exists:
			printf("Label already defined \n");
			break;
			
		case reserverd_word :
			printf("Can't be a name of a command or a register\n");
			break;
		case bad_numbers :
			printf("Bad data\n");
			break;
		case no_begin :
			printf("No legal beginning to the string\n");
			break;
		case no_end :
			printf("No legal ending  to the string\n");
			break;
		
		case Illegel:
			printf("Illegel instruction\n");
			break;
		case no_exist:		
			printf("Symbol doesn't exist\n");
			break;
		case bad_num_oper:
			printf("Illegal number of operands\n");
			break;
		case  bad_for_one :
			printf("The operand must be a label\n");
		  break;
		case  bad_for_one2 :
			printf("The operand must be a label or a register\n");
		  break;
		case  fn_register :
		  printf("The operand can not be a register\n");
		  break;
         case  fn_direct_for_one :
		  printf("The operand can not  be of direct addressing\n");
		  break;
		case  fn_number_for_one :
		  printf("Operand of direct addressing must be a legal number \n");
			break;
	    case  bad_for_two:
			printf("The second operand must be a label or a register\n");
		  break; 
		case  fn_reg_leb_for_one:
		  printf("The operand can not be a register or a lebel\n");
		  break;
		case fn_lab_for_one:
		  printf("The operand can not be a label\n");
		  break;
		case fn_number_for_two:
		  printf("Second operand of direct addressing must be a legal number \n");
		  break;
		case bad_second:
		  printf("The second operand must be a label\n");
		  break;
		case fn_direct_for_two:
		  printf("Second operand can not be direct\n");
		  break;
	}
}
