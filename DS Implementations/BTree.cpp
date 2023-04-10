#include "BTree.h"
BTree::BTree() {
    set_root(nullptr);
}

//setters
void BTree::set_root(BTNode* rt) {
    root = rt;
}
//getters
BTNode* BTree::get_root() {
    return root;
}

//Public Tree methods
void BTree::insert(Process* p) {
    insertHelper(root, p);
}
bool BTree::remove(int pid, Process*& p) {
    return removeHelper(root, pid, p);
}

//Assisting recursive functions
void BTree::insertHelper(BTNode*& subroot, Process* p) {
    if (!subroot) {
        subroot = new BTNode();
        subroot->setPrcs(p);
        return;
    }
    //Currently a process can only fork once
    insertHelper(subroot->getLch(), p);
}
bool BTree::removeHelper(BTNode* subroot, int pid, Process*& p) {
    if (!subroot) return false;
    Process* prcs = subroot->getPrcs();
    int id = prcs->get_PID();
    if (id == pid) {
        p = new Process(*(prcs));
        markOrphan(subroot->getLch());
        return true;
    }
    //Currently a process can only fork once
    return removeHelper(subroot->getLch(), pid, p);
}
void BTree::markOrphan(BTNode*& subroot) {
    if (!subroot) return;
    subroot->getPrcs()->set_state(5);
}
void BTree::removeSubTree(BTNode*& subroot) {
    if (!subroot) return;
    removeSubTree(subroot->getLch());
    delete subroot;
    subroot = nullptr;
}

BTree::~BTree() {
    removeSubTree(root);
}