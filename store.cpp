#include "store.h"

Store::Store()
{
}

Store::Store(unsigned int id)
{
    storeId = id;
}

Store::~Store()
{
}

void Store::EnrollUser(unsigned int userID, std::vector<unsigned char> userPK)
{
    UserDB[userID] = userPK;
}

void Store::InitProximityList(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> pList)
{
    ProximityList = pList;
}

void Store::DeriveRiskList()
{
    for (int i = 0; i < ProximityList.size(); i++)
    {
        for (int j = 0; j < ProximityList[i].second.size(); j++)
        {
            Triple T;
            unsigned int X = ProximityList[i].first;
            std::vector<unsigned char> A_y = UserDB[ProximityList[i].second[j]];
            ComputeRiskTriple(T, X, A_y); //Compute T_z
            List.push_back(T);        //insert T_z in List
        }
    }
}

void Store::ComputeRiskTriple(Triple &T, unsigned int X, std::vector<unsigned char> A_y)
{

    unsigned char z[crypto_core_ed25519_BYTES];
    crypto_core_ed25519_scalar_random(z); //sample random z
    T.first = Compute_HX(X);             //compute g^{H(X)}
    T.second = Compute_GZ(z);             //compute g^z
    T.third = Compute_AyZ(z, A_y);        //compute A_y^z
}

std::vector<unsigned char> Store::Compute_HX(unsigned int X)
{
    uint8_t hashOut[crypto_core_ed25519_BYTES];
    uint8_t hashIn[sizeof(unsigned int)];
    
    memcpy(&hashIn, &X, sizeof(X));
    crypto_hash_sha256(hashOut, hashIn, sizeof(unsigned int));
    crypto_core_ed25519_scalar_reduce(hashOut, hashOut);  //compute H(X)
    std::vector<unsigned char> vecHx(hashOut, hashOut + crypto_core_ed25519_BYTES);
    return vecHx;
    // unsigned char ghx[crypto_core_ed25519_BYTES];
    // crypto_scalarmult_ed25519_base_noclamp(ghx, hashOut); //compute g^{H(X)}
    // std::vector<unsigned char> vecGhx(ghx, ghx + crypto_core_ed25519_BYTES);
    // return vecGhx;
}


std::vector<unsigned char> Store::Compute_GZ(unsigned char z[])
{
    unsigned char gz[crypto_core_ed25519_BYTES];
    crypto_scalarmult_ed25519_base_noclamp(gz, z); //compute g^z
    std::vector<unsigned char> vecGz(gz, gz + crypto_core_ed25519_BYTES);
    return vecGz;
}

std::vector<unsigned char> Store::Compute_AyZ(unsigned char z[], std::vector<unsigned char> A_y)
{
    unsigned char UserPK[crypto_core_ed25519_BYTES];
    std::copy(A_y.begin(), A_y.end(), UserPK);          //vector to array
    crypto_scalarmult_ed25519_base_noclamp(UserPK, z); //compute g^z
    std::vector<unsigned char> vecAyz(UserPK, UserPK + crypto_core_ed25519_BYTES);  //array to vector
    return vecAyz;
}

std::vector<Triple> Store::GetRiskList()
{
    return List;
}
