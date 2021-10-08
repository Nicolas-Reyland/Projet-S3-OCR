// randomness.c

#include "randomness.h"

/* Initialize randomness
 */
void _nn_initRandom()
{
  if (_nn_random_init_done)
    return;
  srand( time( NULL ));
  _nn_random_init_done = true;
}

/* Returns a random double value between min_value and max_value
 */
double getRandomDouble(double min_value, double max_value)
{
  double range = max_value - min_value;
  double random_double = (double) rand() / (D_RAND_MAX / range);
  return random_double + min_value;
}

/* Returns a random double value between 0.0 and 1.0
 */
double getNormalizedPositiveRandomDouble()
{
  return (double) rand() / D_RAND_MAX;
}

/* Returns a random double value between -1.0 and 1.0
 */
double getNormalizedRandomDouble()
{
  return (double) rand() / RAND_MAX_DIV_BY_2 - 1.0;
}

//
