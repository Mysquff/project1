#ifdef	TREE_H
#define	TREE_H

struct Tree;

extern void initializeTree(Tree* tree);

extern int getTreeNodesAmount(Tree*);

// Adds node and puts it as a 'parentIndex' node's rightmost child. */
extern void addTreeNode(Tree* tree, int parentIndex);

extern int getTreeNodeRightmostChildIndex(Tree* tree, int parentIndex);

#endif /* TREE_H */
