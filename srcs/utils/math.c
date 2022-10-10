#include "cub3d.h"

/* Since I had a few problems with results being X.999999 because of PI,
I made this function in order to ceil the double in case this is all 999999.
Even if this is make by error (really low probability), it will not change anything. */
double  ceil_double(double nb)
{
    double  tmp;

    tmp = nb;
    if (nb - (int)nb > 0.99999)
        tmp = (int)nb + 1;
    return (tmp);
}