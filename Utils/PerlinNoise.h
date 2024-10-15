#pragma once
#include <math.h>
class PerlinNoise
{
private:
public:
    static int p[512];
    static const int permutation[256];
    PerlinNoise();
    ~PerlinNoise();

    static double Noise(double x, double y, double z);
    static double Fade(double t);
    static double Lerp(double t, double a, double b);
    static double Grad(int hash, double x, double y, double z);
};