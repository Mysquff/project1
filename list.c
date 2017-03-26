#include <stdlib.h>

#include "list.h"

struct Node {
	int index;

	// Pointers to neighbours.
	Node* left;
	Node* right;

	// Pointers to sons
	Node* leftmostChild;
	Node* rightmostChild;

	// Used only in either leftmost or rightmost sons. Otherwise set to null.
	Node* parent;
};

/* FUNCTION DECLARATIONS */
void initializeNode(Node**, int);
void destroyNode(Node*);
void linkNodes(Node*, Node*);
void AddNodeToParent(Node*, Node*);
int getIndex(Node*);
Node* getRightmostChild(Node*);

/* FUNCTION DEFINITIONS */

// Initializes node.
void initializeNode(Node** nodePointer, int index) {
	// Allocate node.
	(*nodePointer) = (Node*) malloc(sizeof (Node));

	// Temporary pointer.
	Node* node = (*nodePointer);

	// Set node's index.
	node->index = index;

	// Initialize pointers to neighbours,
	node->left = NULL;
	node->right = NULL;

	// to leftmost and rightmost children,
	node->leftmostChild = NULL;
	node->rightmostChild = NULL;

	// and a parent.
	node->parent = NULL;
}
// Destroys a node and frees its memory.
void destroyNode(Node* node) {
	free(node);
}

// Links two nodes. First one goes to the left, second one to the right.
void linkNodes(Node* leftNode, Node* rightNode) {

	// Both nodes exist.
	if (leftNode && rightNode) {
		leftNode->right = rightNode;
		rightNode->left = leftNode;
	}

	// Only left node exists.
	else if (leftNode) {
		leftNode->right = NULL;
	}

	// Only right node exists.
	else {
		rightNode->left = NULL;
	}
}

// Adds new child to parent
void AddNodeToParent(Node* parent, Node* child) {

	// Parent node does not have children yet.
	if (parent->leftmostChild == NULL && parent->rightmostChild == NULL) {
		// Link a parent to a child,
		parent->leftmostChild = child;
		parent->rightmostChild = child;

		// and a child to a parent.
		child->parent = parent;
	}

	// Parent has only one child.
	else if (parent->leftmostChild == parent->rightmostChild) {
		// Place a new child as a new rightmostChild.
		linkNodes(parent->rightmostChild, child);

		// Link parent to the new child.
		parent->rightmostChild = child;

		// Link new child to parent.
		child->parent = parent;
	}


	// Parent has one or more children.
	else {
		// Place a new child as a new rightmostChild.
		linkNodes(parent->rightmostChild, child);

		// Set parent pointer of the old rightmostChild to NULL.
		(parent->rightmostChild)->parent = NULL;

		// Link parent to the new child.
		parent->rightmostChild = child;

		// Link new child to parent.
		child->parent = parent;
	}
}

// Returns node's index. If the node doesn't exist, returns -1.
int getIndex(Node* node) {
	if (node) {
		return node->index;
	}

	else {
		return -1;
	}
}

// Returns rightmost child.
Node* getRightmostChild(Node* parent) {
	return parent->rightmostChild;
}
