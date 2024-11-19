#include "../inc/malloc.h"
#include <stdio.h>

int	main(void){
	char*	bjr = malloc(sizeof(char) * 8);
	if (!bjr){
		printf("malloc()\n");
		return (1);
	}
	bjr = "Bonjour";
    printf("%s\n", bjr);
	bjr = realloc(bjr, sizeof(char) * 22);
	if (!bjr){
		printf("realloc()\n");
		return (1);
	}
	bjr = "Bonjour tous le monde";
    printf("%s\n", bjr);
    free(bjr);
	return (1);
}
