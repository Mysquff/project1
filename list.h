#ifndef LIST_H
#define LIST_H

// Double-linked list node structure.
struct Node;
typedef struct Node Node;

// Main functions.
extern void initializeListNode(Node**, int);
extern void destroyListNode(Node*);
extern void deleteListNode(Node*);
extern void deleteListNodeAndItsChildren(Node*);

// Auxiliary functions.
extern void AddListNodeToParent(Node*, Node*);
extern void splitListNode(Node*, Node*, Node*);

// Getters.
extern int getListNodeIndex(Node*);
extern int getListNodeLeftmostChildIndex(Node*);
extern int getListNodeRightmostChildIndex(Node*);
extern int getListNodeRightNeighbourIndex(Node*);

#endif /* LIST_H */
