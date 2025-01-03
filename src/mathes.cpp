#include "mathes.hpp"

float mathes::clamp(float value, float min, float max) {
    return min + ((value - min) > 0 ? (value - min) : 0) - ((value - max) > 0 ? (value - max) : 0);
}

double mathes::clamp(double value, double min, double max) {
    return min + ((value - min) > 0 ? (value - min) : 0) - ((value - max) > 0 ? (value - max) : 0);
}

int mathes::clamp(int value, int min, int max) {
    return min + ((value - min) > 0 ? (value - min) : 0) - ((value - max) > 0 ? (value - max) : 0);
}


//int mathes::multiply(int a, int b) {
//    if (a < 10 || b < 10) {
//        return a * b; // Base case for small integers
//    }
//
//    int n = max(static_cast<int>(log10(abs(a)) + 1), static_cast<int>(log10(std::abs(b)) + 1));
//    int half = n / 2;
//
//    int highA = a / static_cast<int>(pow(10, half));
//    int lowA = a % static_cast<int>(pow(10, half));
//    int highB = b / static_cast<int>(pow(10, half));
//    int lowB = b % static_cast<int>(pow(10, half));
//
//    int z0 = multiply(lowA, lowB);
//    int z1 = multiply(lowA + highA, lowB + highB);
//    int z2 = multiply(highA, highB);
//
//    return z2 * static_cast<int>(pow(10, 2 * half)) + (z1 - z2 - z0) * static_cast<int>(pow(10, half)) + z0;
//}