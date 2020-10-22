#ifndef GOV_H
#define GOV_H

#include <sodium.h>
#include "triple.h"
#include <vector>
#include <cstring>
#include <algorithm>

class Gov
{

private:
    
    std::vector<unsigned int> knownInfected;    //id's of known infected persons {X_1 ... X_k}
    std::vector<std::vector<unsigned char>> vectorGamma; //vector Gamma in the paper 
    std::vector<Twople> RiskList;
    std::vector<Twople> BulletinBoard;
    

public:
    Gov();
    ~Gov();
    void InitKnownInfected(std::vector<unsigned int> infected);
    void ComputeSetGamma();
    void DeriveRiskList(std::vector<Triple> storeList);
    std::vector<unsigned char> Compute_TS(std::vector<unsigned char> T, unsigned char s[] );
    bool UpdateBoard();

};

#endif
