#include <stdlib.h>
#include <stdbool.h>

#include "list.h"
#include "tree.h"

#define MAXIMUM_NUMBER_OF_NODES 500000

struct Tree {
	int nodesAmount;
	int newNodeIndex;

	Node** nodesArray;
};

/* DECLARATIONS */
void initializeTree(Tree**);
void destroyTree(Tree*);
void destroyTreeNodeByIndex(Tree*, int);
Node* getTreeNodeByIndex(Tree*, int);
void addTreeNode(Tree*, int);
int getTreeNodesAmount(Tree*);
int getRightmostChildIndexByParentIndex(Tree*, int);
void deleteTreeNodeByIndex(Tree*, int);
void deleteSubtreeByIndex(Tree*, int);
void deleteSubtree(Tree*, Node*);
void destroyTreeNodesRecursivelyByIndex(Tree*, int);
void splitTreeNodeByIndex(Tree*, int, int);


// Initializes tree.
void initializeTree(Tree** treePointer) {
	// Allocate tree.
	(*treePointer) = (Tree*) malloc(sizeof (Tree));

	// Temporary pointers.
	Tree* tree = (*treePointer);

	// Allocate nodes array.
	int arraySize = (sizeof (Node*)) * MAXIMUM_NUMBER_OF_NODES;
	tree->nodesArray = (Node**) malloc (arraySize);

	// Initialize root node.
	Node** rootPointer = &(tree->nodesArray[0]);
	initializeNode(rootPointer, 0);

	// Set nodes amount to 1.
	tree->nodesAmount = 1;

	// Set new node index to 1.
	tree->newNodeIndex = 1;
}

void decreaseTreeNodesAmount(Tree* tree) {
	(tree->nodesAmount)--;
}

void increaseTreeNodesAmount(Tree* tree) {
	(tree->nodesAmount)++;
}

void increaseTreeNewNodeIndex(Tree* tree) {
	(tree->newNodeIndex)++;
}

// Destroys tree and frees its memory.
void destroyTree(Tree* tree) {

	// Destroy all tree nodes.
	for (int i = 0; i < tree->newNodeIndex; i++) {
		destroyTreeNodeByIndex(tree, i);
	}

	// Destroy the nodes array.
	free(tree->nodesArray);

	// At last, destroy the tree.
	free(tree);
}

// Returns a pointer to the node by its index.
Node* getTreeNodeByIndex(Tree* tree, int index) {
	return tree->nodesArray[index];
}

// Adds new node to the tree.
void addTreeNode(Tree* tree, int parentIndex) {

	// Initialize new node.
	Node* node;
	initializeNode(&node, tree->newNodeIndex);

	// Place new node at the end of the nodes array.
	(tree->nodesArray)[tree->newNodeIndex] = node;

	// Increase number of nodes.
	increaseTreeNodesAmount(tree);

	// Increase new node index.
	increaseTreeNewNodeIndex(tree);

	// Put node into parent's children list.
	Node* parent = getTreeNodeByIndex(tree, parentIndex);
	AddNodeToParent(parent, node);
}

// Returns number of nodes in the tree.
int getTreeNodesAmount(Tree* tree) {
	return tree->nodesAmount;
}

// Returns an index of a rightmost child. If a child doesn't exist, returns -1.
int getRightmostChildIndexByParentIndex(Tree* tree, int parentIndex) {

	Node* parent = getTreeNodeByIndex(tree, parentIndex);

	return getRightmostChildIndex(parent);
}

// Deletes node and puts its children in its place.
void deleteTreeNodeByIndex(Tree* tree, int index) {

	Node* node = getTreeNodeByIndex(tree, index);

	// Delete node from its parent's list and put children in its place.
	deleteNode(node);

	// Delete node from nodes array and free its memory.
	destroyTreeNodeByIndex(tree, index);

}

void destroyTreeNodeByIndex(Tree* tree, int index) {

	Node* node = getTreeNodeByIndex(tree, index);

	if (node) {
		// Delete node from nodes array.
		tree->nodesArray[index] = NULL;

		// Destroy node.
		destroyNode(node);

		// Decreases nodes amount.
		decreaseTreeNodesAmount(tree);
	}
}

void deleteSubtreeByIndex(Tree* tree, int subtreeRootIndex) {
	Node* subtreeRoot = getTreeNodeByIndex(tree, subtreeRootIndex);
	deleteSubtree(tree, subtreeRoot);
}

void deleteSubtree(Tree* tree, Node* subtreeRoot) {
	// Disconnect root node from its parent and neighbours.
	deleteNodeAndItsChildren(subtreeRoot);

	// Destroy subtree recursively.
	int subtreeRootIndex = getIndex(subtreeRoot);
	destroyTreeNodesRecursivelyByIndex(tree, subtreeRootIndex);
}

// Destroy subtree recursively by indexes.
void destroyTreeNodesRecursivelyByIndex(Tree* tree, int index) {

	Node* node = getTreeNodeByIndex(tree, index);

	if (node) {

		// Destroy nodes below, starting from the leftmost child.
		int leftmostChildIndex = getLeftmostChildIndex(node);

		if (leftmostChildIndex != -1) {
			destroyTreeNodesRecursivelyByIndex(tree, leftmostChildIndex);
		}


		// Destroy nodes on the right.
		int rightNeighbourIndex = getRightNeighbourIndex(node);

		if (rightNeighbourIndex != -1) {
			destroyTreeNodesRecursivelyByIndex(tree, rightNeighbourIndex);
		}

		// Destroy node.
		destroyTreeNodeByIndex(tree, index);
	}
}

// Adds new child of parent and puts it on the right of left neighbour.
// All nodes on the right of left neighbour become children of a new node.
void splitTreeNodeByIndex(Tree* tree, int parentIndex, int leftNeighbourIndex) {

	// Initialize new node.
	Node* node;
	initializeNode(&node, tree->newNodeIndex);

	// Place new node at the end of the nodes array.
	(tree->nodesArray)[tree->newNodeIndex] = node;

	// Increase number of nodes.
	increaseTreeNodesAmount(tree);

	// Increase new node index.
	increaseTreeNewNodeIndex(tree);

	Node* parent = getTreeNodeByIndex(tree, parentIndex);
	Node* leftNeighbour = getTreeNodeByIndex(tree, leftNeighbourIndex);

	splitNode(parent, leftNeighbour, node);
}
