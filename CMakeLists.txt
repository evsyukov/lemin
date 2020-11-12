cmake_minimum_required(VERSION 3.17)
project(clion_lemin C)

set(CMAKE_C_STANDARD 99)

add_executable(lemin bellman_ford.c bfs.c calc_speed.c debug_functions.c
        dijkstra.c ft_atoi_validate_pos.c gnl.c hash.c lem_in.h main.c
        parse_functions.c parse_input.c pathfinder.c utils_nick.c
        libft/ft_putstr.c libft/ft_putnbr.c libft/ft_isdigit.c
        libft/ft_strcat.c libft/ft_strequ.c libft/ft_strdup.c
        libft/ft_putchar.c libft/ft_strcmp.c libft/ft_strlen.c
        libft/ft_strjoin.c utils_nick_2.c my_cool_algo.c test_speed_calc.c utils_nick_3.c)
