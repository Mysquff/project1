#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
bool isLeftmostChild(Node*);
bool isRightmostChild(Node*);
void setLeftmostChild(Node*, Node*);
void setRightmostChild(Node*, Node*);
void deleteNode(Node*);

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
	assert(node);
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
	assert(node);
	return node->index;
}

// Returns rightmost child.
Node* getRightmostChild(Node* parent) {
	assert(parent);
	return parent->rightmostChild;
}

// Checks if a node is leftmost child of its parent.
bool isLeftmostChild(Node* node) {

	// Node is a leftmost child.
	if (node->left == NULL) {

		// Asserts child has pointer to its parent set.
		assert(node->parent);

		return true;
	}

	// Node is not a leftmost child.
	else {
		return false;
	}
}

// Checks if a node is leftmost child of its parent.
bool isRightmostChild(Node* node) {

	// Node is a rightmost child.
	if (node->right == NULL) {

		// Asserts child has pointer to its parent set.
		assert(node->parent);

		return true;
	}

	// Node is not a rightmost child.
	else {
		return false;
	}
}

// Sets parent's leftmost child and accordingly sets leftmost child's parent.
void setLeftmostChild(Node* parent, Node* child) {

	if (child) {

	}

	// Asserts child can be made leftmost child.
	assert(child->left == NULL);

	parent->leftmostChild = child;
	child->parent = parent;
}

// Sets parent's rightmost child and accordingly sets rightmost child's parent.
void setRightmostChild(Node* parent, Node* child) {

	if (child) {
		// Asserts child can be made rightmost child.
		assert(child->right == NULL);

		child->parent = parent;
	}

	parent->rightmostChild = child;
}

// Deletes node from its parent children list.
// and puts own children in the place in the list it occupied.
void deleteNode(Node* node) {

	Node* parent = node->parent;

	if (isLeftmostChild(node) && isRightmostChild(node)) {
		// Set node's border child as its parent's border child.
		setLeftmostChild(parent, node->leftmostChild);
		setRightmostChild(parent, node->rightmostChild);
	}

	else if (isLeftmostChild(node)) {
		// Set node's leftmost child as its parent's leftmost child.
		setLeftmostChild(parent, node->leftmostChild);

		// Link right neighbour with rightmost child.
		linkNodes(node->rightmostChild, node->right);
	}

	else if (isRightmostChild(node)) {
		// Set node's rightmost child as its parent's rightmost child.
		setRightmostChild(parent, node->rightmostChild);

		// Link left neighbour with leftmost child.
		linkNodes(node->left, node->leftmostChild);
	}

	else { // Node is not border child.

		// Asserts pointer to parent is set to NULL.
		assert(parent == NULL);

		// Link neighbours with border children.
		linkNodes(node->left, node->leftmostChild);
		linkNodes(node->rightmostChild, node->right);
	}
}
