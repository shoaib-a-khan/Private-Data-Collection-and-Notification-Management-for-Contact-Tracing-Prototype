#include <math.h>
#include "../include/setup.h"

Setup::Setup()
{
}

Setup::~Setup()
{
}

void Setup::CreateUsers(std::vector<User> &Users, unsigned int userCount)
{
    for (int i = 1; i <= userCount; i++)
    {
        User u(i);
        u.GenerateEnrollmentKeys();
        Users.push_back(u);
    }
}

void Setup::EnrollUsersInStore(std::vector<User> Users, Store &s)
{
    for (int i = 0; i < Users.size(); i++)
    {
        std::pair<unsigned int, std::vector<unsigned char>> uei;
        uei = Users[i].GetUserEnrollmentInfo();
        s.EnrollUser(uei.first, uei.second);
    }
}

void Setup::GenerateProximityList(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> &ProximityList, std::vector<User> Users, unsigned int chance)
{
    for (int i = 0; i < Users.size(); i++)
    {
        std::pair<unsigned int, std::vector<unsigned int>> PerUserProximityList;
        int x = (chance == 10 ? 10 : 5);
        PerUserProximityList.first = Users[i].GetID();
        for (int j = 0; j < Users.size(); j++)
        {
            uint32_t r = randombytes_uniform(pow(2, 32) - 1);
            if (r % x == 0 && j != i) //use r mod 10 for 10% or r mod 5 for 20% chance of users X, Y crossing paths
                PerUserProximityList.second.push_back(Users[j].GetID());
        }
        ProximityList.push_back(PerUserProximityList);
    }
}

void Setup::CreateKnownInfectedList(std::vector<unsigned int> &Infected, std::vector<User> Users, unsigned int percent)
{
    int x = (percent == 10 ? 10 : 20);
    for (int i = 0; i < Users.size(); i++)
    {
        uint32_t r = randombytes_uniform(pow(2, 32) - 1);
        if (r % x == 0) //use r mod 10 for 10% of user population or r mod 20 for 5% of user population.
            Infected.push_back(Users[i].GetID());
    }
}