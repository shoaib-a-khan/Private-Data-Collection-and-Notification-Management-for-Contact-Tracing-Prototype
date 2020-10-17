#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <sodium.h>
#include <string.h>
#include <math.h>
#include <vector>
#include "user.h"
#include "store.h"
#include "gov.h"


int main(void)
{
    if (sodium_init() < 0)
    {
        /* panic! the library couldn't be initialized, it is not safe to use */
        std::cout << "Error!\n";
    }
    
    Gov G;
    std::vector<User> Users;
    Store s(1);
    for(int i=1; i <= 500; i++)
    {   
        User u(i);
        u.GenerateEnrollmentKeys();
        std::pair<unsigned int, std::vector<unsigned char>> uei;
        uei = u.GetUserEnrollmentInfo();
        s.EnrollUser(uei.first, uei.second);
        Users.push_back(u);
    }
    std::vector<std::pair<unsigned int, std::vector<unsigned int>>> ProximityList;
    for(int i=0; i < Users.size(); i++)
    {
        std::pair<unsigned int, std::vector<unsigned int>> PerUserProximityList;
        PerUserProximityList.first = Users[i].GetID();
        for(int j=i+1; j < Users.size(); j++)
        {
            uint32_t r = randombytes_uniform(pow(2, 32) - 1);
            if(r % 10 == 0)
                PerUserProximityList.second.push_back(Users[j].GetID());
        }
        ProximityList.push_back(PerUserProximityList);        
    }

    s.InitProximityList(ProximityList);
    s.DeriveRiskList();
    
    std::vector<unsigned int> Infected;
    for(int i=0; i < Users.size(); i++)
    {
        uint32_t r = randombytes_uniform(pow(2, 32) - 1);
        if(r % 10 == 0)
            Infected.push_back(Users[i].GetID());
    }
    G.InitKnownInfected(Infected);
    G.ComputeSetKhi();
    G.DeriveRiskList(s.GetRiskList());


    
    

    
    // for (int i = 0; i < 100; i++)
    // {
    //     uint32_t r = randombytes_uniform(pow(2, 32) - 1);
    //     std::cout << r << std::endl;
    // }

    // unsigned char r[crypto_core_ed25519_BYTES];
    // unsigned char gr[crypto_core_ed25519_BYTES];
    // crypto_core_ed25519_scalar_random(r);
    // crypto_scalarmult_ed25519_base_noclamp(gr, r);
    // crypto_scalarmult_base(gr, r);
    // unsigned char client_pk[crypto_kx_PUBLICKEYBYTES], client_sk[crypto_kx_SECRETKEYBYTES];
    
    /* Generate the client's key pair */
    // crypto_kx_keypair(gr, r);



    // uint8_t sk[crypto_core_ed25519_SCALARBYTES];
    // uint8_t pk[crypto_core_ed25519_BYTES];
    // crypto_core_ed25519_scalar_random(sk);
    // crypto_scalarmult_ed25519_base_noclamp(pk, sk);

    return 0;
}