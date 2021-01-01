#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	 int *result = malloc(sizeof(int));
	 int a=1;
	 int b=2;
         int ret = syscall(334,a,b, result);
         printf("System call sys_cs3753_add returned %d\n", ret);
         printf("Result is %d\n", *result);
	 return 0;
}
