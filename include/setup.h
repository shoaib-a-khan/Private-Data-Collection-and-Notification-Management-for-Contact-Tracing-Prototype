#ifndef SETUP_H
#define SETUP_H

#include <vector>
#include <sodium.h>
#include "user.h"
#include "store.h"

class Setup
{
private:
public:
    Setup();
    ~Setup();
    void CreateUsers(std::vector<User> &Users, unsigned int userCount);
    void EnrollUsersInStore(std::vector<User> Users, Store &s);
    void GenerateProximityList(std::vector<std::pair<unsigned int, std::vector<unsigned int>>> &ProximityList, std::vector<User> Users, unsigned int chance);
    void CreateKnownInfectedList(std::vector<unsigned int> &Infected, std::vector<User> Users, unsigned int percent);
};

#endif
