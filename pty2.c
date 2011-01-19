#include <stdarg.h>
#ifdef WIN32
#include <windows.h>
#include <conio.h>
#include <limits.h>
#endif // WIN32

#ifdef LINUX
#include <termios.h>
#endif // LINUX

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h> 
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <termios.h> // baudrate settings are defined in <asm/termbits.h>, which is included by <termios.h> 
#include <sys/time.h>
#include <sys/stat.h> 
#include <sys/select.h>
#include <netinet/in.h>


//pseudoTY()
#include <pty.h>

//For getIP
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>


int pseudoTY(char** PTY)
{
 //char *letters;
 int master;
 int slave;

 pid_t pid = openpty(&master,&slave,NULL,NULL,NULL);//Create a pseudo terminal
 //Use ttyname() on the file descriptor to find the name of the terminal
 //That is:  slave name = ttyname(slave);

 if(pid == -1)
   {//Openpty() failed
     perror("Openpty() Failed!  :");
     return pid;
   }

 if(pid == 0)
   {//Openpty() successful
     (*PTY) = ttyname(slave);
     printf("pty name is : %s\n",(*PTY));
     // Ensure that the echo is switched off
     struct termios orig_termios;
     if (tcgetattr (master, &orig_termios) < 0)
       {
         perror ("ERROR getting current terminal's attributes");
         return -1;
       }
     orig_termios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
     orig_termios.c_oflag &= ~(ONLCR);

     if (tcsetattr (master, TCSANOW, &orig_termios) < 0)
       {
         perror ("ERROR setting current terminal's attributes");
         return -1;
       }
        return master; //Return the file descriptor
     }
}

int main()
{
 char *PTY; //Pseudo Terminal Name
 int pty = -1; //Pseudo Terminal File Descriptor
 int fdm;
 char message[6]="88888";
 char response[6]; /* receive buffer */
 FILE *input;
 FILE *output;

 pty = pseudoTY(&PTY);
 printf("the pty value is :%d\n",pty);
 if (pty < 0)
 {
  printf("cantopen,master"); //FLUSH;
 }

 fdm = open(PTY, O_RDWR | O_NOCTTY | O_NONBLOCK);
 if (fdm < 0)
 {
  printf("cantopenfile"); //FLUSH;
 }

 input = fopen(PTY, "r");      //open the terminal keyboard
 output = fopen(PTY, "w");     //open the terminal screen

 if (!input || !output)
 {
  fprintf(stderr, "Unable to open /dev/tty\n");
  exit(1);
 }

 for(;;)
 {
  fprintf(output,"88888");               //display the program introduction
  fprintf(output,"88888");
 }

 //for(;;)
 //{
 //}
 //fread(response,5,input);
 //printf("reading is finished!\n");
 //printf("the response is: %s\n",response);

 /*
 FILE* fp = NULL;
 fp  = fopen(PTY, "w" );
 if (fp == NULL)
 {
  printf("file opening failed!\n");
 }

 for(;;)
 { 
  fprintf(fp,"8888");
  sleep(1);
 }
 */

return 0;
}

