#ifndef LIST_H
#define LIST_H

// Node type used in both trees and lists.
struct Node;
typedef struct Node Node;

extern void initializeNode(Node**, int);
extern void destroyNode(Node*);
extern void linkNodes(Node*, Node*);
extern void AddNodeToParent(Node*, Node*);
extern int getIndex(Node*);
extern Node* getRightmostChild(Node*);

#endif /* LIST_H */
