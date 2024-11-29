#include "../inc/malloc.h"

int	main(void){
	// Malloc
	char*	bjr = malloc(sizeof(char) * 8);
	if (!bjr){
		fprintf(stderr, "malloc()\n");
		return (0);
	}
	bjr = "Bonjour";
	fprintf(stderr, "%s\n", bjr);

	// Realloc
	// bjr = realloc(bjr, sizeof(char) * 22);
	// if (!bjr){
	// 	fprintf(stderr, "realloc()\n");
	// 	return (0);
	// }
	// bjr = "Bonjour tous le monde";
	// fprintf(stderr, "%s\n", bjr);

	// Free
	showAllocMem();
	free(bjr);
	showAllocMem();
	return (0);
}
