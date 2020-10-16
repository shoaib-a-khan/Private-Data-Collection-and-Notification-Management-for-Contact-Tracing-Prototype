#include "gov.h"


Gov::Gov()
{

}

Gov::~Gov()
{

}

void Gov::DeriveRiskList(std::vector<Triple> List)
{
    

}

void Gov::InitKnownInfected(std::vector<unsigned int> infected)
{
    knownInfected = infected;
}

void Gov::ComputeSetKhi()
{
    for (int i = 0; i < knownInfected.size(); i++)
    {
        uint8_t hashOut[crypto_core_ed25519_BYTES];
        uint8_t hashIn[sizeof(unsigned int)];
        unsigned int X = knownInfected[i];

        memcpy(&hashIn, &X, sizeof(X));
        crypto_hash_sha256(hashOut, hashIn, sizeof(unsigned int));
        crypto_core_ed25519_scalar_reduce(hashOut, hashOut); //compute H(X_i)
        std::vector<unsigned char> vecHx(hashOut, hashOut + crypto_core_ed25519_BYTES);
        vectorKhi.insert(vecHx);
    }
}

bool Gov::UpdateBoard()
{

}
