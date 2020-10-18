#include "gov.h"

Gov::Gov()
{
}

Gov::~Gov()
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
        // crypto_core_ed25519_scalar_reduce(hashOut, hashOut); //compute H(X_i)
        std::vector<unsigned char> vecHx(hashOut, hashOut + crypto_core_ed25519_BYTES);
        vectorKhi.push_back(vecHx);
    }
}

void Gov::DeriveRiskList(std::vector<Triple> storeList)
{
    for (int i = 0; i < storeList.size(); i++)
    {
        Triple T = storeList[i];
        bool match = 0; 
        // std::equal(T.first.begin(), T.first.end(), vectorKhi[i].begin());
        for(int i=0; i < vectorKhi.size(); i++)
        {
            if(T.first == vectorKhi[i])
            {
                match = 1;
                break;
            }
        }
        
        // std::vector<std::vector<unsigned char>>::iterator itr;
        // itr = find(vectorKhi.begin(), vectorKhi.end(), T.first);
        // if (itr != vectorKhi.end())
        if(match)
        {
            Twople R;
            unsigned char s[crypto_core_ed25519_BYTES];
            crypto_core_ed25519_scalar_random(s); //sample random s
            R.first = Compute_TS(T.second, s);
            R.second = Compute_TS(T.third, s);
            RiskList.push_back(R);
        }
    }
}

std::vector<unsigned char> Gov::Compute_TS(std::vector<unsigned char> T, unsigned char s[])
{
    unsigned char Tar[crypto_core_ed25519_BYTES];
    unsigned char Ts[crypto_core_ed25519_BYTES];
    std::copy(T.begin(), T.end(), Tar);                                 //vector to array
    crypto_scalarmult_ed25519(Ts, s, Tar);                               //  Ts = Tar^s
    std::vector<unsigned char> vecTs(Ts, Ts + crypto_core_ed25519_BYTES); //array to vector
    return vecTs;
}

bool Gov::UpdateBoard()
{

}
