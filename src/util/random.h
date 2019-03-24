#ifndef RANDOM_H
#define RANDOM_H
#include <string>
#include <cstdlib>
#include <ctime>

class Random {
public:
    Random() {
        srand(time(NULL));
    }
    std::string string(int);
    int number(int);
    int number(int, int);
private:
    std::string seeder = "ABCDEFGHIJLMNOPQRSTUVWXYZ~!@#$%^&*()_+-=abcdefghijlmnopqrstuvwxyz0123456789";
};

#endif
