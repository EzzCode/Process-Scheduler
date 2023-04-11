#pragma once
#include "BTNode.h"
class BTree {
private:
	BTNode* root;
	int count_forked;

	//Private setters
	void set_count(int val);

	//Assisting recursive functions
	void insertHelper(BTNode*& subroot, Process* p);
	bool removeHelper(BTNode* subroot, int pid, Process*& p);
	void markOrphan(BTNode*& subroot);
	void removeSubTree(BTNode*& subroot);
public:
	BTree();

	//Public setters
	void set_root(BTNode* rt);
	
	//getters
	BTNode* get_root();
	int get_count();

	//Public Tree methods
	void insert(Process* p);
	bool remove(int pid, Process*& p);

	~BTree();
};