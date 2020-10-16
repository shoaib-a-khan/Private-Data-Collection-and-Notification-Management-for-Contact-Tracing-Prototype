#ifndef GOV_H
#define GOV_H

#include <sodium.h>
#include "triple.h"
#include <vector>
#include <cstring>
#include <unordered_set>

class Gov
{

private:
    
    std::vector<unsigned int> knownInfected;    //id's of known infected persons {X_1 ... X_k}
    std::unordered_set<std::vector<unsigned char>> vectorKhi; 

public:
    Gov();
    ~Gov();
    void InitKnownInfected(std::vector<unsigned int> infected);
    void ComputeSetKhi();
    void DeriveRiskList(std::vector<Triple> List);
    bool UpdateBoard();

};

#endif
