#ifndef	TREE_H
#define	TREE_H

// Tree structure based on double-linked lists and array.
struct Tree;
typedef struct Tree Tree;

// Main functions.
extern void initializeTree(Tree**);
extern void destroyTree(Tree*);

// Auxiliary functions.
extern void addTreeNode(Tree*, int);
void splitTreeNodeByIndex(Tree*, int, int);
extern void deleteTreeNodeByIndex(Tree*, int);
extern void deleteSubtreeByIndex(Tree*, int);

// Getters.
extern int getTreeNodesAmount(Tree*);
extern int getTreeNodeRightmostChildIndexByIndex(Tree*, int);

#endif /* TREE_H */
