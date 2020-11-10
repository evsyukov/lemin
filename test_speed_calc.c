#include "lem_in.h"

void	test_speed_calc()
{
	size_t	result;

	
	size_t	arr[] = {2, 7, 4, 9, 7};

	li_sort(arr, 5);
	result = do_calc_speed(27, arr, 5);
	ft_putstr("Number steps = ");
	ft_putnbr(result);
	ft_putstr("\n");

//	size_t	arr1[] = {3};
//
//	li_sort(arr1, 1);
//	result = do_calc_speed(5, arr1, 1);
//	ft_putstr("Number steps = ");
//	ft_putnbr(result);
//	ft_putstr("\n");

//	size_t	arr2[] = {4, 4};
//
//	li_sort(arr2, 2);
//	result = do_calc_speed(7, arr2, 2);
//	ft_putstr("Number steps = ");
//	ft_putnbr(result);
//	ft_putstr("\n");

//	size_t	arr3[] = {2, 7, 4, 9, 7};
//
//	li_sort(arr3, 5);
//	result = do_calc_speed(1, arr3, 5);
//	ft_putstr("Number steps = ");
//	ft_putnbr(result);
//	ft_putstr("\n");
//
//	size_t	arr4[] = {2, 7, 4, 9, 7};
//
//	li_sort(arr4, 5);
//	result = do_calc_speed(5, arr4, 5);
//	ft_putstr("Number steps = ");
//	ft_putnbr(result);
//	ft_putstr("\n");
}
