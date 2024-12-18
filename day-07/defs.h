#ifndef __DEFS__
#define __DEFS__

double pow(double base, double exponent)
{
  double result = 1;
  while (exponent > 0)
  {
    result *= base;
    --exponent;
  }
  return result;
}

#endif
