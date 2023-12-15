#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
using namespace std;

struct data
{
  char charData[10];
  int num;
};

int main()
{
 
 char filename[13]="/tmp/my_file";
 mkfifo(filename, 0666);

 int fd=open(filename,  O_WRONLY);
 
 data s;
 strcpy(s.charData, "welcome");
 s.num=10;
 write(fd, &s, sizeof(data));

 close(fd); 
}


