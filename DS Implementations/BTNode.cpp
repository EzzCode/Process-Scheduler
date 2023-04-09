#include "BTNode.h"
BTNode::BTNode() {
	setPrcs(nullptr);
	setLch(nullptr);
	setRch(nullptr);
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
Process*& BTNode::getPrcs() {
	return prcs;
}

BTNode*& BTNode::getLch() {
	return lch;
}

BTNode*& BTNode::getRch() {
	return rch;
}

BTNode::~BTNode(){
	delete prcs;
	setPrcs(nullptr);
	delete lch;
	setLch(nullptr);
	delete rch;
	setRch(nullptr);
}