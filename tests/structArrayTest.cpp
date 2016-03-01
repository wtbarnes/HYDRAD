#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct myTestStruct{
  int foo;
  double bar;
  char helloWorld[256];
  int *fooBar;
};
typedef myTestStruct MYSTRUCT;

int main()
{
  MYSTRUCT myTestStruct;
  int i,j,tot_len=10;
  myTestStruct.fooBar = new int[tot_len];
  for(j=0;j<5;j++)
  { for(i=0;i<tot_len;i++)
    {
      myTestStruct.fooBar[i] = i*i;
    }

    for(i=0;i<tot_len;i++)
    {
      printf("Entry %d=%d\n",i,myTestStruct.fooBar[i]);
    }
  }
  delete myTestStruct.fooBar;

  return 0;
}
