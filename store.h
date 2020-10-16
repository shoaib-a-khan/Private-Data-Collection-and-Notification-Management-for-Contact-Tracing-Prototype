#ifndef STORE_H
#define STORE_H

#include "sodium.h"
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <cstring>
#include "triple.h"

class Store
{

private:
    std::unordered_map<unsigned int, std::vector<unsigned char>> UserDB;           //Each row of DB is <UserID, 32 byte PK>
    std::vector<std::pair<unsigned int, std::vector<unsigned int>>> ProximityList; //Each element in the Proximit List is a pair <User X , List of Y's in Proximity to X>
    std::vector<Triple> List;

public:
    Store();
    ~Store();
    void EnrollUser(unsigned int userID, std::vector<unsigned char> userPk);
    void DeriveRiskList();
    void Store::ComputeRiskTriple(Triple &T, unsigned int X, std::vector<unsigned char> A_y);
    std::vector<unsigned char> Compute_HX(unsigned int X);
    std::vector<unsigned char> Compute_GZ(unsigned char z[]);
    std::vector<unsigned char> Compute_AyZ(unsigned char z[], std::vector<unsigned char> A_y);
    std::vector<Triple> GetRiskList();
};

#endif
