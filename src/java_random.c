
#include "java_random.h"

#include <math.h>

void java_random_init(java_random_t* this)
{
    this->seed = 0;
}

void java_random_create(java_random_t* this, seed_t seed)
{
    java_random_init(this);
    java_random_set_seed(this, seed);
}

void java_random_set_seed(java_random_t* this, seed_t seed)
{
    this->seed = (seed ^ 0x5DEECE66DLL) & ((1LL << 48) - 1);
}
seed_t java_random_get_seed(const java_random_t* this)
{
    return this->seed;
}

long long int java_random_next(java_random_t* this, int bits)
{
    if (bits < 1) {
        bits = 1;
    }
    if (bits > 32) {
        bits = 32;
    }

    this->seed = (this->seed * 0x5deece66dLL + 0xbLL) & ((1LL << 48) - 1);

    return this->seed >> (48 - bits);
}

double java_random_double(java_random_t* this)
{
    return ((java_random_next(this, 26) << 27) + java_random_next(this, 27)) / (double)(1LL << 53);
}

double java_random_gaussian(java_random_t* this)
{
    if (!this->_has_next_gaussian) {
        double v1, v2, s;
        do {
            v1 = 2 * java_random_double(this) - 1;
            v2 = 2 * java_random_double(this) - 1;
            s = v1 * v1 + v2 * v2;
        } while (s >= 1 || s == 0);
        double multiplier = sqrt(-2 * log(s) / s);
        this->_next_gaussian = v2 * multiplier;
        this->_has_next_gaussian = true;
        return v1 * multiplier;
    }
    else {
        this->_has_next_gaussian = false;
        return this->_next_gaussian;
    }
}
