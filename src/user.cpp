#include "../include/user.h"
#include <sodium.h>

User::User()
{
}

User::User(unsigned int userId)
{
    id = userId;
}

User::~User()
{
}

unsigned int User::GetID()
{
    return id;
}

void User::GenerateEnrollmentKeys()
{
    crypto_core_ed25519_scalar_random(sk);        //sample random y
    crypto_scalarmult_ed25519_base_noclamp(pk, sk);     //compute A_y = g^y
}

std::pair<unsigned int, std::vector<unsigned char>> User::GetUserEnrollmentInfo()
{
    std::pair<unsigned int, std::vector<unsigned char>> info;
    info.first = id;
    for(int i=0; i < crypto_core_ed25519_BYTES; i++)
        info.second.push_back(pk[i]);
    return info;  
}