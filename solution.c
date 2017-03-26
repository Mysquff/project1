#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "commands.h"

int main(void) {

	Tree* tree;
	initializeTree(&tree);

	destroyTree(tree);

	return 0;
}
