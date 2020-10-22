#include <iostream>
#include <cstdint>
#include <stdio.h>
#include <sodium.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <chrono>
#include "../include/setup.h"
#include "../include/user.h"
#include "../include/store.h"
#include "../include/gov.h"


int main(void)
{
    if (sodium_init() < 0)
    {
        /* panic! the library couldn't be initialized, it is not safe to use */
        std::cout << "Error initializing libsodium!\n";
    }

    std::vector<int> percentInitiallyInfected = {5, 10};                //Experimental Settings (Changing these values requires modifications in setup.cpp)   
    std::vector<int> probabilityOfContact = {10, 20};                   //Experimental Settings (Changing these values requires modifications in setup.cpp) 
    std::vector<int> userCount = {500, 1000, 1500, 2000, 2500};         //Experimental Settings (Values may be added, modified or deleted) 

    std::vector<User> Users;
    std::vector<unsigned int> KnownInfected;
    std::vector<std::pair<unsigned int, std::vector<unsigned int>>> ProximityList;
    Setup sim;
    std::ofstream fout;
    fout.open("Contact_Tracing_Results.txt", std::ios_base::app); //runtimes and communication costs are dumped here.

    for (int i = 0; i < probabilityOfContact.size(); i++)   //2 iterations
    {
        for (int j = 0; j < percentInitiallyInfected.size(); j++)   //2 iterations
        {
            fout << "\nProbability of Proximity between any 2 users X & Y: " << probabilityOfContact[i] << "%" << std::endl;
            fout << "Percentage of Users Initially Infected: " << percentInitiallyInfected[j] << "%" << std::endl;
            std::cout << "\nProbability of Proximity between any 2 users X & Y: " << probabilityOfContact[i] << "%" << std::endl;
            std::cout << "Percentage of Users Initially Infected: " << percentInitiallyInfected[j] << "%" << std::endl;

            for (int k = 0; k < userCount.size(); k++)     //userCount.size() many iterations
            {
                Gov G;
                Store store(1);
                fout << "\nUser Count: " << userCount[k] << std::endl;
                std::cout << "\nUser Count: " << userCount[k] << std::endl;
                
                sim.CreateUsers(Users, userCount[k]);                                           //Creating userCount[k] many Users in the system
                sim.EnrollUsersInStore(Users, store);                                           //Simulating users' enrollment in store
                sim.CreateKnownInfectedList(KnownInfected, Users, percentInitiallyInfected[j]); //Creating list of known infected users
                sim.GenerateProximityList(ProximityList, Users, probabilityOfContact[i]);       //Generating Delta - The simulated proximity list provided by CCTV infrastructure
                
                G.InitKnownInfected(KnownInfected);
                auto start = std::chrono::high_resolution_clock::now();
                G.ComputeSetGamma();                                                             //Gov computing set Gamma
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                fout << "Gov's Time to Compute Set Gamma: " << duration.count() / 1000000.0 << " s" << std::endl;
                std::cout << "Gov's Time to Compute Set Gamma: " << duration.count() / 1000000.0 << " s" << std::endl;

                store.InitProximityList(ProximityList);                                         //Initializing store's proximity list with simulated Delta
                start = std::chrono::high_resolution_clock::now();
                store.DeriveRiskList();                                                         //Store deriving list L_j from Delta
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                fout << "Store's Time to Compute List L: " << duration.count() / 1000000.0 << " s" << std::endl;
                std::cout << "Store's Time to Compute List L: " << duration.count() / 1000000.0 << " s" << std::endl;

                start = std::chrono::high_resolution_clock::now();
                G.DeriveRiskList(store.GetRiskList());                                          //Gov deriving RiskList
                stop = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                fout << "Gov's Time to Derive Risk List: " << duration.count() / 1000000.0 << " s" << std::endl;
                fout << "Store to Gov Communication Cost: " << 3 * 32 * (store.GetRiskList().size()) << " bytes" << std::endl;
                std::cout << "Gov's Time to Derive Risk List: " << duration.count() / 1000000.0 << " s" << std::endl;
                std::cout << "Store to Gov Communication Cost: " << 3 * 32 * (store.GetRiskList().size()) << " bytes" << std::endl;

                Users.clear();
                KnownInfected.clear();
                ProximityList.clear();
            }
        }
    }
    fout.close();
    return 0;
}