#ifndef LIST_H
#define LIST_H

struct Node;
typedef struct Node Node;

struct List;
typedef struct List List;

extern void initializeNode(Node**, int);
extern void initializeSentinel(Node**);
extern void linkNodes(Node*, Node*);
extern void addLeftNode(Node*, Node*);
extern void addRightNode(Node*, Node*);
extern void AddNodeToParent(Node*, Node*);


extern void initializeList(List**);
extern void addNodeToList(List*, Node*);

#endif /* LIST_H */
