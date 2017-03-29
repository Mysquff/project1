#ifndef	TREE_H
#define	TREE_H

struct Tree;
typedef struct Tree Tree;

extern void initializeTree(Tree**);
extern void destroyTree(Tree*);
extern void addTreeNode(Tree*, int);
extern int getTreeNodesAmount(Tree*);
extern int getTreeNodeRightmostChildIndexByIndex(Tree*, int);
extern void deleteTreeNodeByIndex(Tree*, int);
extern void deleteSubtreeByIndex(Tree*, int);
void splitTreeNodeByIndex(Tree*, int, int);

#endif /* TREE_H */
