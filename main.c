
//   File Name:		main.c
//   File Type:		source file



// main.c - performs the first scan according to the algorithm



#include "header.h"

FILE *ext;
char *ex;


char *register_table[]={
	"r0","r1","r2","r3","r4","r5","r6","r7"
		,"PSW","PC","SP","carry","zero","not_a_register_word"};



int dc,ic,ERROR;
char label_name[LABEL_LENGTH];
int ind=0,
chck_lbl,                                       //used to check labels
command_type,                                   //command type
tmp,data_zone[DATA_ZONE],code_zone[DATA_ZONE],
temp_data[80]={0},                              //holds temp lines

end_ic;
int line_address[MAXLINES],                    //holds the lines address
flag[MAXLINES],               //indicates when there's a label in a line

good_line[MAXLINES];
int there_is_extern=no,there_is_entry=no;
char colon;
char *ext_file;


struct commands {
	char *code;
	char *command;
	int num_of_operands;
	int L;  //how many words are needed for the command
} command_list[]={{"00","mov",2,-2},{"01","cmp",2,-2},{"02","add",2,-2},
				{"03","sub",2,-2},{"04","div",2,-2},{"05","mod",2,-2},
				{"06","lea",2,-2},{"07","inc",1,-1},
				{"10","dec",1,-1},{"11","jmp",1,-1},{"12","bne",1,-1},
				{"13","get",2,-2},{"14","prn",1,-1},{"15","jsr",1,-1},
				{"16","rts",0,1},{"17","hlt",0,1},{"20",'\0',0,0}};

struct label *root;


// function main gets the parameters from the command line.
// it calls for the first scan, then it rewinds the source file
// and calls the second scan function.


int main(int argc,char *argv[])

{
    FILE *ifp;
	char filename[MAX_NAME];
	char *suffix=".as";
			
	if (argc==1)
		return !OK;

	while (--argc>0)
	{
		strcpy(filename,*++argv);			//copy the file name to the array filename
		strcat(filename,suffix);			//adds suffix .as to the filename
		
		if ((ifp=fopen(filename,"r"))==NULL)
			printf("Could not open file %s\n",*argv);
		else
		{
			printf("\nAssembling %s ...",filename);
			ex=filename;
			there_is_extern=no;
		 	ERROR=no;
			first_scan(ifp);
			rewind(ifp);
			second_scan(ifp);
			build_entries_file(filename);
			if (ext!=NULL)
				fclose(ext);
			if (!ERROR)
				build_object_file(filename);
			fclose(ifp);
		}
	}
	printf("\n");
	return OK;
}








// function first_scan gets the original source file and performs
// the first scan according to the algorithm we were given (page #28)

void first_scan(FILE*ifp)
{
  char* found_label,                            //holds the label name

	  line[LINE_LENGTH];                        //holds input line
    int label,                      //checks if the label is in the line

	  answer_type=no,
	  line_counter=0;                           //counts the lines
  int num_of_data,found,
	  legal_string;          //will help to check if the string is legal

  root=NULL;

	ic=0;dc=0;		     //setting ic,dc to 0  - line #1 in algorithm
	                     //ic=instruction counter; dc=data counter

while (fgets(line,LINE_LENGTH,ifp)!=NULL)
	                            //read a line -  line #2 in algorithm
  {
		line_counter++;
		good_line[line_counter]=yes;
		flag[line_counter]=no;
		tmp=0;
		num_of_data=legal_string=yes;
		chck_lbl=no;
		found=no;
		label=no;
		ind=0;
		if (strchr(line,'\n')!=NULL)           //if '\n' appears in line
			*(strchr(line,'\n'))='\0';
		if (line[0]=='\0')
		{

			line_address[line_counter]=bad;
			continue;
		}
		       /* check if there are empty spaces or mark in the line */


		if (line[0] == ';')
			        //if the line begins with a ';' it is a remark line
		{

			line_address[line_counter]=bad;
			continue;                                 /* remark line */
		}
		while (isspace(line[ind]) && line[ind+1]!='\0')//skip spaces
			ind++;
		if (line[ind+1]=='\0')
		{
			line_address[line_counter]=bad;

			continue;                             /*all line is space */
		}
		if (line[ind]==';' && ind>0)
	         //the remark begins somewhere in the middle of the code line

		{

			good_line[line_counter]=nftfc;
			continue;
		}


		if (ind==0)
	   //checking if the first field is a flag -  line #3 in algorithm
		{
			colon=':';
			label=is_legal_label(line);
			               //checks if the first string is a legal label
			if (label==yes)    //if label!=yes then skip to line #5 in algorithm
			{
				tmp=0;
				found_label=exclude_label_from_line(line);
				if(is_a_command_or_a_register(found_label))
				{

					label=reserverd_word;
					          //illegal label - label is a reserved word

				}
				else

					{
						while (isspace(line[ind]) && line[ind+1]!='\0')
						{
							if (line[ind+1]=='\0')
								break;
			                      // there is label without any continue
							ind++;
						}
						flag[line_counter]=yes;
			             // found a legal label- line #4 in algorithm

					}
			}
		}
		command_type=has_data_or_string(line);
		  //checking if this is a virtual instruction - .data or .string
	                                        	// line #5 in algorithm

		if (command_type==data || command_type==string)
			                                  //fifth line in algorithm
				                             //if  command_type!=data || command_type!=string -> then skip to line #8
		{
			chck_lbl=no;
			line_address[line_counter]=dc;
			if(command_type==data)
			{
				if (flag[line_counter]==yes)
					                      //insert label with dc address
				root=add_label_to_label_table(root,found_label,dc,"data");
				num_of_data= is_legal_data(line);
				if (num_of_data)
					store_data(num_of_data);
				else
				good_line[line_counter]=bad_numbers;
			}
			else		                          //command_type==string
			{
				if (flag[line_counter]==yes)
					        //if there's a symbol -  line #6 in algorithm

					root=add_label_to_label_table(root,found_label,dc,"data");
				                 // add the label to table with dc value
				legal_string=is_a_legal_string(line);
				                       //checking if the .string is legal
				if (legal_string==yes)
					save_str(line);
				else
					good_line[line_counter]=legal_string;
			}
			if(chck_lbl)
				label=chck_lbl;
			if(label>yes)
				good_line[line_counter]=label;
			continue;     //back to line #2 in algorithm
		}
		answer_type = check_if_extrn_or_entry(line); //line #8 in algorithm
	  if (answer_type==extrn || answer_type==entry)
		  // if (answer_type!=extrn || answer_type!=entry)->then skip to  line #11 in the algorithm.
	  {
			line_address[line_counter]=bad;
			chck_lbl=no;
			while (!isspace(line[ind]))
				ind++;
			while (isspace(line[ind]))              //skip declarations
				ind++;
	    tmp=ind;
			colon='\0';
			label=is_legal_label(line);
			if (label==yes)
			{
				found_label=exclude_label_from_line(line);
				if(is_a_command_or_a_register(found_label))
					label=reserverd_word;

				else

					{
						if (answer_type==extrn)  //line #9 in algorithm
						{
							root=add_label_to_label_table(root,label_name,0,"extr");
							//add the label to the label table.
						}
					}
			}
			if (good_line[line_counter]==yes)
				good_line[line_counter]=label;
			if (chck_lbl)
				label=chck_lbl;
			if (label>yes)
				good_line[line_counter]=label;
			continue;         //back to line #2 in algorithm.(line #10 in algorithm)

		}
    chck_lbl=no;
		if (flag[line_counter]==yes)
			root=add_label_to_label_table(root,found_label,ic,"code");
		found=find_command(line,line_counter);      //line # 12 in algorithm.
		if (found!=bad)//it's a legal command
		{
			line_address[line_counter]=ic;
			if(command_list[found].L==1)
			   ic=ic+1;
			else
				ic=ic+how_many_lines_to_save(line);
				//line #13 in algorithm.
		}
		else           //found=bad.
		{
			line_address[line_counter]=bad;

		}

		if (chck_lbl)
		label=chck_lbl;
		if (label>yes)
		  good_line[line_counter]=label;
		if (found==bad  && label<=yes)
			good_line[line_counter]=Illegel;
  	}
  end_ic=ic;
}









// function build_new_file_name get the source file name and
// creates a new file using the suffix provided as an argument


char *build_new_file_name(char *source_file,char file_name[])
{
	char *dot;                          //points to the dot in file name
	char *p;


	p=(char *) malloc(strlen(source_file)+strlen(file_name)-2);
	               //allocate memory for new file name.
                   //size of length of source name, minus 2 - the suffix
	strncpy(p,source_file,strlen(source_file));
	                          //copy to p the prefix name of source file
	dot=strchr(p,'.');
	            //find where the '.' is in the  name and advance it by 1
	++dot;
	strcpy(dot,file_name);        //add the suffix argument after the '.'
	return p;
}


// function is_legal_label checks if the label is legal-
// a legal label can begin with an alphanumeric char followed by
// letters or digits and ends with ':'
// The label must begin in first column of the line.
// Label length can not exceed 30 chars


int is_legal_label(char *line)
{
	int tmp_ind=1;
	if (strchr(line,colon)==NULL)

		return no;


	if (isalpha(line [ind]))      //if first char in line is alphanumeric
	{

		while (isalnum(line[ind]))
			              //while rest of chars are alphanumric or digits
		{
			if (tmp_ind>LABEL_LENGTH) return label_too_long;
			     //length of label can not exceed 30 chars - illegal label
			ind++;
			tmp_ind++;
			if (line[ind]==colon)return yes;
		}
		return Illegal_chars_in_label;
		                   //the chars are not alphanumeric-illegal label

	}
	else return illegal_first_char;
	                    //illegal label - first char is not alphanumeric
}









// function exclude_label_from_line - excludes the label in line and
// returns the label


char *exclude_label_from_line(char *line)
{
  int tmp_ind=0;
  ind=tmp;
  while (line[ind]!=colon)
  {                        // while we have not reached the end of label
	label_name[tmp_ind]=line[ind];
	ind++;
	tmp_ind++;
  }
  label_name[tmp_ind]='\0';
  return label_name;
}







// function add_lable gets the labels_table, the label we want to add
// to the table,it's name,type and address and returns the update table.
// If the new label is an extrenal one - it calls for the extrenal label
// file builder function.



struct label* add_label_to_label_table(struct label*p,char *lbl_name,int 
address,char* type)
{
	if (p==NULL)
	{

		p=(struct label*) malloc (sizeof(struct label));
		p->next=NULL;
		strcpy(p->label_name,lbl_name);
		p->address=address;
		p->entry=no;
		strcpy(p->type,type);
		if (!(strcmp(type,"extr")))  //if this label is an external one
		{
		  if (!there_is_extern)
	     //if this is the first external label in file - create ext file
		  {

		    there_is_extern=yes;
	        ext_file=build_new_file_name(ex,"ext");
		                      //found an external label-create ext file
		    if ((ext=fopen(ext_file,"w"))==NULL)
              printf("Can not open file %s.Openning the next file.\n\n",ext_file);
		  }


		}
	}
	else if (strcmp(p->label_name,lbl_name))
		p->next=add_label_to_label_table(p->next,lbl_name,address,type);
				else
				{
					if (!(strcmp(p->type,type)))
						chck_lbl=label_already_exists;
					else
						chck_lbl=different_type;
				}

	return p;

}







//function is_a_command_or_a_register checkes if the string is
// a reserved command or a register


int is_a_command_or_a_register(char *found_label)

{
	int list=0;
	while ((command_list[list].command)!='\0')
	{
		if	(strcmp(found_label,(command_list[list].command))==0)
			return yes;
		else
			list++;
	}
	list=0;    //the label is not a command. Checking if it's a register
	while (strcmp(register_table[list],"not_a_register_word"))
	{
		if (0==(strcmp(found_label,register_table[list])))
			return yes;
			else
			list++;
	}
	return no;

}







//function check_if_extrn_or_entry returns the type of the command
// - extern or entry or no
int check_if_extrn_or_entry(char* line)
{
	if (strstr(line,".entry")!=NULL)
		return entry;
	if (strstr(line,".extern")!=NULL)
		return extrn;
	else return no;
}






// function has_data_or_string checks if current line has '.data'
// or '.string' in it.


int has_data_or_string(char*line)
{
	if (strstr(line,".data")!=NULL)
		return data;
	if (strstr(line,".string")!=NULL)
		return string;
	return 0;
}






// function is_legal_data checks parameters on (numbers),
// in ".data" line. if one is illegal no element is saved



int is_legal_data(char*line)
{
  int mone=0,i=0,j,t,terms=0;
  char str[]=".data",data_par[LINE_LENGTH],*token,seps[]=",",*cll;
  strcpy(data_par,line);
  ind=strstr (data_par,str)-data_par+5;
  while(isspace(data_par[ind]) && data_par[ind]!='\0')
	                                 // check if rest of line is empty
	ind++;
  if (line[ind]=='\0')
	return no;
  j=strlen(line);
  for (t=ind;t<j;t++) if (data_par[t]==',')
	mone++;
  cll=strstr(data_par,".data");
  for (t=1;t<=5;cll++,++t);
  token=(strtok(cll,seps));
  while (token!=NULL)
  {
	if (is_legal_number(token))
	{
	  temp_data[i]=atoi(token);
	  terms++;
	}
	else return no;
	i++;
	token=strtok(NULL,seps);
  }
  if (mone+1==terms)
	return i;
  return no;
}





// function is_legal_number checks if the number is legal
// (with or without +/-)


int is_legal_number(char p[])
{
  int n=0,k,l=yes;
  while (isspace(p[n]))
	n++;
  if (isdigit(p[n])|| p[n]=='+' || p[n]=='-')
  {
	  k=(strlen(p));
	  n++;
	  while (n<k && isdigit(p[n]))
		n++;
	  while (n<k)
	  {
		if (isspace(p[n]))
		  n++;
		else return no;
	  }

  }
  else return no;
  return l;
}








//function store_data stores data in the data zone                 /


void store_data(int num)
{
  int i;

  for(i=0;i<num;i++,dc++)
  	data_zone[dc]=temp_data[i];


}






//function how many lines should be saved
//for the code according to the parameters in the current line of code


int how_many_lines_to_save(char*line)
{
	int ind1,ind2=0,
		total=1;
	char operand[LINE_LENGTH];
	for(ind2=0,ind1=0;ind2<2;ind2++)
	{
	    ind1=0;
		while(isspace(line[ind]))
		    ind++;
	    if (line[ind]=='@'||line[ind]=='#'||line[ind]=='*')
		    ind++;
        while(isspace(line[ind]))
		    ind++;
		while((line[ind]!=','))
		{
		    if(line[ind]==' '||line[ind]=='\0')
				break;
			operand[ind1]=line[ind];
		    ind1++;
		    ind++;
		}
	    operand[ind1]='\0';
		if (!(is_a_command_or_a_register(operand)))
		    total++;
		while(isspace(line[ind]))
		    ind++;
	    if(line[ind]==',')
			ind++;
	    else
		   return total;
	}
    return total;
}







// function is_a_legal_string checks if the string is a legal one



int is_a_legal_string(char*line)
{
  int ind1;
  char quotes='"';
  char str[]=".string";
  ind=strstr (line,str)-line+7;
  while (line[ind]!=quotes)
  {
	if (isspace(line[ind]))
	  ind++;
	else
	  return no_begin;
  }
  if (strchr(line,quotes)==strrchr(line,quotes))
	return no_end;
  ind1=strrchr(line,quotes)-line;
  while (isspace(line[ind1]))
	ind1++;
  if (line[ind1+1]=='\0')
	return yes;
  else
	return no_end;
}







// function save_str saves chars from the string into the data zone

void save_str(char*line)
{
  int current,last_char;

current =strchr (line,'"')-line;                     //the first char
last_char= strrchr(line,'"')-line;                   //the last char
  while (++current !=last_char)
  {
		data_zone[dc]= line[current];
		dc++;
  }
	data_zone[dc]=0;               // 0 indicates the end of the string
	dc++;

}








//function find_command checks if the command appears in the command
//table.if it finds the command-it returns the number of the command


int find_command(char* line,int line_counter)
{
  char comm_name[LINE_LENGTH];        //holds the command name to check
  int ind1=0,ind2=0;                              //temp indexes
  if(flag[line_counter])
  	ind=strchr(line,':')-line+1;
  else ind=0;
  while (isspace(line[ind]))
	ind++;
  while (!isspace(line[ind]) && line[ind]!='\0')
  	comm_name[ind1++]=line[ind++];
  comm_name[ind1]='\0';
  while ((command_list[ind2].command)!='\0')
  {
	if (0==strcmp (comm_name,command_list[ind2].command))
	  return ind2;
	else ind2++;
  }
  return bad;
}



