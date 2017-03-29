#ifndef LIST_H
#define LIST_H

// Node type used in both trees and lists.
struct Node;
typedef struct Node Node;

extern void initializeListNode(Node**, int);
extern void destroyListNode(Node*);
extern void deleteListNode(Node*);
extern void deleteListNodeAndItsChildren(Node*);
extern void AddListNodeToParent(Node*, Node*);
extern void splitListNode(Node*, Node*, Node*);

extern int getListNodeIndex(Node*);
extern int getListNodeLeftmostChildIndex(Node*);
extern int getListNodeRightmostChildIndex(Node*);
extern int getListNodeRightNeighbourIndex(Node*);

#endif /* LIST_H */
