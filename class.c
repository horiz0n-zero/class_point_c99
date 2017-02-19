#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

struct class
{
	size_t	size;
	void	*(*ctor)(const void * const self, ...);
	void	(*dtor)(const void * const self);
	void	*(*copy)(const void * const self);
};

struct point
{
	const void * __class;
	int	x;
	int	y;
};

void	*ft_ctor(const void * const self, ...);
void	ft_dtor(const void * const self);
void	*ft_copy(const void * const self);
static const struct class _desc_class_point =
{
	sizeof(struct point), ft_ctor, ft_dtor, ft_copy
};

const void * const _point_describe = &_desc_class_point;

void	*ft_ctor(const void * const self, ...)
{
	struct point	*Point;
	va_list		args;

	va_start(args, self);
	Point = malloc(sizeof(struct point));
	Point->__class = _point_describe;
	Point->x = (int)va_arg(args, int);
	Point->y = (int)va_arg(args, int);
	return (Point);
}

void	ft_dtor(const void * const self)
{
	free((void*)self);
}

void	*ft_copy(const void * const self)
{
	struct point	*Point;

	Point = malloc(sizeof(struct point));
	*Point = *(struct point*)self;
	return (Point);
}

int	main(void)
{
	struct point	*Point;
	struct point	*OtherPoint;

	Point = ((struct class*)_point_describe)->ctor(Point, 5, 10);
	OtherPoint = (*(struct class**)Point)->ctor(Point, 10, 5);
	(*(struct class**)OtherPoint)->dtor(OtherPoint);
	OtherPoint = (*(struct class**)Point)->ctor(NULL, 35, 10);
	printf("Point : x(%d) y(%d), OtherPoint : x(%d) y(%d)\n", Point->x, Point->y, OtherPoint->x, OtherPoint->y);
	return (0);
}
