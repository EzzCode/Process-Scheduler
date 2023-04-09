#pragma once
#include "BTNode.h"
class BTree {
private:
	BTNode* root;

	//Assisting recursive functions
	void insertHelper(BTNode*& subroot, Process* p);
	bool preorderSearchHelper(BTNode* subroot, int pid, Process*& p);
	bool removeHelper(BTNode* subroot, int pid, Process*& p);
	void markOrphan(BTNode*& subroot);
	void removeSubTree(BTNode*& subroot);
public:
	BTree();

	//setters
	void set_root(BTNode* rt);
	//getters
	BTNode* get_root();

	//Public Tree methods
	void insert(Process* p);
	bool preorderSearch(int pid, Process*& p);
	bool remove(int pid, Process*& p);

	~BTree();
};