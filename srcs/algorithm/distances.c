#include "cub3d.h"

/* Calculate the distance between 2 points */
double  calc_dist(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}