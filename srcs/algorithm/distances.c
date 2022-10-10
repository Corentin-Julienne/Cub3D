#include "cub3d.h"

/* Calculate the distance between 2 intersections points on X axis */
double  calc_dist_x(double ang_y)
{
    return (CUBES_SIZE / tan(ang_y));
}

/* Calculate the distance between 2 intersections points on Y axis */
double  calc_dist_y(double ang_y)
{
    return (CUBES_SIZE / tan(ang_y));
}

/* Calculate the distance between 2 points */
double  calc_dist(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}