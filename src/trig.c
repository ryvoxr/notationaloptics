#include "utils.h"
#include <math.h>

/* degnormalize: normalizes angle deg to [0,360) */
double degnormalize(double deg) {
    double result = fmod(deg, 360);
    if (result < 0) result += 360;
    return result;
}

double degtorad(double deg) {
    return deg * (M_PI / 180);
}

double radtodeg(double rad) {
    return rad * (180 / M_PI);
}

double degsin(double deg) {
    return degnormalize(sin(degtorad(deg)));
}

double degcos(double deg) {
    return degnormalize(cos(degtorad(deg)));
}

double degtan(double deg) {
    return degnormalize(tan(degtorad(deg)));
}

double degatan2(double y, double x) {
    return degnormalize(radtodeg(atan2(y, x)));
}

