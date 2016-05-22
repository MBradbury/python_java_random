#ifndef JAVA_RANDOM_H
#define JAVA_RANDOM_H
#pragma once

#include <stdbool.h>

typedef long long int seed_t;

typedef struct {

  seed_t seed;
  double _next_gaussian;
  bool _has_next_gaussian;

} java_random_t;


void java_random_init(java_random_t* this);

void java_random_create(java_random_t* this, seed_t seed);

void java_random_set_seed(java_random_t* this, seed_t seed);
seed_t java_random_get_seed(const java_random_t* this);

long long int java_random_next(java_random_t* this, int bits);

double java_random_double(java_random_t* this);
double java_random_gaussian(java_random_t* this);


#endif // JAVA_RANDOM_H
