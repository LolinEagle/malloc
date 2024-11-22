#include "../inc/malloc.h"

int	main(void){
	// Malloc
	char*	bjr = malloc(sizeof(char) * 8);
	if (!bjr){
		printf("malloc()\n");
		return (0);
	}
	bjr = "Bonjour";
	printf("%s\n", bjr);

	// Realloc
	// bjr = realloc(bjr, sizeof(char) * 22);
	// if (!bjr){
	// 	printf("realloc()\n");
	// 	return (0);
	// }
	// bjr = "Bonjour tous le monde";
	// printf("%s\n", bjr);

	// Free
	// free(bjr);
	return (0);
}
