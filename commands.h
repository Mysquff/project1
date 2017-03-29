#ifndef COMMANDS_H
#define COMMANDS_H

enum Command;

typedef enum Command Command;

enum Command {
	COMMAND_ADD_NODE,
	COMMAND_RIGHTMOST_CHILD,
	COMMAND_DELETE_NODE,
	COMMAND_DELETE_SUBTREE,
	COMMAND_SPLIT_NODE,
	COMMAND_UNKNOWN
};

extern Command selectCommand(char*);

// ADD_NODE
extern void commandAddNode(Tree*, int);

// RIGHTMOST_CHILD
extern void commandRightmostChild(Tree*, int);

// DELETE_NODE
extern void commandDeleteNode(Tree*, int);

// DELETE_SUBTREE
extern void commandDeleteSubtree(Tree*, int);

// SPLIT_NODE
void commandSplitNode(Tree*, int, int);

#endif /* COMMANDS_H */
