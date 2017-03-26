#ifndef	TREE_H
#define	TREE_H

struct Tree;
typedef struct Tree Tree;

extern void initializeTree(Tree**);
extern void destroyTree(Tree*);
extern void addTreeNode(Tree*, int);
extern int getTreeNodesAmount(Tree*);
extern int getRightmostChildIndex(Tree*, int);

#endif /* TREE_H */
