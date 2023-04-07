#include "BTNode.h"
BTNode::BTNode(Process* process) {
	setPrcs(process);
	setLch(NULL);
	setRch(NULL);
}

//setters
void BTNode::setPrcs(Process* process) {
	prcs = process;
}

void BTNode::setLch(BTNode* left) {
	lch = left;
}

void BTNode::setRch(BTNode* right) {
	rch = right;
}

//getters
Process* BTNode::getPrcs() {
	return prcs;
}

BTNode* BTNode::getLch() {
	return lch;
}

BTNode* BTNode::getRch() {
	return rch;
}

BTNode::~BTNode(){}