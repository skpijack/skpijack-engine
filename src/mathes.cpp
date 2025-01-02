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