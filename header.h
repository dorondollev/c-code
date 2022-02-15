/********************************************************************
*   File Name:		header.h        								*   
*   File Type:		include file									*
********************************************************************/

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>	
#define OK 0
#define LINE_LENGTH 80
#define LABEL_LENGTH 30 
#define MAXLINES 10000
#define DATA_ZONE 2000
#define MAX_NAME 30

                
struct label {
	char label_name[LABEL_LENGTH ];
	int address;
	char type[4];
	int entry;
	struct label *next;
};


enum errors { bad=-1, no , yes ,different_type,label_already_exists,  
              illegal_first_char,label_too_long,Illegal_chars_in_label,
			  reserverd_word,bad_numbers,no_begin,no_end,nftfc,Illegel};

//  illegal_first_char - first char in label is illegal
//  label_too_long - label length exceeds 30 chars
//  Illegal_chars_in_label - non alphanumeric chars in label
//  reserverd_word - a reserved command name or register name
//  bad_numbers - numbers of ".data" are illegal
//  no_begin - the string that comes with ".string" has no beginning sign
//  no_end - the string that comes with ".string" has no ending sign
//  nftfc - the remark line doesn't begin in the first code column
//  illegel - the code line is any other  error message of the first scan


enum  { data=2, string , entry, extrn };

void first_scan(FILE*);
void second_scan(FILE*);
char* build_new_file_name(char *,char*);
int is_a_command_or_a_register(char*);
char* exclude_label_from_line(char*);
int is_legal_label(char*);
struct label* add_label_to_label_table(struct label*,char*,int,char*);
int has_data_or_string(char*);
int is_legal_data(char*);
void store_data(int);
int is_a_legal_string(char*);
void save_str(char*);
int find_command(char*,int);
int  num_of_operands(int,char*);
int set_second_operand(int found,char*line);
int how_many_lines_to_save(char*line);
int check_if_extrn_or_entry(char*);
int is_legal_number(char p[]);
struct label* does_entry_label_exist(char*,struct label*);
void add_zero (FILE*,int);
int two_oprand (int ,char* );
int one_oprand (int found,char* line);
void found_label (char*,struct label*p);
int find_number_of_registers(char*);
void build_entries_file(char *);
void build_object_file(char*);
void print_object_file(FILE*);
void print_entries_file(struct label*,FILE*);
void print_externals_file(char* );
void print_error(int,int);


