#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <sodium.h>
#include <string.h>
#include <math.h>



int main(void)
{
    if (sodium_init() < 0)
    {
        /* panic! the library couldn't be initialized, it is not safe to use */
        std::cout << "Error!\n";
    }

    for (int i = 0; i < 100; i++)
    {
        uint32_t r = randombytes_uniform(pow(2, 32) - 1);
        std::cout << r << std::endl;
    }

    unsigned char r[crypto_core_ed25519_BYTES];
    unsigned char gr[crypto_core_ed25519_BYTES];
    crypto_core_ed25519_scalar_random(r);
    crypto_scalarmult_ed25519_base_noclamp(gr, r);
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