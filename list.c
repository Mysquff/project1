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
void deleteNode(Node*);
void deleteNodeAndItsChildren(Node*);

// Bolean checkers.
bool isLeftmostChild(Node*);
bool isRightmostChild(Node*);

// Getters.
int getIndex(Node*);
Node* getLeftmostChild(Node*);
Node* getRightmostChild(Node*);
Node* getLeftNeighbour(Node*);
Node* getRightNeighbour(Node*);
int getLeftmostChildIndex(Node*);
int getRightmostChildIndex(Node*);
int getLeftNeighbourIndex(Node*);
int getRightNeighbourIndex(Node*);

// Setters.
void setParent(Node*, Node*);
void setLeftmostChild(Node*, Node*);
void setRightmostChild(Node*, Node*);
void setLeftNeighbour(Node*, Node*);
void setRightNeighbour(Node*, Node*);


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
	else if (rightNode) {
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

// Returns leftmost child.
Node* getLeftmostChild(Node* parent) {
	assert(parent);
	return parent->leftmostChild;
}

// Returns rightmost child.
Node* getRightmostChild(Node* parent) {
	assert(parent);
	return parent->rightmostChild;
}

// Returns left neighbour.
Node* getLeftNeighbour(Node* node) {
	assert(node);
	return node->left;
}

// Returns right neighbour.
Node* getRightNeighbour(Node* node) {
	assert(node);
	return node->right;
}

// Returns leftmost child's index.
int getLeftmostChildIndex(Node* parent) {
	assert(parent);
	Node* leftmostChild = getLeftmostChild(parent);
	return getIndex(leftmostChild);
}

// Returns rightmost child's index.
int getRightmostChildIndex(Node* parent) {
	assert(parent);
	Node* rightmostChild = getRightmostChild(parent);
	return getIndex(rightmostChild);
}

// Returns left neighbour's index.
int getLeftNeighbourIndex(Node* node) {
	assert(node);
	Node* leftNeighbour = getLeftNeighbour(node);
	return getIndex(leftNeighbour);
}

// Returns right neighbour's index.
int getRightNeighbourIndex(Node* node) {
	assert(node);
	Node* rightNeighbour = getRightNeighbour(node);
	return getIndex(rightNeighbour);
}

// Checks if a node is leftmost child of its parent.
bool isLeftmostChild(Node* node) {

	// Node is a leftmost child.
	if (node->left == NULL) {
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
		return true;
	}

	// Node is not a rightmost child.
	else {
		return false;
	}
}

// Sets node's pointer to parent.
void setParent(Node* node, Node* parent) {
	node->parent = parent;
}

// Sets parent's leftmost child and accordingly sets leftmost child's parent.
void setLeftmostChild(Node* parent, Node* child) {

	if (child) {
		// Assert child can be made leftmost child.
		assert(child->left == NULL);

		child->parent = parent;
	}

	if (parent) {
		parent->leftmostChild = child;
	}
}

// Sets parent's rightmost child and accordingly sets rightmost child's parent.
void setRightmostChild(Node* parent, Node* child) {

	if (child) {
		// Assert child can be made rightmost child.
		assert(child->right == NULL);

		child->parent = parent;
	}

	// There is no parent. Hence child is a root node.
	if (parent) {
		parent->rightmostChild = child;
	}

}

// Sets node's left neighbour.
void setLeftNeighbour(Node* node, Node* leftNeighbour) {
	if (node) {
		node->left = leftNeighbour;
	}
}

void setRightNeighbour(Node* node, Node* rightNeighbour) {
	if (node) {
		node->right = rightNeighbour;
	}
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
		// Node has children.
		if (node->leftmostChild) {
			// Assert node has also rightmost child.
			assert(node->rightmostChild);

			// Reset node's rightmost child poiinter to parent.
			setParent(node->rightmostChild, NULL);

			// Link right neighbour with rightmost child.
			linkNodes(node->rightmostChild, node->right);

			// Set node's leftmost child as its parent's leftmost child.
			setLeftmostChild(parent, node->leftmostChild);
		}

		// Node has no children.
		else {
			// Assert node has no link to rightmost child.
			assert(!(node->leftmostChild));

			// Link right neighbour with rightmost child.
			linkNodes(node->rightmostChild, node->right);

			// Set right neighbour to leftmost child.
			setLeftmostChild(parent, node->right);
		}
	}

	else if (isRightmostChild(node)) {
		// Node has children.
		if (node->rightmostChild) {
			// Assert node has also leftmost child.
			assert(node->leftmostChild);

			// Reset node's leftmost child pointer to parent.
			setParent(node->leftmostChild, NULL);

			// Link left neighbour with leftmost child.
			linkNodes(node->left, node->leftmostChild);

			// Set node's rightmost child as its parent's rightmost child.
			setRightmostChild(parent, node->rightmostChild);
		}

		// Node has no children.
		else {
			// Assert node has no link to leftmost child.
			assert(!(node->rightmostChild));

			// Link left neighbour with leftmost child.
			linkNodes(node->left, node->leftmostChild);

			// Set left neighbour to rightmost child.
			setRightmostChild(parent, node->left);
		}
	}

	else { // Node is not border child.

		// Assert pointer to parent is set to NULL.
		assert(node->parent == NULL);

		// Node has children.
		if (node->leftmostChild && node->rightmostChild) {
			// Reset neighbours links to parent.
			setParent(node->leftmostChild, NULL);
			setParent(node->rightmostChild, NULL);

			// Link neighbours with border children.
			linkNodes(node->left, node->leftmostChild);
			linkNodes(node->rightmostChild, node->right);
		}

		// Node has no children.
		else {
			// Link node's neighbours to each other.
			linkNodes(node->left, node->right);
		}


	}
}

void deleteNodeAndItsChildren(Node* subtreeRootNode) {

	Node* parent = subtreeRootNode->parent;
	Node* leftNeighbour = subtreeRootNode->left;
	Node* rightNeighbour = subtreeRootNode->right;

	// Subtree root node is only child.
	if (isLeftmostChild(subtreeRootNode) && isRightmostChild(subtreeRootNode)) {
		setRightmostChild(parent, NULL);
		setLeftmostChild(parent, NULL);
	}

	// Subtree root node is leftmost child.
	else if (isLeftmostChild(subtreeRootNode)) {
		setLeftNeighbour(rightNeighbour, NULL);
		setLeftmostChild(parent, rightNeighbour);
	}

	// Subtree root node is rightmost child.
	else if (isRightmostChild(subtreeRootNode)) {
		setRightNeighbour(leftNeighbour, NULL);
		setRightmostChild(parent, leftNeighbour);
	}

	// Subtree is middle child.
	else {
		linkNodes(leftNeighbour, rightNeighbour);
	}

	subtreeRootNode->parent = NULL;
	setLeftNeighbour(subtreeRootNode, NULL);
	setRightNeighbour(subtreeRootNode, NULL);
}
