cmake_minimum_required(VERSION 3.17)
project(clion_lemin C)

set(CMAKE_C_STANDARD 99)

#add_executable(lemin bellman_ford.c calc_speed.c debug_functions.c
#        ft_atoi_validate_pos.c gnl.c hash.c lem_in.h main.c
#        parse_functions.c parse_input.c utils_nick.c
#        libft/ft_putstr.c libft/ft_putnbr.c libft/ft_isdigit.c
#        libft/ft_strcat.c libft/ft_strequ.c libft/ft_strdup.c
#        libft/ft_putchar.c libft/ft_strcmp.c libft/ft_strlen.c
#        libft/ft_strjoin.c utils_free.c my_cool_algo.c test_speed_calc.c utils_nick_3.c debug_func_nick.c print_result.c)
add_executable(lemin main.c bellman_ford.c calc_speed.c debug_func_nick.c
        debug_functions.c free_hash.c ft_atoi_validate_pos.c gnl.c hash.c
        insert_to_hash_functions.c lem_in.h links_functions.c my_cool_algo.c
        parse_functions.c parse_input.c print_result.c test_speed_calc.c
        utils.c utils_free.c utils_nick.c utils_nick_3.c
        libft/ft_putstr.c libft/ft_putnbr.c libft/ft_isdigit.c
        libft/ft_strcat.c libft/ft_strequ.c libft/ft_strdup.c
        libft/ft_putchar.c libft/ft_strcmp.c libft/ft_strlen.c
        libft/ft_strjoin.c)