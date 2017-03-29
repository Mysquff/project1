#ifndef LIST_H
#define LIST_H

// Node type used in both trees and lists.
struct Node;
typedef struct Node Node;

extern void initializeNode(Node**, int);
extern void destroyNode(Node*);
extern void deleteNode(Node*);
extern void deleteNodeAndItsChildren(Node*);
extern void linkNodes(Node*, Node*);
extern void AddNodeToParent(Node*, Node*);
extern void splitNode(Node*, Node*, Node*);


extern bool isLeftmostChild(Node*);
extern bool isRightmostChild(Node*);

extern int getIndex(Node*);
extern Node* getLeftmostChild(Node*);
extern Node* getRightmostChild(Node*);
extern Node* getLeftNeighbour(Node*);
extern Node* getRightNeighbour(Node*);
extern int getLeftmostChildIndex(Node*);
extern int getRightmostChildIndex(Node*);
extern int getLeftNeighbourIndex(Node*);
extern int getRightNeighbourIndex(Node*);

#endif /* LIST_H */
