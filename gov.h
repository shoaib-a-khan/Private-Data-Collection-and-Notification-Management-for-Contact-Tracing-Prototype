#ifndef GOV_H
#define GOV_H

#include "sodium.h"
#include "triple.h"
#include <vector>

class Gov
{

private:
    
    std::vector<unsigned int> knownInfected;    //id's of known infected persons {X_1 ... X_k}
    std::vector<std::vector<unsigned char>> vectorKhi;


public:
    Gov();
    ~Gov();
    void DeriveRiskList(std::vector<Triple> List);
    bool UpdateBoard();

};

#endif
