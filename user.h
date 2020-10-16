#ifndef USER_H
#define USER_H

#include <vector>
#include <sodium.h>
#include <cstdint>

class User
{

private: 
    unsigned int id = 0;
    unsigned char sk[crypto_core_ed25519_BYTES];
    unsigned char pk[crypto_core_ed25519_BYTES];

public:
    User();
    User(unsigned int userId);
    ~User();
    void GenerateEnrollmentKeys();        //generates user secret key and public key
    std::pair<unsigned int, std::vector<unsigned char>> GetUserEnrollmentInfo();    //returns <User ID, User public key>

};

#endif