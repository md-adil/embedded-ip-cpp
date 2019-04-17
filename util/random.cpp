#include "random.h"

std::string Random::string(int length) {
    std::string val = "";
    for(int i = 0; i <= length; i++) {
       val += seeder[number(seeder.size())];
    }
    return val;
}

int Random::number(int max) {
    return rand() % max;
}

int Random::number(int min, int max) {
    return min + ( rand() % ( max - min));
}
