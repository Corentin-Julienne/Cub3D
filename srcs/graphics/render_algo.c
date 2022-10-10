#include "cub3d.h"

/* Render walls from the map with the raycasting algorithm */
void    render_everything(t_game *game, int img_index)
{
    t_player    *ply;
    t_raycast   ray;
    double      wall_height;
    double      dist_wall;
    double      top_wall_y;
	int		    y;
    double      ang_offset;

    ply = game->player;

    if (game->keys[4])
        ply->ang_y -= 1;
    else if (game->keys[5])
        ply->ang_y += 1;

    for (int i = 0; i < game->wdw_x; i++)
    {
        ang_offset = ((double)i * ((double)PLY_VIEW_FOV_DEG / (double)game->wdw_x));
        raycast(game, &ray, ang_offset);
        dist_wall = calc_dist(ply->pos_x, ply->pos_y, ray.wall_touch_x, ray.wall_touch_y);
        wall_height = (CUBES_SIZE / dist_wall) * ply->dist_from_proj;
        top_wall_y = (game->wdw_y / 2) - (wall_height / 2);

    	y = top_wall_y;
        while (y < game->imgs_set[img_index]->height && y < top_wall_y + wall_height)
        {
            mlx_pixel_put_to_img(game->imgs_set[img_index], i, y, 0x00FFFF00);
            y++;
        }
    }
}