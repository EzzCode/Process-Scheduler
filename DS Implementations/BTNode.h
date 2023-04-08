#pragma once
#include "../Program Classes/Process.h"
class BTNode {
private:
    Process* prcs;
    BTNode* lch;
    BTNode* rch;
public:
    BTNode(Process* process);

    //setters
    void setPrcs(Process* process);
    void setLch(BTNode* left);
    void setRch(BTNode* right);

    //getters
    Process* getPrcs();
    BTNode* getLch();
    BTNode* getRch();
    
    ~BTNode();
};