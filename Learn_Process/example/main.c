#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("Argc: %d\n",argc);
	for(int i=0;i<argc;i++){
		printf("Argv[%d]: %s\n",i,argv[i]);
	}
	return 0;
}
