#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "list.h"

// Double-linked list node structure.
struct Node {

	// Number used in identifying a node.
	int index;

	// Pointers to neighbours.
	Node* left;
	Node* right;

	// Pointers to sons
	Node* leftmostChild;
	Node* rightmostChild;

	// Used only in either leftmost or rightmost children.
	// Otherwise set to null.
	Node* parent;
};

/* FUNCTION DECLARATIONS */

// Main functions.
void initializeListNode(Node**, int);
void destroyListNode(Node*);
void deleteListNode(Node*);
void deleteListNodeAndItsChildren(Node*);

// Auxiliary functions.
void linkListNodes(Node*, Node*);
void AddListNodeToParent(Node*, Node*);
void splitListNode(Node*, Node*, Node*);

// Bolean checkers.
bool isListNodeLeftmostChild(Node*);
bool isListNodeRightmostChild(Node*);

// Getters.
int getListNodeIndex(Node*);
int getListNodeLeftmostChildIndex(Node*);
int getListNodeRightmostChildIndex(Node*);
int getListNodeLeftNeighbourIndex(Node*);
int getListNodeRightNeighbourIndex(Node*);

Node* getListNodeParent(Node*);
Node* getListNodeLeftmostChild(Node*);
Node* getListNodeRightmostChild(Node*);
Node* getListNodeLeftNeighbour(Node*);
Node* getListNodeRightNeighbour(Node*);

// Setters.
void setListNodeParent(Node*, Node*);
void setListNodeLeftmostChild(Node*, Node*);
void setListNodeRightmostChild(Node*, Node*);
void setListNodeLeftNeighbour(Node*, Node*);
void setListNodeRightNeighbour(Node*, Node*);

/* FUNCTION DEFINITIONS */

// Main functions.

// Initializes node.
void initializeListNode(Node** nodePointer, int index) {
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
void destroyListNode(Node* node) {
	assert(node);
	free(node);
}

// Deletes node from its parent children list.
// And puts its own children in the place in the list it occupied.
void deleteListNode(Node* node) {

	Node* parent = getListNodeParent(node);

	if (isListNodeLeftmostChild(node) && isListNodeRightmostChild(node)) {
		// Set node's border child as its parent's border child.
		setListNodeLeftmostChild(parent, node->leftmostChild);
		setListNodeRightmostChild(parent, node->rightmostChild);
	}

	else if (isListNodeLeftmostChild(node)) {
		// Node has children.
		if (node->leftmostChild) {
			// Assert node has also rightmost child.
			assert(node->rightmostChild);

			// Reset node's rightmost child poiinter to parent.
			setListNodeParent(node->rightmostChild, NULL);

			// Link right neighbour with rightmost child.
			linkListNodes(node->rightmostChild, node->right);

			// Set node's leftmost child as its parent's leftmost child.
			setListNodeLeftmostChild(parent, node->leftmostChild);
		}

		// Node has no children.
		else {
			// Assert node has no link to rightmost child.
			assert(!(node->leftmostChild));

			// Link right neighbour with rightmost child.
			linkListNodes(node->rightmostChild, node->right);

			// Set right neighbour to leftmost child.
			setListNodeLeftmostChild(parent, node->right);
		}
	}

	else if (isListNodeRightmostChild(node)) {
		// Node has children.
		if (node->rightmostChild) {
			// Assert node has also leftmost child.
			assert(node->leftmostChild);

			// Reset node's leftmost child pointer to parent.
			setListNodeParent(node->leftmostChild, NULL);

			// Link left neighbour with leftmost child.
			linkListNodes(node->left, node->leftmostChild);

			// Set node's rightmost child as its parent's rightmost child.
			setListNodeRightmostChild(parent, node->rightmostChild);
		}

		// Node has no children.
		else {
			// Assert node has no link to leftmost child.
			assert(!(node->rightmostChild));

			// Link left neighbour with leftmost child.
			linkListNodes(node->left, node->leftmostChild);

			// Set left neighbour to rightmost child.
			setListNodeRightmostChild(parent, node->left);
		}
	}

	else { // Node is not border child.

		// Assert pointer to parent is set to NULL.
		assert(node->parent == NULL);

		// Node has children.
		if (node->leftmostChild && node->rightmostChild) {
			// Reset neighbours links to parent.
			setListNodeParent(node->leftmostChild, NULL);
			setListNodeParent(node->rightmostChild, NULL);

			// Link neighbours with border children.
			linkListNodes(node->left, node->leftmostChild);
			linkListNodes(node->rightmostChild, node->right);
		}

		// Node has no children.
		else {
			// Link node's neighbours to each other.
			linkListNodes(node->left, node->right);
		}
	}
}

// Deletes node from its parent children list.
// Does not put its children in its place.
void deleteListNodeAndItsChildren(Node* subtreeRootNode) {

	Node* parent = getListNodeParent(subtreeRootNode);
	Node* leftNeighbour = getListNodeLeftNeighbour(subtreeRootNode);
	Node* rightNeighbour = getListNodeRightNeighbour(subtreeRootNode);

	bool isLeftmostChild = isListNodeLeftmostChild(subtreeRootNode);
	bool isRightmostChild = isListNodeRightmostChild(subtreeRootNode);

	// Subtree root node is only child.
	if (isLeftmostChild && isRightmostChild) {

		setListNodeRightmostChild(parent, NULL);
		setListNodeLeftmostChild(parent, NULL);
	}

	// Subtree root node is leftmost child.
	else if (isLeftmostChild) {
		setListNodeLeftNeighbour(rightNeighbour, NULL);
		setListNodeLeftmostChild(parent, rightNeighbour);
	}

	// Subtree root node is rightmost child.
	else if (isRightmostChild) {
		setListNodeRightNeighbour(leftNeighbour, NULL);
		setListNodeRightmostChild(parent, leftNeighbour);
	}

	// Subtree is middle child.
	else {
		linkListNodes(leftNeighbour, rightNeighbour);
	}

	setListNodeParent(subtreeRootNode, NULL);
	setListNodeLeftNeighbour(subtreeRootNode, NULL);
	setListNodeRightNeighbour(subtreeRootNode, NULL);
}

// Auxiliary functions.

// Links two nodes. First one goes to the left, second one to the right.
void linkListNodes(Node* leftNode, Node* rightNode) {

	// Both nodes exist.
	if (leftNode && rightNode) {
		setListNodeRightNeighbour(leftNode, rightNode);
		setListNodeLeftNeighbour(rightNode, leftNode);
	}

	// Only left node exists.
	else if (leftNode) {
		setListNodeRightNeighbour(leftNode, NULL);
	}

	// Only right node exists.
	else if (rightNode) {
		setListNodeLeftNeighbour(rightNode, NULL);
	}
}

// Adds new child to parent
void AddListNodeToParent(Node* parent, Node* child) {

	Node* leftmostChild = getListNodeLeftmostChild(parent);
	Node* rightmostChild = getListNodeRightmostChild(parent);

	// Parent node does not have children yet.
	if (leftmostChild == NULL && rightmostChild == NULL) {
		// Link a parent to a child.
		setListNodeLeftmostChild(parent, child);
		setListNodeRightmostChild(parent, child);
	}

	// Parent has only one child.
	else if (leftmostChild == rightmostChild) {
		// Place a new child as a new rightmostChild.
		linkListNodes(rightmostChild, child);

		// Link parent to the new child.
		setListNodeRightmostChild(parent, child);
	}


	// Parent has one or more children.
	else {
		// Place a new child as a new rightmostChild.
		linkListNodes(rightmostChild, child);

		// Set parent pointer of the old rightmostChild to NULL.
		setListNodeParent(rightmostChild, NULL);

		// Link parent to the new child.
		setListNodeRightmostChild(parent, child);
	}
}

// Adds new child of parent and puts it on the right of left neighbour.
// All nodes on the right of left neighbour become children of a new node.
void splitListNode(Node* parent, Node* leftNeighbour, Node* node) {

	bool isLeftmostChild = isListNodeLeftmostChild(leftNeighbour);
	bool isRightmostChild = isListNodeRightmostChild(leftNeighbour);

	// Left neighbour is parent's only child.
	if (isLeftmostChild && isRightmostChild) {

		// Link left neighbour and node.
		linkListNodes(leftNeighbour, node);

		// Set node as parent's rightmost child.
		setListNodeRightmostChild(parent, node);
	}

	// Left neighbour is parent's rightmost child.
	else if (isRightmostChild) {
		// Link left neighbour and node.
		linkListNodes(leftNeighbour, node);

		// Set node as parent's rightmost child.
		setListNodeRightmostChild(parent, node);

		// Reset left neighbour link to parent.
		setListNodeParent(leftNeighbour, NULL);
	}

	// Left neighbour is middle or leftmost child.
	else {

		// And reset its link to left neighbour.
		setListNodeLeftNeighbour(leftNeighbour->right, NULL);

		// Set right neighbour of the left neighbour as node's leftmost child.
		setListNodeLeftmostChild(node, leftNeighbour->right);

		// Set parent's rightmost child as node's rightmost child.
		setListNodeRightmostChild(node, parent->rightmostChild);

		// Set node as parent's rightmost child.
		setListNodeRightmostChild(parent, node);

		// Link left neighbour and node.
		linkListNodes(leftNeighbour, node);
	}
}

// Boolean checkers.

// Checks if a node is leftmost child of its parent.
bool isListNodeLeftmostChild(Node* node) {

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
bool isListNodeRightmostChild(Node* node) {

	// Node is a rightmost child.
	if (node->right == NULL) {
		return true;
	}

	// Node is not a rightmost child.
	else {
		return false;
	}
}

// Getters.

// Returns node's index. If the node doesn't exist, returns -1.
int getListNodeIndex(Node* node) {

	if (node) {
		return node->index;
	}

	else {
		return -1;
	}

}

// Returns leftmost child's index.
int getListNodeLeftmostChildIndex(Node* parent) {
	assert(parent);
	Node* leftmostChild = getListNodeLeftmostChild(parent);
	return getListNodeIndex(leftmostChild);
}

// Returns rightmost child's index.
int getListNodeRightmostChildIndex(Node* parent) {
	assert(parent);
	Node* rightmostChild = getListNodeRightmostChild(parent);
	return getListNodeIndex(rightmostChild);
}

// Returns left neighbour's index.
int getListNodeLeftNeighbourIndex(Node* node) {
	assert(node);
	Node* leftNeighbour = getListNodeLeftNeighbour(node);
	return getListNodeIndex(leftNeighbour);
}

// Returns right neighbour's index.
int getListNodeRightNeighbourIndex(Node* node) {
	assert(node);
	Node* rightNeighbour = getListNodeRightNeighbour(node);
	return getListNodeIndex(rightNeighbour);
}

// Returns parent.
Node* getListNodeParent(Node* node) {
	assert(node);
	return node->parent;
}

// Returns leftmost child.
Node* getListNodeLeftmostChild(Node* parent) {
	assert(parent);
	return parent->leftmostChild;
}

// Returns rightmost child.
Node* getListNodeRightmostChild(Node* parent) {
	assert(parent);
	return parent->rightmostChild;
}

// Returns left neighbour.
Node* getListNodeLeftNeighbour(Node* node) {
	assert(node);
	return node->left;
}

// Returns right neighbour.
Node* getListNodeRightNeighbour(Node* node) {
	assert(node);
	return node->right;
}

// Setters.

// Sets node's pointer to parent.
void setListNodeParent(Node* node, Node* parent) {
	node->parent = parent;
}

// Sets parent's leftmost child and accordingly sets leftmost child's parent.
void setListNodeLeftmostChild(Node* parent, Node* child) {

	if (child) {
		// Assert child can be made leftmost child.
		assert(child->left == NULL);

		setListNodeParent(child, parent);
	}

	if (parent) {
		parent->leftmostChild = child;
	}
}

// Sets parent's rightmost child and accordingly sets rightmost child's parent.
void setListNodeRightmostChild(Node* parent, Node* child) {

	if (child) {
		// Assert child can be made rightmost child.
		assert(child->right == NULL);

		setListNodeParent(child, parent);
	}

	// There is no parent. Hence child is a root node.
	if (parent) {
		parent->rightmostChild = child;
	}

}

// Sets node's left neighbour.
void setListNodeLeftNeighbour(Node* node, Node* leftNeighbour) {
	if (node) {
		node->left = leftNeighbour;
	}
}

// Sets node's left neighbour.
void setListNodeRightNeighbour(Node* node, Node* rightNeighbour) {
	if (node) {
		node->right = rightNeighbour;
	}
}
