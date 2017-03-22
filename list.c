#include "stdlib.h"

// Node type used in both trees and lists.
struct Node;
typedef struct Node Node;

// Double-linked list type.
struct List;
typedef struct List List;

struct Node {
	int index;

	List* childrenList;

	// Pointers to neighbours.
	Node* left;
	Node* right;
};

struct List {
	Node* leftSentinel;
	Node* rightSentinel;
};

/* FUNCTION DECLARATIONS */
void initializeNode(Node**, int);
void initializeSentinel(Node**);
void linkNodes(Node*, Node*);
void addLeftNode(Node*, Node*);
void addRightNode(Node*, Node*);
void AddNodeToParent(Node*, Node*);

void initializeList(List**);
void addNodeToList(List*, Node*);

/* FUNCTION DEFINITIONS */

// Initializes node.
void initializeNode(Node** nodePointer, int index) {
	// Allocate node.
	(*nodePointer) = (Node*) malloc(sizeof (Node));

	// Temporary pointer.
	Node* node = (*nodePointer);

	// Set node's index.
	node->index = index;

	// Set neighbours' pointers to NULL.
	node->left = NULL;
	node->right = NULL;

	// Initialzie children list.
	initializeList(&(node->childrenList));
}

// Initializes list sentinel.
void initializeSentinel(Node** sentinelPointer) {
	// Allocate sentinel.
	(*sentinelPointer) = (Node*) malloc(sizeof (Node));

	// Temporary pointer.
	Node* sentinel = (*sentinelPointer);

	// Set index to -1.
	sentinel->index = -1; // -1 is restricted only to sentinels.

	// Set  neighbours' pointers to NULL.
	sentinel->left = NULL;
	sentinel->right = NULL;

	// Sentinels do not have children, so set children list to NULL.
	sentinel->childrenList = NULL;
}

// Links two nodes. First one goes to the left, second one to the right.
void linkNodes(Node* leftNode, Node* rightNode) {
	leftNode->right = rightNode;
	rightNode->left = leftNode;
}

// Puts new node to the left of right node.
void addLeftNode(Node* rightNode, Node* newNode) {

	// Temporary pointer to original left neighbour of the right node.
	Node* leftNode = rightNode->left;

	// Place new node between left node and right node.
	linkNodes(leftNode, newNode);
	linkNodes(newNode, rightNode);
}

// Puts new node to the right of left node.
void addRightNode(Node* leftNode, Node* newNode) {

	// Temporary pointer to original left neighbour of the right node.
	Node* rightNode = leftNode->right;

	// Place new node between left node and right node.
	linkNodes(leftNode, newNode);
	linkNodes(newNode, rightNode);
}

// Adds new child to parent
void AddNodeToParent(Node* parent, Node* child) {
	addNodeToList(parent->childrenList, child);
}

// Initializes list.
void initializeList(List** listPointer) {
	// Allocate list.
	(*listPointer) = (List*) malloc(sizeof (List));

	// Temporary pointer.
	List* list = (*listPointer);

	// Initialize both sentinels and link them.
	initializeSentinel(&(list->leftSentinel));
	initializeSentinel(&(list->rightSentinel));
	linkNodes(list->leftSentinel, list->rightSentinel);
}

// Puts node on the right end of the list, just before the right sentinel.
void addNodeToList(List* list, Node* node) {
	addLeftNode(list->rightSentinel, node);
}
