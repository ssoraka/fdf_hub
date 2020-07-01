/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoraka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:23:42 by ssoraka           #+#    #+#             */
/*   Updated: 2019/03/07 16:22:42 by ssoraka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

#define ABS(nbr) ((nbr) >= 0 ? (nbr) : (-1) * (nbr))

void *mlx_ptr;
void *win_ptr;
void *img_ptr;

int width;
int hight;
int img_width;
int img_hight;
int cam_x;
int cam_y;

int point_x;
int point_y;

char *addr;
int len = 100;
int ox_x = 1;
int ox_y = 0;
int ox_z = 0;

int oy_x = 0;
int oy_y = 1;
int oy_z = 0;

int oz_x = 0;
int oz_y = 0;
int oz_z = 1;

double ang_x = 0;
double ang_y = 0;
double ang_z = 0;





typedef struct		s_vektr
{
	double x;
	double y;
	double z;
	int abs_x;
	int abs_y;
	int abs_z;

}					t_vektr;


t_vektr *ox0;
t_vektr *oy0;
t_vektr *oz0;


int ft_znak(int num)
{
	int znak;

	znak = 0;
	if (num > 0)
		znak = 1;
	else if (num < 0)
		znak = -1;
	return (znak);
}



void ft_put_pixel_to_img(char *addr, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= img_width || y >= img_hight)
		return ;
	addr[(y * img_width + x) * 4 + 0] = color;// & 0x000000FF;
	addr[(y * img_width + x) * 4 + 1] = (color >> 8);// & 0x000000FF;
	addr[(y * img_width + x) * 4 + 2] = (color >> 16);// & 0x000000FF;
	addr[(y * img_width + x) * 4 + 3] = (color >> 24);// & 0x000000FF;
}


typedef struct		s_line
{
	int y1;
	int x1;
	int y2;
	int x2;
	int diry;
	int dirx;
	int deltay;
	int deltax;
	int error;
	int color;
	struct s_line *next;
}					t_line;


int ft_altha_from_error(int error, int delta)
{
	int altha;

	error = ABS(error);
	delta = ABS(delta);

	if (error == 0)
		return (0);
	else if (delta / error >= 2)
		return (0x90000000);
	else if (delta / error == 0)
		return (0xFF000000);
	else
		return (0xE0000000);
	/*
	error = ABS(error);
	delta = ABS(delta);
	altha = 0x19000000;
	error = (error * 10) / delta;
	if (error >= 10)
		return (0);
	if (error == 0)
		return (0xFF000000);
	altha = altha * (10 - error);*/
	return (altha);
}

/*
** худо бедно работает...
*/
void draw_line_img_lower_45_wu(t_line *line)
{
	int error;
	int color;
	int znak;

	error = 0;
	znak = ft_znak(line->deltax);
	while (line->x1 != line->x2)
	{
		if (2 * error >= line->deltax)
		{
			line->y1 += line->diry;
			error = error - line->deltax;
		}
		ft_put_pixel_to_img(addr, line->x1, line->y1, line->color);
		color = ft_altha_from_error(error, line->deltax) + line->color;
		if (ft_znak(error) * znak == 1)
			ft_put_pixel_to_img(addr, line->x1, line->y1 + line->diry, color);
		else if (ft_znak(error) * znak == -1)
			ft_put_pixel_to_img(addr, line->x1, line->y1 - line->diry, color);
		error = error + line->deltay;
		line->x1 += line->dirx;
	}
	ft_put_pixel_to_img(addr, line->x1, line->y1, color);
}

void draw_line_img_over_45_wu(t_line *line)
{
	int error;
	int color;
	int znak;

	error = 0;
	znak = ft_znak(line->deltay);
	while (line->y1 != line->y2)
	{
		if (2 * error >= line->deltay)
		{
			line->x1 += line->dirx;
			error = error - line->deltay;
		}
		ft_put_pixel_to_img(addr, line->x1, line->y1, line->color);
		color = ft_altha_from_error(error, line->deltay) + line->color;
		if (ft_znak(error) * znak == 1)
			ft_put_pixel_to_img(addr, line->x1 + line->dirx, line->y1, color);
		else if (ft_znak(error) * znak == -1)
			ft_put_pixel_to_img(addr, line->x1 - line->dirx, line->y1, color);
		error = error + line->deltax;
		line->y1 +=line->diry;
	}
	ft_put_pixel_to_img(addr, line->x1, line->y1, color);
}


void draw_line_img_lower_45(t_line *line)
{
	int error;

	error = 0;
	while (line->x1 != line->x2)
	{
		ft_put_pixel_to_img(addr, line->x1, line->y1, line->color);
		//printf("%d\t%d\t%d\t%d\n", error, line->deltay, error * 2, line->deltax);
		error = error + line->deltay;
		if (2 * error >= line->deltax)
		{
			line->y1 += line->diry;
			error = error - line->deltax;
		}
		line->x1 += line->dirx;
	}
	ft_put_pixel_to_img(addr, line->x2, line->y2, line->color);
}


void draw_line_img_over_45(t_line *line)
{
	int error;

	error = 0;
	while (line->y1 != line->y2)
	{
		ft_put_pixel_to_img(addr, line->x1, line->y1, line->color);
		error = error + line->deltax;
		if (2 * error >= line->deltay)
		{
			line->x1 += line->dirx;
			error = error - line->deltay;
		}
		line->y1 +=line->diry;
	}
	ft_put_pixel_to_img(addr, line->x2, line->y2, line->color);
}


int draw_line_img1(int x1, int y1, int x2, int y2, int color)
{
	t_line *line;

	line = (t_line *)malloc(sizeof(t_line));
	line->x1 = x1;
	line->y1 = y1;
	line->x2 = x2;
	line->y2 = y2;
	line->color = color;
	line->diry = ft_znak(y2 - y1);
	line->dirx = ft_znak(x2 - x1);
	line->deltay = line->diry * (y2 - y1);
	line->deltax = line->dirx * (x2 - x1);
	if (line->deltax >= line->deltay)
	{
		draw_line_img_lower_45_wu(line);
	}
	else
	{
		draw_line_img_over_45_wu(line);
	}
	return (0);
}











int draw_line_img(int x1, int y1, int x2, int y2, int color)
{
	int diry;
	int dirx;
	int error;
	int deltay;
	int deltax;

	error = 0;

	diry = ft_znak(y2 - y1);
	dirx = ft_znak(x2 - x1);
	deltay = diry * (y2 - y1);
	deltax = dirx * (x2 - x1);

	if (deltax >= deltay)
	{
		while (x1 != x2)
		{
			ft_put_pixel_to_img(addr, x1, y1, color);
			error = error + deltay;
			if (2 * error >= deltax)
			{
				y1 += diry;
				error = error - deltax;
			}
			x1 +=dirx;
		}
	}
	else
	{
		while (y1 != y2)
		{
			ft_put_pixel_to_img(addr, x1, y1, color);
			error = error + deltax;
			if (2 * error >= deltay)
			{
				x1 += dirx;
				error = error - deltay;
			}
			y1 +=diry;
		}
	}
	return (0);
}




int draw_line(int x1, int y1, int x2, int y2)
{
	int diry;
	int dirx;
	int error;
	int deltay;
	int deltax;

	diry = ft_znak(y2 - y1);
	dirx = ft_znak(x2 - x1);

	error = 0;
	deltay = diry * (y2 - y1);
	deltax = dirx * (x2 - x1);

	if (deltax >= deltay)
	{
		while (x1 != x2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xFFFFFF);
			error = error + deltay;
			if (2 * error >= deltax)
			{
				y1 += diry;
				error = error - deltax;
			}
			x1 +=dirx;
		}
	}
	else
	{
		while (y1 != y2)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, 0xFFFFFF);
			error = error + deltax;
			if (2 * error >= deltay)
			{
				x1 += dirx;
				error = error - deltay;
			}
			y1 +=diry;
		}
	}



	mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, 0xFFFFFF);

	return (0);
}


/* 3 матрицы поворота */
void ft_print_oxyz()
{
	int ox_x1;
	int ox_y1;
	int ox_z1;

	int oy_x1;
	int oy_y1;
	int oy_z1;

	int oz_x1;
	int oz_y1;
	int oz_z1;

	ft_bzero(addr, 	img_width * img_hight * 4);
	ox_x1 = ox_x * cos(ang_z) - ox_y * sin(ang_z) + ox_z * 0;
	ox_y1 = ox_x * sin(ang_z) + ox_y * cos(ang_z) + ox_z * 0;
	ox_z1 = ox_x * 0 + ox_y * 0 + ox_z * 1;

	oy_x1 = oy_x * cos(ang_z) - oy_y * sin(ang_z) + oy_z * 0;
	oy_y1 = oy_x * sin(ang_z) + oy_y * cos(ang_z) + oy_z * 0;
	oy_z1 = oy_x * 0 + oy_y * 0 + oy_z * 1;

	oz_x1 = oz_x * cos(ang_z) - oz_y * sin(ang_z) + oz_z * 0;
	oz_y1 = oz_x * sin(ang_z) + oz_y * cos(ang_z) + oz_z * 0;
	oz_z1 = oz_x * 0 + oz_y * 0 + oz_z * 1;

	int ox_x2;
	int ox_y2;
	int ox_z2;

	int oy_x2;
	int oy_y2;
	int oy_z2;

	int oz_x2;
	int oz_y2;
	int oz_z2;

	ox_x2 = ox_x1 * cos(ang_y) + ox_y1 * 0 + ox_z1 * sin(ang_y);
	ox_y2 = ox_x1 * 0 + ox_y1 * 1 + ox_z1 * 0;
	ox_z2 = - ox_x1 * sin(ang_y) + ox_y1 * 0 + ox_z1 * cos(ang_y);

	oy_x2 = oy_x1 * cos(ang_y) + oy_y1 * 0 + oy_z1 * sin(ang_y);
	oy_y2 = oy_x1 * 0 + oy_y1 * 1 + oy_z1 * 0;
	oy_z2 = - oy_x1 * sin(ang_y) + oy_y1 * 0 + oy_z1 * cos(ang_y);

	oz_x2 = oz_x1 * cos(ang_y) + oz_y1 * 0 + oz_z1 * sin(ang_y);
	oz_y2 = oz_x1 * 0 + oz_y1 * 1 + oz_z1 * 0;
	oz_z2 = - oz_x1 * sin(ang_y) + oz_y1 * 0 + oz_z1 * cos(ang_y);


	int ox_x3;
	int ox_y3;
	int ox_z3;

	int oy_x3;
	int oy_y3;
	int oy_z3;

	int oz_x3;
	int oz_y3;
	int oz_z3;

	ox_x3 = ox_x2 * 1 + ox_y2 * 0 + ox_z2 * 0;
	ox_y3 = ox_x2 * 0 + ox_y2 * cos(ang_x) - ox_z2 * sin(ang_x);
	ox_z3 = ox_x2 * 0 + ox_y2 * sin(ang_x) + ox_z2 * cos(ang_x);

	oy_x3 = oy_x2 * 1 + oy_y2 * 0 + oy_z2 * 0;
	oy_y3 = oy_x2 * 0 + oy_y2 * cos(ang_x) - oy_z2 * sin(ang_x);
	oy_z3 = oy_x2 * 0 + oy_y2 * sin(ang_x) + oy_z2 * cos(ang_x);

	oz_x3 = oz_x2 * 1 + oz_y2 * 0 + oz_z2 * 0;
	oz_y3 = oz_x2 * 0 + oz_y2 * cos(ang_x) - oz_z2 * sin(ang_x);
	oz_z3 = oz_x2 * 0 + oz_y2 * sin(ang_x) + oz_z2 * cos(ang_x);


	draw_line_img(240, 240, ox_x3 + 240, ox_y3 + 240, 0x00FF00);
	draw_line_img(240, 240, oy_x3 + 240, oy_y3 + 240, 0x0000FF);
	draw_line_img(240, 240, oz_x3 + 240, oz_y3 + 240, 0xFF0000);
	mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);
}


t_vektr *ft_new_vektor(double x, double y, double z);




/*
**	избавление от погрешности
*/

void ft_norm_vektor(t_vektr *vek)
{
	double summ;

	summ = vek->x * vek->x + vek->y * vek->y + vek->z * vek->z;
	summ = sqrt(summ);
	vek->x = vek->x / summ;
	vek->y = vek->y / summ;
	vek->z = vek->z / summ;
}






t_vektr *ft_rot(t_vektr *ox, t_vektr *oy, double ang)
{
	t_vektr *ox1;
	double cosa = cos(ang);
	double sina = sin(ang);

	if (ang == 0)
		return (ox);
	ox1 = ft_new_vektor(0, 0, 0);
/*	ox1->x = ox1->x + ox->x * (cosa + (1 - cosa) * oy->x * oy->x);
	ox1->x = ox1->x + ox->y * ((1 - cosa) * oy->x * oy->y - sina * oy->z);
	ox1->x = ox1->x + ox->z * ((1 - cosa) * oy->x * oy->z + sina * oy->y);

	ox1->y = ox1->y + ox->x * ((1 - cosa) * oy->y * oy->x + sina * oy->z);
	ox1->y = ox1->y + ox->y * (cosa + (1 - cosa) * oy->y * oy->y);
	ox1->y = ox1->y + ox->z * ((1 - cosa) * oy->y * oy->z - sina * oy->x);

	ox1->z = ox1->z + ox->x * ((1 - cosa) * oy->z * oy->x - sina * oy->y);
	ox1->z = ox1->z + ox->y * ((1 - cosa) * oy->z * oy->y + sina * oy->x);
	ox1->z = ox1->z + ox->z * (cosa + (1 - cosa) * oy->z * oy->z);
*/
	double x = oy->x;
	double y = oy->y;
	double z = oy->z;

	ox1->x = ox1->x + ox->x * (cosa + (1 - cosa) * x * x);
	ox1->x = ox1->x + ox->y * ((1 - cosa) * x * y - sina * z);
	ox1->x = ox1->x + ox->z * ((1 - cosa) * x * z + sina * y);

	ox1->y = ox1->y + ox->x * ((1 - cosa) * y * x + sina * z);
	ox1->y = ox1->y + ox->y * (cosa + (1 - cosa) * y * y);
	ox1->y = ox1->y + ox->z * ((1 - cosa) * y * z - sina * x);

	ox1->z = ox1->z + ox->x * ((1 - cosa) * z * x - sina * y);
	ox1->z = ox1->z + ox->y * ((1 - cosa) * z * y + sina * x);
	ox1->z = ox1->z + ox->z * (cosa + (1 - cosa) * z * z);


	free(ox);
	ft_norm_vektor(ox1);
	return (ox1);
}


t_vektr *ft_new_vektor(double x, double y, double z)
{
	t_vektr *tmp;

	tmp = (t_vektr *)malloc(sizeof(t_vektr));
	tmp->x = x;
	tmp->y = y;
	tmp->z = z;
	return (tmp);
}


void ft_ret_abs_xyz(t_vektr *ox)
{
	ox->abs_x = (int)(ox->x * len);
	ox->abs_x = ox->abs_x + cam_x;
	ox->abs_y = (int)(ox->y * len);
	ox->abs_y = ox->abs_y + cam_y;
	ox->abs_z = (int)(ox->z * len);
	ox->abs_z = ox->abs_z;
}



void ft_print_oxyz2()
{
	t_vektr *ox;
	t_vektr *oy;
	t_vektr *oz;

	t_vektr *oxyz;

	//oxyz = ft_new_vektor(1, 1, 1);
//	ox = ft_new_vektor(ox0->x, ox0->y, ox0->z);
//	oy = ft_new_vektor(oy0->x, oy0->y, oy0->z);
//	oz = ft_new_vektor(oz0->x, oz0->y, oz0->z);

/*	if (ang_x != 0)
	{
		oy = ft_rot(oy, ox0, ang_x);
		oz = ft_rot(oz, ox0, ang_x);
		ang_x = 0;
	}
	else if (ang_y != 0)
	{
		ox = ft_rot(ox, oy0, ang_y);
		oz = ft_rot(oz, oy0, ang_y);
		ang_y = 0;
	}
	else if (ang_z != 0)
	{
	//	oy = ft_rot(oy, oz0, ang_z);
		ox = ft_rot(ox, oz0, ang_z);
		ang_z = 0;
	}*/
	if (ang_z != 0)
	{
		oxyz = ft_new_vektor(oz0->x, oz0->y, oz0->z);
		//oxyz = ft_new_vektor(0.9, 0.9, 0.9);
		oy0 = ft_rot(oy0, oxyz, ang_z);
		ox0 = ft_rot(ox0, oxyz, ang_z);
		//oz0 = ft_rot(oz0, oxyz, ang_z);
		ft_putchar('Z');
		free(oxyz);
	}
	if (ang_x != 0)
	{
		oxyz = ft_new_vektor(ox0->x, ox0->y, ox0->z);
		oy0 = ft_rot(oy0, oxyz, ang_x);
		//ox0 = ft_rot(ox0, oxyz, ang_x);
		oz0 = ft_rot(oz0, oxyz, ang_x);
		ft_putchar('X');
		free(oxyz);
	}
	if (ang_y != 0)
	{
		oxyz = ft_new_vektor(oy0->x, oy0->y, oy0->z);
		//oy0 = ft_rot(oy0, oxyz, ang_y);
		ox0 = ft_rot(ox0, oxyz, ang_y);
		oz0 = ft_rot(oz0, oxyz, ang_y);
		ft_putchar('Y');
		free(oxyz);
	}

/*	ox = ft_rot(ox, oz0, ang_z);
	ox = ft_rot(ox, oy0, ang_y);
	ox = ft_rot(ox, ox0, ang_x);

	oz = ft_rot(oz, oz0, ang_z);
	oz = ft_rot(oz, oy0, ang_y);
	*/

//	free(ox0);
//	free(oy0);
//	free(oz0);

//	ox0 = ox;
//	oy0 = oy;
//	oz0 = oz;

	ang_x = 0;
	ang_y = 0;
	ang_z = 0;

//	oz = ft_rot(oz, oy, ang_y);

//	oy = ft_rot(oy, ox, ang_x);
//	oz = ft_rot(oz, ox, ang_x);



	ft_ret_abs_xyz(ox0);
	ft_ret_abs_xyz(oy0);
	ft_ret_abs_xyz(oz0);


	ft_bzero(addr, 	img_width * img_hight * 4);
	draw_line_img1(cam_x, cam_y, ox0->abs_x, ox0->abs_y, 0x0000FF);
	printf("%d_%d_%d\n", ox0->abs_x, ox0->abs_y, ox0->abs_z);
	draw_line_img1(cam_x, cam_y, oy0->abs_x, oy0->abs_y, 0x00FF00);
	draw_line_img1(cam_x, cam_y, oz0->abs_x, oz0->abs_y, 0xFF0000);
	//draw_line_img(240, 240, oy_x3 + 240, oy_y3 + 240);
	//draw_line_img(240, 240, oz_x3 + 240, oz_y3 + 240);
	mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);
//	free(ox);
//	free(oy);
//	free(oz);
}


int deal_key(int key, void *param)
{
	printf("%d\n", key);

	if (key == 12)
		ang_z = ang_z + M_PI_4 / 10;
	if (key == 13)
		ang_y = ang_y + M_PI_4 / 10;
	if (key == 14)
		ang_x = ang_x + M_PI_4 / 10;
	if (key == 53)//ESC
	{
		exit(0);
		return (0);
	}
	if (key == 124)
		cam_x++;
	if (key == 123)
		cam_x--;
	if (key == 126)
		cam_y--;
	if (key == 125)
		cam_y++;
	mlx_clear_window(mlx_ptr, win_ptr);
	ft_print_oxyz2();
//	mlx_clear_window(mlx_ptr, win_ptr);
	//mlx_pixel_put(mlx_ptr, win_ptr, point_x, point_y, 0xFFFFFF);

	return (0);
}

int mouse_press(int button, int x, int y, void *param)
{
	//printf("%d\n", button);
	if (button == 1)
	{
		//mlx_clear_window(mlx_ptr, win_ptr);
		ft_bzero(addr, 	width * hight * 4);
		draw_line_img(250, 250, x, y, 0xFFFFFF);
		mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 0, 0);
		mlx_string_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF, "Hello World");
		//draw_line(250, 250, x, y);
		//mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);

	}

	return (0);
}

int mouse_move(int x, int y, void *param)
{
	//mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF);
	//mlx_clear_window(mlx_ptr, win_ptr);
	ft_bzero(addr, 	img_width * img_hight * 4);
	draw_line_img(240, 240, x - 10, y - 10, 0xFFFFFF);
	mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);
	//draw_line(250, 250, x, y);
	return (0);
}


int main()
{
	width = 500;
	hight = 500;
	point_x = width/2;
	point_y = hight/2;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, hight, "mlx 42");
	//mlx_pixel_put(mlx_ptr, win_ptr, point_x, point_y, 0xFFFFFF);
	img_width = width - 20;
	img_hight = hight - 20;
	img_ptr = mlx_new_image(mlx_ptr, img_width, img_hight);


	int bits_per_pixel = 0;
	int size_line = 0;
	int endian = 0;
	//ft_memset(bits_per_pixel, 255, 500 * 500 * 4);
	//bits_per_pixel[500 * 250] = 0xFFFFFF;

	cam_x = img_width / 2;
	cam_y = img_hight / 2;

	ox0 = ft_new_vektor(1, 0, 0);
	oy0 = ft_new_vektor(0, 1, 0);
	oz0 = ft_new_vektor(0, 0, 1);



	addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);


	//ft_memset(addr, 0xFF, 10 * 20 * 4);

	//printf("%d__%d__%d__%d\n", addr[0], addr[1], addr[2], addr[3]);
	/*
	int i = 0;
	int j = 0;
	while (j < 2)
	{
		i = 0;
		while (i < 10)
		{
			addr[(j * 40) + 4 * i + 0] = 0xFF;
			addr[(j * 40) + 4 * i + 1] = 0xFF;
			addr[(j * 40) + 4 * i + 2] = 0xFF;
			addr[(j * 40) + 4 * i + 3] = 0x00;
			i++;
		}
		j++;
	}
	*/
	//addr[0] = addr[1] = addr[2] = addr[3] = 0xFF;
	//ft_memset(addr, 0xFF, 500 * 2000);
	printf("%d_%d\n", bits_per_pixel, size_line);



/*
	int x = 0;
	int y = 0;
	int i = 0;
	while (i < hight*width - 1)
	{
		x = i % hight;
		y = i / hight;
		if (x == y)
			((char *)img_ptr)[i] = 1;//0xFFFFFF;
		i++;
	}
*/
	int ans;

	//ans = mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 0, 0);
	printf("%d\n", ans);

	mlx_hook(win_ptr, 2, 0, deal_key, (void *)0);
	//mlx_key_hook(win_ptr, deal_key, (void *)0);
	//mlx_hook(win_ptr, 4, 0, mouse_press, (void *)0);
///	mlx_hook(win_ptr, 6, 0, mouse_move, (void *)0);
	//mlx_mouse_hook(win_ptr, mouse_press, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}

//gcc -I /usr/local/include main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
//gcc -I /usr/local/include main.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit libft.a


//mlx_pixel_put.1
//int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
//int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);

//mlx.1
//void *mlx_init();

//mlx_loop.1
//int mlx_loop(void *mlx_ptr);
//int mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
//int mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param);
//int mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param);
//int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);

//mlx_new_window.1
//void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
//int mlx_clear_window(void *mlx_ptr, void *win_ptr);
//int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
