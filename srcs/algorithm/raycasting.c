#include "cub3d.h"

/* Calculate the remaining distance between x and 
the next intersection point on X axis */
static double  calc_next_inter_x(double x, double ang_y)
{
    double  dist;

    dist = (CUBES_SIZE - fmod(x, CUBES_SIZE));
    ang_y = fmod(ang_y, 360);
    if (ang_y > 90 && ang_y < 270)
        dist *= -1;
    return (x + dist);
}

/* Calculate the remaining distance between y and
the next intersection point on Y axis */
static double  calc_next_inter_y(double y, double ang_y)
{
    double  dist;

    dist = (CUBES_SIZE - fmod(y, CUBES_SIZE));
    ang_y = fmod(ang_y, 360);
    if (ang_y < 180 && ang_y > 0)
        dist *= -1;
    return (y + dist);
}

/* Allocate a new intersections array */
static double **new_intersections_array(int count)
{
    double  **intersections;
    int     i;

    intersections = malloc(sizeof(double *) * (count + 1));
    if (!intersections)
        return (NULL);

    i = 0;
    while (i < count)
    {
        intersections[i] = malloc(sizeof(double) * 2);
        if (!intersections[i])
            return (NULL);
        intersections[i][0] = (double)-1;
        intersections[i][1] = (double)-1;
        i++;
    }

    intersections[i] = NULL;
    return (intersections);
}

/* Free the instructions array */
static void free_intersections_array(double **intersections)
{
    int i;

    if (!intersections)
        return ;

    i = 0;
    while (intersections[i])
    {
        free(intersections[i]);
        i++;
    }
    free(intersections);
}

/* Calculate all intersections of x-axis */
double **find_x_intersections(t_game *game, double ang, double start_x, double start_y)
{
    double  **intersections;
    double  cast_x;
    double  found_y;
    int     map_x;
    int     map_y;
    int     i;

    ang = fmod(ang, 360);
    if (ang == 90 || ang == 270)
        return (NULL);
    
    intersections = new_intersections_array(6); // CHANGE THIS WITH THE MAP WIDTH
    if (!intersections)
        return (NULL);

    cast_x = start_x;
    i = 0;
    while (42)
    {
        cast_x = calc_next_inter_x(cast_x, ang);
        if (ang >= 90 && ang <= 270)
            found_y = start_y + tanf(ang * M_PI / 180) * fabs(cast_x - start_x);
        else
            found_y = start_y - tanf(ang * M_PI / 180) * fabs(cast_x - start_x);
        found_y = ceil_double(found_y);

        map_x = (int)floor(cast_x / CUBES_SIZE);
        map_y = (int)floor(found_y / CUBES_SIZE);

        if (map_x > 6 || map_y > 6 || map_x < 0 || map_y < 0) // CHANGE THIS WITH THE MAP WIDTH
            break;

        intersections[i][0] = cast_x;
        intersections[i][1] = found_y;
        i++;

        if (game->infomap->map[map_y][map_x] == '1')
            break;
    }
    return intersections;
}

/* Calculate all intersections of y-axis */
double **find_y_intersections(t_game *game, double ang, double start_x, double start_y)
{
    double  **intersections;
    double  cast_y;
    double  found_x;
    int     map_x;
    int     map_y;
    int     i;

    ang = fmod(ang, 360);
    if (ang == 0 || ang == 180)
        return (NULL);
    
    intersections = new_intersections_array(6); // CHANGE THIS WITH THE MAP HEIGHT
    if (!intersections)
        return (NULL);

    cast_y = start_y;
    i = 0;
    while (42)
    {
        cast_y = calc_next_inter_y(cast_y, ang);
        if (ang >= 180 && ang <= 360)
            found_x = start_x - fabs(cast_y - start_y) / tanf(ang * M_PI / 180);
        else
            found_x = start_x + fabs(cast_y - start_y) / tanf(ang * M_PI / 180);
        found_x = ceil_double(found_x);
        map_x = (int)floor(found_x / CUBES_SIZE);
        map_y = (int)floor(cast_y / CUBES_SIZE);

        if (map_x > 6 || map_y > 6 || map_x < 0 || map_y < 0) // CHANGE THIS WITH THE MAP WIDTH AND HEIGHT
            break;

        intersections[i][0] = found_x;
        intersections[i][1] = cast_y;
        i++;

        if (game->infomap->map[map_y][map_x] == '1')
            break;
    }
    return (intersections);
}

/* Count the amount of valid intersections = thoses that are not -1 */
static int count_valid_intersections(double **intersections)
{
    int i;

    if (!intersections)
        return (0);
    i = 0;
    while (intersections[i])
    {
        if (intersections[i][0] == -1 || intersections[i][1] == -1)
            break;
        i++;
    }
    return (i);
}

/* Check which intersection array has the last value to the wall */
double **get_touching_array(t_raycast *cast, t_player *ply)
{
    double  x_dist;
    double  y_dist;
    double  **x_inter;
    double  **y_inter;

    x_inter = cast->intersections_x;
    y_inter = cast->intersections_y;

    if (!x_inter && !y_inter)
        return (NULL);

    if (cast->inter_x_size - 1 >= 0)
        x_dist = calc_dist(ply->pos_x, ply->pos_y, x_inter[cast->inter_x_size - 1][0], x_inter[cast->inter_x_size - 1][1]);
    else
        x_dist = -1;

    if (cast->inter_y_size - 1 >= 0)
        y_dist = calc_dist(ply->pos_x, ply->pos_y, y_inter[cast->inter_y_size - 1][0], y_inter[cast->inter_y_size - 1][1]);
    else
        y_dist = -1;

    if (x_dist >= y_dist)
        return (x_inter);
    return (y_inter);
}

/* Start the raycasting */
void    raycast(t_game *game, t_raycast *cast)
{
    char        **map;
    t_player    *ply;
    double      *touching_inter;

    map = game->infomap->map;
    ply = game->player;

    cast->intersections_x = find_x_intersections(game, ply->ang_y, ply->pos_x, ply->pos_y);
    cast->intersections_y = find_y_intersections(game, ply->ang_y, ply->pos_x, ply->pos_y);
    cast->inter_x_size = count_valid_intersections(cast->intersections_x);
    cast->inter_y_size = count_valid_intersections(cast->intersections_y);

    /* In all intersections we have found, get the one who touched the wall and copy values to struct */
    if (get_touching_array(cast, ply) == cast->intersections_x)
        touching_inter = cast->intersections_x[cast->inter_x_size - 1];
    else
        touching_inter = cast->intersections_y[cast->inter_y_size - 1];

    /* Copy them to the structure */
    cast->wall_touch_x = touching_inter[0];
    cast->wall_touch_y = touching_inter[1];

    if (!cast->intersections_x)
        printf("No intersections on X axis\n");
    if (!cast->intersections_y)
        printf("No intersections on Y axis\n");

    /* Free everything */
    free_intersections_array(cast->intersections_x);
    free_intersections_array(cast->intersections_y);

    /* Set everything to NULL to be sure we're not using freed values anymore */
    cast->intersections_x = NULL;
    cast->intersections_y = NULL;
}