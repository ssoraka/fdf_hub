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
int perspect = 20;

int point_x;
int point_y;

char *addr;
int len = 100;

double ang_x = 0;
double ang_y = 0;
double ang_z = 0;





typedef struct		s_vektr
{
	int abs_x;
	int abs_y;
	int abs_z;
	int color;
	double x;
	double y;
	double z;
	int otn_x;
	int otn_y;
	int otn_z;
	struct s_vektr *next;
	struct s_vektr *parent;
}					t_vektr;

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
	struct s_vektr *p1;
	struct s_vektr *p2;
	struct s_line *next;
}					t_line;


t_vektr *ox0;
t_vektr *oy0;
t_vektr *oz0;
t_vektr *o0;

t_line *begin_list;
t_vektr *points;

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


int draw_line_img(t_vektr *p1, t_vektr *p2, int color)
{
	t_line *line;

	line = (t_line *)malloc(sizeof(t_line));
	line->x1 = p1->abs_x;
	line->y1 = p1->abs_y;
	line->x2 = p2->abs_x;
	line->y2 = p2->abs_y;
	line->color = color;
	line->diry = ft_znak(p2->abs_y - p1->abs_y);
	line->dirx = ft_znak(p2->abs_x - p1->abs_x);
	line->deltay = line->diry * (p2->abs_y - p1->abs_y);
	line->deltax = line->dirx * (p2->abs_x - p1->abs_x);
	if (line->deltax >= line->deltay)
	{
		draw_line_img_lower_45_wu(line);
	}
	else
	{
		draw_line_img_over_45_wu(line);
	}
	free(line);
	return (0);
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
	double cosa;
	double sina;
	double temp_x;
	double temp_y;
	double temp_z;

	if (ang == 0)
		return (ox);
	cosa = cos(ang);
	sina = sin(ang);
	temp_x = ox->x * (cosa + (1 - cosa) * oy->x * oy->x);
	temp_x = temp_x + ox->y * ((1 - cosa) * oy->x * oy->y - sina * oy->z);
	temp_x = temp_x + ox->z * ((1 - cosa) * oy->x * oy->z + sina * oy->y);
	temp_y = ox->x * ((1 - cosa) * oy->y * oy->x + sina * oy->z);
	temp_y = temp_y + ox->y * (cosa + (1 - cosa) * oy->y * oy->y);
	temp_y = temp_y + ox->z * ((1 - cosa) * oy->y * oy->z - sina * oy->x);
	temp_z = ox->x * ((1 - cosa) * oy->z * oy->x - sina * oy->y);
	temp_z = temp_z + ox->y * ((1 - cosa) * oy->z * oy->y + sina * oy->x);
	temp_z = temp_z + ox->z * (cosa + (1 - cosa) * oy->z * oy->z);
	ox->x = temp_x;
	ox->y = temp_y;
	ox->z = temp_z;
	ft_norm_vektor(ox);
	return (ox);
}


t_vektr *ft_new_vektor(double x, double y, double z)
{
	t_vektr *tmp;

	tmp = (t_vektr *)malloc(sizeof(t_vektr));
	tmp->x = x;
	tmp->y = y;
	tmp->z = z;
	tmp->otn_x = (int)x;
	tmp->otn_y = (int)y;
	tmp->otn_z = (int)z;
	tmp->color = 0xFFFFFF;
	tmp->next = NULL;
	tmp->parent = NULL;
	return (tmp);
}

t_line *ft_new_line(t_vektr *p1, t_vektr *p2, int color)
{
	t_line *line;

	if (p1 == NULL || p2 == NULL)
		return (NULL);
	line = (t_line *)malloc(sizeof(t_line));
	if (line == NULL)
		return (NULL);
	line->x1 = p1->abs_x;
	line->y1 = p1->abs_y;
	line->x2 = p2->abs_x;
	line->y2 = p2->abs_y;
	line->diry = ft_znak(p2->abs_y - p1->abs_y);
	line->dirx = ft_znak(p2->abs_x - p1->abs_x);
	line->deltay = line->diry * (p2->abs_y - p1->abs_y);
	line->deltax = line->dirx * (p2->abs_x - p1->abs_x);
	if (color == 0)
		line->color = p1->color;
	else
		line->color = color;
	return (line);
}

void ft_ret_abs_xyz(t_vektr *ox)
{
	ox->otn_x = (int)(ox->x * len);
	ox->abs_x = ox->otn_x + cam_x;
	ox->otn_y = (int)(ox->y * len);
	ox->abs_y = ox->otn_y + cam_y;
	ox->otn_z = (int)(ox->z * len);
	ox->abs_z = ox->otn_z;
}



void ft_print_oxyz2()
{
	if (ang_z != 0)
	{
		oy0 = ft_rot(oy0, oz0, ang_z);
		ox0 = ft_rot(ox0, oz0, ang_z);
	}
	if (ang_x != 0)
	{
		oy0 = ft_rot(oy0, ox0, ang_x);
		oz0 = ft_rot(oz0, ox0, ang_x);
	}
	if (ang_y != 0)
	{
		ox0 = ft_rot(ox0, oy0, ang_y);
		oz0 = ft_rot(oz0, oy0, ang_y);
	}
	ang_x = 0;
	ang_y = 0;
	ang_z = 0;

	ft_ret_abs_xyz(ox0);
	ft_ret_abs_xyz(oy0);
	ft_ret_abs_xyz(oz0);
	ft_ret_abs_xyz(o0);


	ft_bzero(addr, 	img_width * img_hight * 4);
	//draw_line_img1(cam_x, cam_y, ox0->abs_x, ox0->abs_y, 0x0000FF);
	//printf("%d_%d_%d\n", ox0->abs_x, ox0->abs_y, ox0->abs_z);
	//draw_line_img1(cam_x, cam_y, oy0->abs_x, oy0->abs_y, 0x00FF00);
	//draw_line_img1(cam_x, cam_y, oz0->abs_x, oz0->abs_y, 0xFF0000);
	draw_line_img(o0, ox0, 0x0000FF);
	draw_line_img(o0, oy0, 0x00FF00);
	draw_line_img(o0, oz0, 0xFF0000);

	//mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);

}



void ft_change_points()
{
	t_vektr *p;

	p = points;
	while (p)
	{
		p->abs_z = ox0->otn_z * p->otn_x + oy0->otn_z * p->otn_y + oz0->otn_z * p->otn_z;
		p->abs_x = ox0->otn_x * p->otn_x + oy0->otn_x * p->otn_y + oz0->otn_x * p->otn_z;
		p->abs_y = ox0->otn_y * p->otn_x + oy0->otn_y * p->otn_y + oz0->otn_y * p->otn_z;
		//персппектива
		//p->abs_x = p->abs_x - p->abs_z * ft_znak(p->abs_x) / (perspect);
		//p->abs_y = p->abs_y - p->abs_z * ft_znak(p->abs_y) / (perspect);
		p->abs_x = p->abs_x + cam_x;
		p->abs_y = p->abs_y + cam_y;
		p = p->next;
	}
}


void ft_print_points()
{
	t_vektr *point;

	point = points;
	while (point->next)
	{
		draw_line_img(point, point->next, 0xFFFFFF);
		point = point->next;
	}

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
	if (key == 35)
	{
		perspect++;
		if (perspect == 0)
			perspect++;
	}
	if (key == 31)
	{
		perspect--;
		if (perspect == 0)
			perspect--;
	}
	printf("%d\n", perspect);
	mlx_clear_window(mlx_ptr, win_ptr);
	ft_print_oxyz2();

	ft_change_points();
	ft_print_points();
	mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);

	return (0);
}

int mouse_press(int button, int x, int y, void *param)
{
	//printf("%d\n", button);
	if (button == 1)
	{
		//mlx_clear_window(mlx_ptr, win_ptr);
		ft_bzero(addr, 	width * hight * 4);
		draw_line_img1(250, 250, x, y, 0xFFFFFF);
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
	draw_line_img1(240, 240, x - 10, y - 10, 0xFFFFFF);
	mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, 10, 10);
	//draw_line(250, 250, x, y);
	return (0);
}


void ft_return_lines(t_line **begin)
{
	t_vektr *p1;
	t_vektr *p2;
	t_vektr *p3;
	t_vektr *p4;
	t_vektr *p5;
	t_vektr *p6;
	t_vektr *p7;
	t_vektr *p8;
	t_vektr *p9;
	t_vektr *p10;

	t_line *l1;
	t_line *l2;
	t_line *l3;
	t_line *l4;


	p1 = ft_new_vektor(-1, -1, 1);
	p2 = ft_new_vektor(1, -1, 1);
	p3 = ft_new_vektor(1, 1, 1);
	p4 = ft_new_vektor(-1, 1, 1);
	p5 = ft_new_vektor(-1, -1, 1);

	p6 = ft_new_vektor(-1, -1, -1);
	p7 = ft_new_vektor(1, -1, -1);
	p8 = ft_new_vektor(1, 1, -1);
	p9 = ft_new_vektor(-1, 1, -1);
	p10 = ft_new_vektor(-1, -1, -1);

	points = p1;
	p1->next = p2;
	p2->next = p3;
	p3->next = p4;
	p4->next = p5;
	p5->next = p6;
	p6->next = p7;
	p7->next = p8;
	p8->next = p9;
	p9->next = p10;

	/*l1 = ft_new_line(p1, p2, 0);
	l2 = ft_new_line(p2, p3, 0);
	l3 = ft_new_line(p3, p4, 0);
	l4 = ft_new_line(p4, p1, 0);

	l1->next = l2;
	l2->next = l3;
	l3->next = l4;
	*begin = l1;*/

}



int ft_create_window(void)
{
	width = 500;
	hight = 500;
	point_x = width/2;
	point_y = hight/2;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, hight, "mlx 42");

	return (0);
}

int ft_create_img(void)
{
	img_width = width - 20;
	img_hight = hight - 20;
	img_ptr = mlx_new_image(mlx_ptr, img_width, img_hight);
	cam_x = img_width / 2;
	cam_y = img_hight / 2;

	return (0);
}

int main()
{
	ft_return_lines(&begin_list);
	ft_create_window();
	ft_create_img();
	int bits_per_pixel = 0;
	int size_line = 0;
	int endian = 0;
	addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

	ox0 = ft_new_vektor(1, 0, 0);
	oy0 = ft_new_vektor(0, 1, 0);
	oz0 = ft_new_vektor(0, 0, 1);
	o0 = ft_new_vektor(0, 0, 0);


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
