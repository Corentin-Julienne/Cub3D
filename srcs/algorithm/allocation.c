#include "../../includes/cub3d.h"

/* Allocate vertical and horizontal arrays with 2 sub-doubles */
static void alloc_vert_horiz(t_ray *ray)
{
    int i;

    i = 0;
    while (i < ray->size_x)
    {
        ray->found_vert[i] = malloc(sizeof(double) * 2);
        if (!ray->found_vert[i])
            exit(0); // TODO: Change this
        ray->found_vert[i][0] = -1.0;
        ray->found_vert[i][1] = -1.0;
        i++;
    }
    i = 0;
    while (i < ray->size_y)
    {
        ray->found_horiz[i] = malloc(sizeof(double) * 2);
        if (!ray->found_horiz[i])
            exit(0); // TODO: Change this
        ray->found_horiz[i][0] = -1.0;
        ray->found_horiz[i][1] = -1.0;
        i++;
    }
}

/* Allocate arrays we will need in order to detect intersections */
void    alloc_ray_intersections(t_ray *ray)
{
    int i;

    ray->found_vert = malloc(sizeof(double *) * ray->size_x);
    if (!ray->found_vert)
        exit(0); // TODO: Change this
    ray->found_horiz = malloc(sizeof(double *) * ray->size_y);
    if (!ray->found_horiz)
        exit(0); // TODO: Change this
    ray->found_order = malloc(sizeof(double *) * (ray->size_x + ray->size_y));
    if (!ray->found_order)
        exit(0); // TODO: Change this
    alloc_vert_horiz(ray);
    i = 0;
    while (i < ray->size_x + ray->size_y)
    {
        ray->found_order[i] = malloc(sizeof(double) * 3);
        if (!ray->found_order[i])
            exit(0); // TODO: Change this
        ray->found_order[i][0] = -1.0;
        ray->found_order[i][1] = -1.0;
        ray->found_order[i][2] = 0.0; // 0 for horizontal, 1 for vertical
        i++;
    }
}

/* Free intersections arrays */
void    free_ray_intersections(t_ray *ray)
{
    for (int i = 0; i < ray->size_x; i++)
        free(ray->found_vert[i]);
    free(ray->found_vert);
    for (int i = 0; i < ray->size_y; i++)
        free(ray->found_horiz[i]);
    free(ray->found_horiz);
    for (int i = 0; i < ray->size_x + ray->size_y; i++)
        free(ray->found_order[i]);
    free(ray->found_order);
}