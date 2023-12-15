#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
using namespace std;

struct data
{
  char charData[10];
  int num;
};

int main()
{

 char filename[13]="/tmp/my_file";

 int fd=open(filename, O_RDONLY); 

 data s;
 read(fd, &s, sizeof(data));
 close(fd);
 cout<<"The string sent by the server is: "<<s.charData<<endl;
 cout<<"The number sent by the server is: "<<s.num<<endl;


}


