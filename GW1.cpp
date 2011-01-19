/*
 * GW.cpp
 *
 *  Created on: Oct 17, 2010
 *      Author: Ruyi
 */

//****************************************************************************
//
//	FILE NAME	:	GW1.cpp
//
//	This file contains the test functions and initialization functions
//	associated with the GW Module for this node
//
//	FUNCTIONS	:
//04%^
//                  Gw_Fc_Ruby
//		    Gw_Spt_Fc_File_Communication
//                  Gw_Spt_Fc_Communication
//                  Gw_Spt_Communication
//                  Gw_Sending_Datastream
//		    Gw_Sending_Request_To_SPT
//		    Gw_Test_UTC
//		    Gw_Test_Channel
//		    Gw_Test_Ed

//04%$

//
//*****************************************************************************
//*****************************************************************************
//
//	REVISION HISTORY
//



//****************************************************************************
//	INCLUDE STANDARD HEADER FILES
//****************************************************************************
#include <pthread.h>
pthread_mutex_t count_mutex;
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "all_nodes1.h"
#include <fstream>
#include <iostream>
//const char* const OUTPUT_FILE ="/opt/test/ttyUSBout";
//const char* const USBIN_FILE ="/opt/test/ttyUSBin";
const char* const USBIN_FILE ="inputusb.dat";
const char* const OUTPUT_FILE ="output.dat";

using namespace std;
struct timeval tv;
time_t rawtime;
struct tm * timeinfo;

//****************************************************************************
//	INCLUDE USER-DEFINED HEADER FILES
//****************************************************************************

//****************************************************************************
//	GLOBAL DECLARATIONS
//****************************************************************************

//****************************************************************************
//	EXTERNAL VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
//	EXTERNAL FUNCTIONS
//****************************************************************************
extern int tcpipserver (int argc, char *argv[]);
extern int tcpipclient (int argc, char *argv[]);
extern int tcpipserver1 (int argc, char *argv[]);
extern int tcpipclient1 (int argc, char *argv[]);
extern int tcpipclient2 (int argc, char *argv[]);
extern int tcpipserver2 (int argc, char *argv[]);
extern int tcpipserver3 (int argc, char *argv[]);
extern int tcpipclient3 (int argc, char *argv[]);
extern int tcpipclient4 (int argc, char *argv[]);
extern int tcpipserver4 (int argc, char *argv[]);
extern void mymemcpy( BYTE *destination, BYTE *source, BYTE counter );


//****************************************************************************
//	FUNCTION DECLARATIONS
//****************************************************************************

//	If a new module test is to be added, then its corresponding function
//	must be declared down below

//01%^		<--- This symbol facilitates finding this portion of the file

char portnumber[10];
struct thread_data
{
	char *executiontime;
	char *delaytime;
	const char *hostname;
	char *portname;
	char *commandname;
};
#define NUM_THREADS 1
struct thread_data thread_data_array[NUM_THREADS];
struct thread_data2
{
	char *gwshift;
	char *gwbunchid;
	const char *hostname;
	char *portname;
	char *gwrss;
};
#define NUM_THREADS2 0
struct thread_data2 thread_data_array2[NUM_THREADS2];


void *PrintHello1(void *threadarg)
{

   struct thread_data *my_data;
   char *hello_msg;
   my_data = (struct thread_data *) threadarg;
   hello_msg=my_data->portname;
   printf("the message is :%s!\n",hello_msg);

   char *ARGV[2];
   ARGV[1]=hello_msg;
   tcpipserver(2,ARGV);

   pthread_exit(NULL);

}

void *DataStreamReceive(void *threadarg)
{
   struct thread_data *my_data;
   char *hello_msg;
   printf("Here is data stream receive thread");
   my_data = (struct thread_data *) threadarg;
   hello_msg=my_data->portname;
   printf("the message is :%s!\n",hello_msg);

   char *ARGV[2];
   ARGV[1]=hello_msg;
   tcpipserver1(2,ARGV);
   sleep(5);

   pthread_exit(NULL);

}


void *PrintHello2(void *threadarg)
{
   struct thread_data *my_data;
   char *executiontime1;
   char *delaytime1;
   const char *hostname1;
   char *portname1;
   char *commandname1;

   my_data = (struct thread_data *) threadarg;
   executiontime1=my_data->executiontime;
   delaytime1=my_data->delaytime;
   hostname1=my_data->hostname;
   portname1=my_data->portname;
   commandname1=my_data->commandname;


   char *ARGV1[6];
   ARGV1[5]=commandname1;
   ARGV1[4]=delaytime1;
   ARGV1[3]=executiontime1;
   ARGV1[2]=portname1;
   ARGV1[1]=(char*)malloc(strlen(hostname1)+1);
   strcpy(ARGV1[1],hostname1);
   tcpipclient(6,ARGV1);

   pthread_exit(NULL);
}

void *DataStreamSend(void *threadarg)
{
   struct thread_data *my_data;
   char *executiontime1;
   char *delaytime1;
   const char *hostname1;
   char *portname1;
   char *commandname1;

   my_data = (struct thread_data *) threadarg;
   executiontime1=my_data->executiontime;
   delaytime1=my_data->delaytime;
   hostname1=my_data->hostname;
   portname1=my_data->portname;
   commandname1=my_data->commandname;

  char *ARGV1[6];
  ARGV1[5]=commandname1;
  ARGV1[4]=delaytime1;
  ARGV1[3]=executiontime1;
  ARGV1[2]=portname1;
  ARGV1[1]=(char*)malloc(strlen(hostname1)+1);
  strcpy(ARGV1[1],hostname1);
  tcpipclient1(6,ARGV1);

  pthread_exit(NULL);
}

void *DataStreamReceive2(void *threadarg)
{
   struct thread_data *my_data;
   char *hello_msg;
   printf("Here is datastreamreceive thread");
   my_data = (struct thread_data *) threadarg;
   hello_msg=my_data->portname;
   printf("the message is :%s!\n",hello_msg);

   char *ARGV[2];
   ARGV[1]=hello_msg;
   tcpipserver2(2,ARGV);

   pthread_exit(NULL);
}

void *DataStreamSend2(void *threadarg)
{

   struct thread_data2 *my_data;
   char *GWBunchID1;
   char *GWShift1;
   const char *hostname1;
   char *portname1;
   char *GWRss1;

   my_data = (struct thread_data2 *) threadarg;
   GWBunchID1=my_data->gwbunchid;
   GWShift1=my_data->gwshift;
   hostname1=my_data->hostname;
   portname1=my_data->portname;
   GWRss1=my_data->gwrss;

   char *ARGV1[6];
   ARGV1[5]=GWRss1;
   ARGV1[4]=GWShift1;
   ARGV1[3]=GWBunchID1;
   ARGV1[2]=portname1;
   ARGV1[1]=(char*)malloc(strlen(hostname1)+1);

   strcpy(ARGV1[1],hostname1);
   tcpipclient2(6,ARGV1);
   sleep(15);

   pthread_exit(NULL);
}

void *DataStreamSend3(void *threadarg)
{

   struct thread_data2 *my_data;
   char *GWBunchID1;
   char *GWShift1;
   const char *hostname1;
   char *portname1;
   char *GWRss1;

   my_data = (struct thread_data2 *) threadarg;
   GWBunchID1=my_data->gwbunchid;
   GWShift1=my_data->gwshift;
   hostname1=my_data->hostname;
   portname1=my_data->portname;
   GWRss1=my_data->gwrss;

   char *ARGV1[6];
   ARGV1[5]=GWRss1;
   ARGV1[4]=GWShift1;
   ARGV1[3]=GWBunchID1;
   ARGV1[2]=portname1;
   ARGV1[1]=(char*)malloc(strlen(hostname1)+1);

   strcpy(ARGV1[1],hostname1);
   tcpipclient3(6,ARGV1);

   sleep(15);

   pthread_exit(NULL);
}

void *DataStreamSend4(void *threadarg)
{

   struct thread_data2 *my_data;
   char *GWBunchID1;
   char *GWShift1;
   const char *hostname1;
   char *portname1;
   char *GWRss1;

   my_data = (struct thread_data2 *) threadarg;
   GWBunchID1=my_data->gwbunchid;
   GWShift1=my_data->gwshift;
   hostname1=my_data->hostname;
   portname1=my_data->portname;
   GWRss1=my_data->gwrss;

   char *ARGV1[6];
   ARGV1[5]=GWRss1;
   ARGV1[4]=GWShift1;
   ARGV1[3]=GWBunchID1;
   ARGV1[2]=portname1;
   ARGV1[1]=(char*)malloc(strlen(hostname1)+1);
   strcpy(ARGV1[1],hostname1);
   tcpipclient4(6,ARGV1);

   sleep(15);
   pthread_exit(NULL);
}//DataStreamSend4


void *DataStreamReceive3(void *threadarg)
{
   struct thread_data2 *my_data;
   char *GWBunchID3;
   char *GWShift3;
   const char *hostname3;
   char *portname3;
   char *GWRss3;

   my_data = (struct thread_data2 *) threadarg;
   GWBunchID3=my_data->gwbunchid;
   GWShift3=my_data->gwshift;
   hostname3=my_data->hostname;
   portname3=my_data->portname;
   GWRss3=my_data->gwrss;

   char *ARGV[5];
   ARGV[1]=portname3;
   ARGV[2]=GWBunchID3;
   ARGV[3]=GWShift3;
   ARGV[4]=GWRss3;
   tcpipserver3(5,ARGV);
  
   pthread_exit(NULL);
}//DataStreamReceive3

void *DataStreamReceive4(void *threadarg)
{
   struct thread_data2 *my_data;
   char *GWBunchID4;
   char *GWShift4;
   const char *hostname4;
   char *portname4;
   char *GWRss4;

   my_data = (struct thread_data2 *) threadarg;
   GWBunchID4=my_data->gwbunchid;
   GWShift4=my_data->gwshift;
   hostname4=my_data->hostname;
   portname4=my_data->portname;
   GWRss4=my_data->gwrss;
   	                              	
   char *ARGV[5];
   ARGV[1]=portname4;
   ARGV[2]=GWBunchID4;
   ARGV[3]=GWShift4;
   ARGV[4]=GWRss4;

   tcpipserver4(5,ARGV);
    
   pthread_exit(NULL);
}//DataStreamReceive4

void *FcRuby(void *threadid)
{
   unsigned char buf2[100];
   BYTE *ptr2= buf2;
   int bd=0;
   int gshift=0;
   int grss=0;
   long tid;
   int utc;
   int j;
   int counter = 0;
   char command[80];
   char icommand[1];
   tid = (long)threadid;

   if (tid==0)
    {
     cout<<"please enter GW bunchID"<<endl;
     cin>>bd;
     cout<<"please enter GW gw_shift"<<endl;
     cin>>gshift;
     cout<<"please enter GW gw_rss"<<endl;
     cin>>grss;
     FILE* fp1 = NULL;
     fp1 = fopen (USBIN_FILE, "r");
     strcpy(icommand,"i");

     for (;;)
     {
     printf("counter value is %d\n",counter);
     printf("Hello World! It's me, thread #%ld!\n", tid);
     printf("I am waiting for more commands from the clients\n");
     FILE* fp = NULL;
     fp  = fopen( OUTPUT_FILE, "w" );
 
     fgets(command,sizeof(command),fp1);
     printf("the command value is %s\n", command);
     if(strncmp(command,icommand,1))
     printf("the command is not i\n");
     else
     {
      printf("the command is  i\n");
      printf ("AMPT BOU Radio Gateway\n");
      printf("Datarate:12001 Freq2410001 Tick (mks) 200 Chan 7 # SPTs 25 bunch size 16\n");
      printf("UTC:327 663 Normal   long packets  temp 3020     shift -86 ADCs  TRUE  Power ED\n");
      printf("MAC 000000000020 E hop  FEC=0GwAddr 33  EdAddr 34\n");
      printf("Sync Word: F0F0\n");
      fprintf(fp, "AMPT BOU Radio Gateway\n");
      fprintf(fp, "Datarate:12001 Freq2410001 Tick (mks) 200 Chan 7 # SPTs 25 bunch size 16\n");
      fprintf(fp, "UTC:327 663 Normal   long packets  temp 3020     shift -86 ADCs  TRUE  Power ED\n");
      fprintf(fp, "MAC 000000000020 E hop  FEC=0GwAddr 33  EdAddr 34\n");
      fprintf(fp, "Sync Word: F0F0\n");
      continue;
     }

 if(counter%17==0)
    {
      //sending brendan's stream
      printf("=> MAC: 000000000020    Ch:     37      T:      3020    UTC:    327     ms:     584\n");
      fprintf(fp,"=> MAC: 000000000020    Ch:     37      T:      3020    UTC:    327     ms:     584\n");
      counter++;
      continue;
    }

       //sending the data stream continuously to Ruby on Rail file:
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "The current date/time is: %s", asctime (timeinfo) );
  unsigned int uiTime = static_cast<unsigned int>( time( NULL ) );
  printf(" the rawtime is:%d\n",uiTime);
  *ptr2='|';
  ptr2++;

  if (counter %2 ==0)
      {
            bd++;
            gshift++;
            grss++;
      }
  else
      {
            bd--;
            gshift--;
            grss--;
      }

  mymemcpy(ptr2,(BYTE*)&bd,1);
  ptr2++;
  mymemcpy(ptr2,(BYTE*)&gshift,1);
  ptr2++;
  mymemcpy(ptr2,(BYTE*)&grss,1);
  ptr2++;
  *ptr2='|';
  ptr2++;
  utc=rawtime;
  printf("utc value is: %d\n",utc);
  mymemcpy(ptr2,(BYTE*)&utc,4);
  ptr2=ptr2+4;
  *ptr2=0xBB;
  ptr2++;
  *ptr2=0xC3;
  ptr2++;
  *ptr2=0xBC;
  ptr2++;
  *ptr2=0x4A;
  ptr2++;
  *ptr2=0x80;
  ptr2++;
  *ptr2=0x00;
  ptr2++;
  *ptr2=0x08;
  ptr2++;
  *ptr2=0xA2;
  ptr2++;
  *ptr2=0x8D;
  ptr2++;
  *ptr2=0x02;
  ptr2++;
  *ptr2=0x3C;
  ptr2++;
  *ptr2=0x75;
  ptr2++;
  *ptr2=0x22;
  ptr2++;
  *ptr2=0x03;
  ptr2++;
  *ptr2=0xBB;
  ptr2++;
  *ptr2=0x25;
  ptr2++;
  *ptr2=0xCB;
  ptr2++;
  *ptr2=0x0B;
  ptr2++;
  *ptr2=0xAE;
  ptr2++;
  *ptr2=0x09;
  ptr2++;
  *ptr2=0x2C;
  ptr2++;
  *ptr2=0x00;
  ptr2++;
  *ptr2=0x04;
  ptr2++;
  *ptr2=0x00;
  ptr2++;
  *ptr2=0x11;
  ptr2++;
  *ptr2=0xBF;
  ptr2++;
  *ptr2=0xC8;
  ptr2++;
  *ptr2=0xB4;
  ptr2++;

  printf("server adds three more bytes :\n");
  printf("the bunch id is :%d\n",bd);
  printf("the gw shift is :%d\n",gshift);
  printf("the gw rss is :%d\n",grss);
  printf("GW appends the three bytes and generates the datastream: \n");

  j=0;
  printf("%c",buf2[j]);
  fprintf(fp,"%c",buf2[j]);
  j++;
  printf("%02X",buf2[j]);
  fprintf(fp,"%02X",buf2[j]);
  j++;
  printf("%02X",buf2[j]);
  fprintf(fp,"%02X",buf2[j]);
  j++;
  printf("%02X",buf2[j]);
  fprintf(fp,"%02X",buf2[j]);

  j++;
  printf("%c",buf2[j]);
  fprintf(fp,"%c",buf2[j]);
  j++;

  while(1)
  {
        printf("%02X",buf2[j]);
        fprintf(fp,"%02X",buf2[j]);
         j++;
        if (j==37)
          break;
  };

  ptr2=ptr2-37;
  printf("\n");
  fprintf(fp,"\n");
  counter++;
  fclose(fp);
  time_t start_time,cur_time;
  time(&start_time);

  do
	{
	    time(&cur_time);
	}
  while((cur_time-start_time)<3);
    }
  }
   pthread_exit(NULL);
}

UWORD Gw_Fc_Ruby(void);
UWORD Gw_Spt_Fc_File_Communication(void);
UWORD Gw_Spt_Fc_Communication(void);
UWORD Gw_Spt_Communication(void);
UWORD Gw_Sending_Datastream(void);
UWORD Gw_Sending_Request_To_SPT(void);
UWORD Gw_Test_UTC(void);
UWORD Gw_Test_Channel(void);
UWORD Gw_Test_Ed(void);




//01%$

//*****************************************************************************
//
//      FUNCTION:               Gw_Fc_Ruby
//
//      DESCRIPTION:    This function will Fc sending dataframes to the Ruby on rail 
//    interface
//   
//
//
//      INPUTS:                 none
//
//
//      OUTPUTS:                status - status of the function
//                                                      0 = PASS
//                                                      1 = FAIL
//
//*****************************************************************************

UWORD Gw_Fc_Ruby(void)
{
pthread_t threads[NUM_THREADS];
int rc;
long t;
for(t=0;t<NUM_THREADS;t++)
  {
  printf("In main: creating thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, FcRuby, (void *)t);
  if (rc)
    {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
pthread_exit(NULL);
}

//*****************************************************************************
//
//	FUNCTION:		Gw_Spt_Fc_File Communication
//
//	DESCRIPTION:	This function will test  communication between GW,Spt, Fc
//   ,the input file buffer and the output file buffer
//
//
//	INPUTS:			none
//
//
//	OUTPUTS:		status - status of the function
//							0 = PASS
//							1 = FAIL
//
//*****************************************************************************

UWORD Gw_Spt_Fc_File_Communication(void)
{
	UWORD	status = TEST_PASSED;
	pthread_attr_t tattr;
    string inputFileName;
    string outputFileName;
	char GWBunchID[10];
	char GW_Shift[10];
	char GW_Rss[10];
	char interface[40];

	ifstream inputFile;
	ofstream outputFile;

	cout<<"This is Sending Datastream Test\n";
	cout<<"Initializing the SPT\n";
	cout<<"please enter the port number of localhost:"<<endl;
	cin>>portnumber;//15377 can be a good one!

	pthread_t threads2[NUM_THREADS];
	thread_data_array2[0].portname=portnumber;

    cout<<"Initializing the GW and Sending the Datastream\n";
	cout<<"please enter GW bunchID"<<endl;
    cin>>GWBunchID;
	cout<<"please enter GW gw_shift"<<endl;
	cin>>GW_Shift;
	cout<<"please enter GW gw_rss"<<endl;
	cin>>GW_Rss;

	thread_data_array2[0].hostname="localhost";
	thread_data_array2[0].portname=portnumber;
	thread_data_array2[0].gwbunchid=GWBunchID;
	thread_data_array2[0].gwshift=GW_Shift;
	thread_data_array2[0].gwrss=GW_Rss;

	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
    pthread_create(&threads2[0], NULL, DataStreamReceive4,(void *) &thread_data_array2[0]);
    sleep(5);
    sleep(5);
    sleep(5);
    //The following program is to apply the delay time
    /*
	 	         time_t start_time,cur_time;
	 	       	    printf("timing1\n");
	 	       		time(&start_time);
	 	         		do
	 	     		{
	 	     			time(&cur_time);
	 	       		}
	 	       		while((cur_time-start_time)<5);
	 	       		printf("timing2\n");
    */
     pthread_create(&threads2[0], NULL, DataStreamSend4,
     (void *) &thread_data_array2[0]);
     sleep(5);
     sleep(5);
     sleep(5);
     sleep(5);
     sleep(1);
                                                         
     printf("please enter the interface name\n");
     scanf("%s",interface);
     printf("Here is the FC interface:%s \n",interface);
     pthread_join(threads2[0],NULL);

     return status;
}

//Gw_Spt_Fc_File_Communication
//*****************************************************************************
//
//	FUNCTION:		Gw_Spt_Fc Communication
//
//	DESCRIPTION:	This function will test  communication between GW,Spt and Fc
//
//
//
//	INPUTS:			none
//
//
//	OUTPUTS:		status - status of the function
//							0 = PASS
//							1 = FAIL
//
//*****************************************************************************

UWORD Gw_Spt_Fc_Communication(void)
{
	UWORD	status = TEST_PASSED;
	pthread_attr_t tattr;
	string inputFileName;
	string outputFileName;
	char GWBunchID[10];
	char GW_Shift[10];
	char GW_Rss[10];
	char interface[40];
    ifstream inputFile;
	ofstream outputFile;

    cout<<"This is Sending Datastream Test\n";
	cout<<"Initializing the SPT\n";
	cout<<"please enter the port number of localhost:"<<endl;
	cin>>portnumber;//15377 can be a good one!

	pthread_t threads2[NUM_THREADS];
	thread_data_array2[0].portname=portnumber;

    cout<<"Initializing the GW and Sending the Datastream\n";
	cout<<"please enter GW bunchID"<<endl;
	cin>>GWBunchID;
	cout<<"please enter GW gw_shift"<<endl;
	cin>>GW_Shift;
	cout<<"please enter GW gw_rss"<<endl;
	cin>>GW_Rss;

    thread_data_array2[0].hostname="localhost";
    thread_data_array2[0].portname=portnumber;
    thread_data_array2[0].gwbunchid=GWBunchID;
    thread_data_array2[0].gwshift=GW_Shift;
    thread_data_array2[0].gwrss=GW_Rss;
    pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
    pthread_create(&threads2[0], NULL, DataStreamReceive3,(void *) &thread_data_array2[0]);
    sleep(5);
    sleep(5);
     /*
      time_t start_time,cur_time;
      printf("timing1\n");
	  time(&start_time);
	  do
	  {
	  time(&cur_time);
	  }
	  while((cur_time-start_time)<5);
	  printf("timing2\n");
    */
    pthread_create(&threads2[0], NULL, DataStreamSend3,
    (void *) &thread_data_array2[0]);
    sleep(5);
    sleep(5);
    sleep(5);

    printf("please enter the interface name\n");
    scanf("%s",interface);
    printf("Here is the FC interface:%s \n",interface);
    pthread_join(threads2[0],NULL);
	return status;
}//Gw_Spt_Fc_Communication

//*****************************************************************************
//
//	FUNCTION:		Gw_Spt_Communication
//
//	DESCRIPTION:	This function will test  communication between GW and
//SPT
//
//
//	INPUTS:			none
//
//
//	OUTPUTS:		status - status of the function
//							0 = PASS
//							1 = FAIL
//
//*****************************************************************************

UWORD Gw_Spt_Communication(void)
{
   UWORD status = TEST_PASSED;
   pthread_attr_t tattr;
   string inputFileName;
   string outputFileName;
   char GWBunchID[10];
   char GW_Shift[10];
   char GW_Rss[10];
   char interface[40];

   ifstream inputFile;
   ofstream outputFile;

   cout<<"This is Sending Datastream Test\n";
   cout<<"Initializing the SPT\n";
   cout<<"please enter the port number of localhost:"<<endl;
   cin>>portnumber;//15377 can be a good one!

   pthread_t threads2[NUM_THREADS];
   thread_data_array2[0].portname=portnumber;
   pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
   pthread_create(&threads2[0], NULL, DataStreamReceive2,(void *) &thread_data_array2[0]);

   sleep(5);

   cout<<"Initializing the GW and Sending the Datastream\n";
   cout<<"please enter GW bunchID"<<endl;
   cin>>GWBunchID;
   cout<<"please enter GW gw_shift"<<endl;
   cin>>GW_Shift;
   cout<<"please enter GW gw_rss"<<endl;
   cin>>GW_Rss;

   thread_data_array2[0].hostname="localhost";
   thread_data_array2[0].portname=portnumber;
   thread_data_array2[0].gwbunchid=GWBunchID;
   thread_data_array2[0].gwshift=GW_Shift;
   thread_data_array2[0].gwrss=GW_Rss;
   pthread_create(&threads2[0], NULL, DataStreamSend2,
   (void *) &thread_data_array2[0]);

   sleep(5);

   printf("please enter the interface name\n");
   scanf("%s",interface);
   printf("Here is the FC interface:%s \n",interface);
   pthread_join(threads2[0],NULL);

   return	status;
}	// Gw_Spt_Communication

	//01%$
//*****************************************************************************
//
//	FUNCTION:		Gw_Sending_Datastream
//
//	DESCRIPTION:	This function will test Datastream communication between GW and
//SPT
//
//
//	INPUTS:			none
//
//
//	OUTPUTS:		status - status of the function
//							0 = PASS
//							1 = FAIL
//
//*****************************************************************************

	UWORD Gw_Sending_Datastream(void)
{
	UWORD	status = TEST_PASSED;
	pthread_attr_t tattr;
    string inputFileName;
    string outputFileName;
    char delay[10];
    char count[10];
	char command[10];
	char interface[40];

	ifstream inputFile;
	ofstream outputFile;

    cout<<"This is Sending Datastream Test\n";
	// sleep(5);
    cout<<"Initializing the SPT\n";
	cout<<"please enter the port number of localhost:"<<endl;
	cin>>portnumber;//15377 can be a good one!

    pthread_t threads[NUM_THREADS];
	thread_data_array[0].portname=portnumber;

    pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
    pthread_create(&threads[0], NULL, DataStreamReceive,(void *) &thread_data_array[0]);

    sleep(5);

	cout<<"Initializing the GW and Sending the Datastream\n";
	cout<<"please enter length"<<endl;
	cin>>delay;
	cout<<"please enter the edaddress"<<endl;
	cin>>count;
	cout<<"please enter the bunchID"<<endl;
	cin>>command;

    thread_data_array[0].hostname="localhost";
    thread_data_array[0].portname=portnumber;
    thread_data_array[0].delaytime=delay;
    thread_data_array[0].executiontime=count;
    thread_data_array[0].commandname=command;

    pthread_create(&threads[0], NULL, DataStreamSend,
    (void *) &thread_data_array[0]);

    printf("we are after client thread!\n");
    sleep(5);
    printf("please enter the interface name\n");
    scanf("%s",interface);
    printf("Here is the FC interface:%s \n",interface);
    pthread_join(threads[0],NULL);

	return	status;
}	// Gw_Sending_Datastream

	UWORD Gw_Sending_Request_To_SPT(void)
{
	cout<<"This is Gw_Sending_Request_To_SPT\n";
	UWORD	status = TEST_PASSED;
	pthread_attr_t tattr;
    string inputFileName;
	string outputFileName;
	char delay[10];
	char count[10];
	char command[10];
	ifstream inputFile;
	ofstream outputFile;

    cout<<"Initializing the SPT\n";
    cout<<"please enter the port number of localhost:"<<endl;
	cin>>portnumber;

	pthread_t threads[NUM_THREADS];
	thread_data_array[0].portname=portnumber;
	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
    pthread_create(&threads[0], NULL, PrintHello1,(void *) &thread_data_array[0]);

    sleep(5);

	cout<<"Initializing the GW and Sending the Datastream\n";
	cout<<"please enter the delay time"<<endl;
	cin>>delay;
	cout<<"please enter the execution time"<<endl;
	cin>>count;
	cout<<"please enter the command"<<endl;
	cin>>command;

    thread_data_array[0].hostname="localhost";
    thread_data_array[0].portname=portnumber;
    thread_data_array[0].delaytime=delay;
    thread_data_array[0].executiontime=count;
    thread_data_array[0].commandname=command;

    pthread_create(&threads[0], NULL, PrintHello2,
    (void *) &thread_data_array[0]);
    pthread_exit(NULL);

	return	status;
}	// Gw_Sending_Request_To_SPT

	UWORD Gw_Test_UTC(void)
{
	UWORD	status = TEST_PASSED;
	//	This function is used as a sample only.  It does not contain any test
	//	content
	cout<<"This is Gw UTC Test\n";
	return	status;
}	// Gw_Test_UTC

	UWORD Gw_Test_Channel(void)
{
	UWORD	status = TEST_PASSED;
	//	This function is used as a sample only.  It does not contain any test
	//	content
	cout<<"This is Gw Test Channel\n";
	return	status;
}	// Gw_Test_Channel

	UWORD Gw_Test_Ed(void)
{
	UWORD	status = TEST_PASSED;
	//	This function is used as a sample only.  It does not contain any test
	//	content
	cout<<"This is Gw Ed Test\n";
	return	status;
}	// Gw_Test_Ed

	//*****************************************************************************
	//
	//	FUNCTION:		Initialize_Gw_Menu
	//
	//	DESCRIPTION:	This function will initialize the structures for displaying
	//					and the Gw Menu for this node and will associate the menu
	//					item with a test function
	//
	//
	//	INPUTS:			none
	//
	//
	//	OUTPUTS:		none
	//
	//*****************************************************************************

	void C_test_block::Initialize_GW_Menu(void)
	{
	//	If a new test is to be added, then its corresponding structure
	//	information must be stated down below
   	//03%^		<--- This symbol facilitates finding this portion of the file
        insert_test(Gw_Fc_Ruby, "Gw Fc Ruby");
		insert_test(Gw_Spt_Fc_File_Communication,"Gw Spt Fc File Communication");
        insert_test(Gw_Spt_Fc_Communication,"Gw Spt Fc Communication");
		insert_test(Gw_Spt_Communication,"Gw Spt Communication");
		insert_test(Gw_Sending_Datastream, "Sending Datastream");
		insert_test(Gw_Sending_Request_To_SPT, "Sending_Request_To_SPT");
		insert_test(Gw_Test_UTC, "Test UTC");
		insert_test(Gw_Test_Channel, "Test Channel");
		insert_test(Gw_Test_Ed, "Test Ed");
	//03%$
	}	// Initialize_Gw_Menu
