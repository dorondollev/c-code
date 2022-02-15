/*********************************************************************
  L.A.

  Prg name        : transmit.c

  Function     : dialog AV8500 <----> Tashlumat


  Flat programme, only one function except main ???




  Date de creation : 21.02.1999
  by A.Dinur  &  Y.Refaely @ Malam.Systems


***********************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <unistd.h>

#define TIMEOUT 50   /* wait TIMEOUT secs */
#define FALSE 0
#define TRUE 1

char flag_timeout;      /* timeout flag */
char flag_rec = FALSE;
char buff_rx[600];
char code_rx[5] = '\0';
char buff_tx[600];
char expect_code[600];
char c,c_rx = '\0';
char nl = 0x0a;
char cr = 0x0d;
char result[600];
int  size;
int  i = 1;
int  ttyfd;
int  res = 0;

void gest_timeout();      /* timeout function */
void readcom();
void sendmessage(char *messg);
void open_closetashlumat(char *messg);
void sendlogicok();
void sendtashlumat();
char checkresult();
char substr(char *str,int start,int numb,char *outstr);

void transmit (strin, rest)
char* strin;
char* rest;
{
	char code[2];
	char temp_code[5];
	int  trans_cod;
	FILE *ordfile;

    substr ( strin,0,1,code );
    trans_cod = atoi ( code );
    substr ( strin,1,4,expect_code );
    size = strlen ( strin ) -5;
    substr ( strin,5,size,buff_tx );
    rest[0]=0;
/*    ordfile = fopen ("/users/a0elina/proc/ordfd.lis","w"); */
    ttyfd = open ("/dev/term/0",O_RDWR);
/*           sprintf(result,"%s","    3NOANSWER"); */
/*           strcpy ( rest,result ); */
/*           fprintf(ordfile,"ttyfd=%d rest=%s result=%s\n",ttyfd,rest,result); */
/*           fprintf(ordfile,"%s\n","1st    3NOANSWER"); */
/*                        fclose(ordfile); */
/*           return; */
	if (ttyfd == -1)
    {
		sprintf(result,"%s","    3NOANSWER");
		strcpy ( rest,result );
		return;
	}

	printf("test");
/* Use Cuid*/
	system("/usr/bin/stty raw 4800 cs7 parenb -echo -parodd < /dev/term/0");

	switch (trans_cod)
	{
		case 2:                                 /* Money RETURN    */
			trans_cod = 1;
			break;
		case 4:                                 /* Caspomat CLOSE */
			trans_cod = 3;
			break;
	}

	switch ( trans_cod )
	{
		case 1:                                 /* Money PAY */
			sendtashlumat();
			if ( res == 1 )
			{
				sleep(2);
				sendlogicok();
			}
			break;
		case 3:                                 /* Caspomat OPEN */
			open_closetashlumat ( buff_tx );
			break;
		case 5:                                 /* Caspomat STATUS */
			sendtashlumat();
			break;
	}

	if ( flag_rec == FALSE )
		sprintf ( result,"%s","    3NORESPONSE" );
	strcpy ( rest,result );

    close ( ttyfd );

    return ;
}
/**********************************************************************/
/* Set flag timeout */

void gest_timeout()
{
	flag_timeout = TRUE;
}
/********************************************************/
/*      SEND Tashlumat                                  */

void sendtashlumat()
{
	if ( size != 0 )
		sendmessage ( buff_tx );

	flag_timeout = FALSE;
	alarm ( TIMEOUT );
	signal ( SIGALRM, *gest_timeout );
	i = 0;
	do
	{
		sprintf ( result,"%s","    0" );
		readcom();
		code_rx[0] = '\0';
		substr ( buff_rx,0,4,code_rx );
		res = checkresult ();
	}
	while ( flag_timeout == FALSE );
}
/****************************************************************/
/*      Read communication                                      */

void readcom()
{
	buff_rx[0] = '\0';
	i = 0;
	do
	{
		read ( ttyfd,&c_rx,1 );
		buff_rx[i++] = c_rx;
		if ( i > 1 )
		flag_rec = TRUE;
	}
    while ( c_rx != 0x0d && flag_timeout == FALSE );
    read ( ttyfd,&c_rx,1 );
    buff_rx[--i] = '\0';
}
/**********************************************************************/
/*      Send message    */

void sendmessage(char *messg)
{
	write(ttyfd,messg,strlen(messg));
	write(ttyfd,&cr,1);
	write(ttyfd,&nl,1);
}

/**********************************************************************/
/*   String function    */

char substr(char *str,int start,int numb,char *outstr)
{
    int i,j = 0;
    int ret;

    for ( i = 0; i < numb; i++ )
    {
		if ( str[start+i] == '\0' )
		{
			return;
		}
		outstr[j++] = str[start+i];
	}
	outstr[j] = '\0';
}

/****************************************************************/
/*      OPEN or CLOSE Tashlumat                                         */

void open_closetashlumat(char *messg)
{
	sendmessage ( messg );
	flag_timeout = FALSE;
	alarm ( TIMEOUT );
	signal ( SIGALRM, *gest_timeout );
	do
	{
		readcom();
		code_rx[0] = '\0';
		substr(buff_rx,0,4,code_rx);
		res = checkresult();
	}
	while ( flag_timeout == FALSE );
}

/**********************************************************************/

char checkresult()
{
	if ( strcmp ( code_rx,expect_code ) == 0 )
    {
		size = strlen ( buff_rx );
		if ( size > 4 )
        {
			sprintf ( result,"%s","    1" );
			buff_rx[size] = '\0';
			strcat ( result,buff_rx );
		}
        else
        {
			sprintf ( result,"%s","    1NOSTRING" );
		}
		flag_timeout = TRUE;
		return 1;
	}
	else
	{
		sprintf ( result,"%s","    4NOCOMPATIBLE" );
		return 0;
	}
}

/*********************************************************************/

void sendlogicok()
{
	char mess1[20] = "000811";
    char oper[5];
    long i;
	substr ( buff_rx,10,4,oper );
	strcat ( mess1,oper );
	strcat ( mess1,"00" );
	strcat ( mess1,oper );
    for ( i = 0; i < 1000000 ; i++ );
		sendmessage ( mess1 );
}
