/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <nmustach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:35:58 by nmustach          #+#    #+#             */
/*   Updated: 2020/11/10 23:54:18 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    del_from_top(t_list **top_node)
{
    t_list *to_del;
    to_del = *top_node;
    *top_node = (*top_node)->prev;
    if (*top_node != NULL)
    (*top_node)->next = NULL;
    free(to_del);
}
void    add_new(t_list **node, int val)
{
    t_list *old;
    if (*node == NULL)
    {
        *node = malloc(sizeof(t_list));
        (*node)->next = NULL;
        (*node)->prev = NULL;
        (*node)->val = val;
        (*node)->index = 0;
        return ;
    }
    old = *node;
    *node = malloc(sizeof(t_list));
    (*node)->prev = NULL;
    (*node)->val = val;
    (*node)->next = old;
    old->prev = *node;
}

t_hash    **clean_path(t_path *path, int p_len)
{
        t_path *next_node;

        int i = 0;
        t_hash **nodes_arr;
        next_node = path->next;
        MFAIL((nodes_arr = malloc(sizeof(*nodes_arr) * p_len)));
        while (path)
        {
            if (!check_nodenames_is_family(path->node->node_name, next_node->node->node_name))
                {
                    nodes_arr[i++] = path->node;
                }
                
            path = path->next;
            next_node = next_node->next;
            if (!next_node)
           {    
            //printf("%s->", path->node->node_name);
            nodes_arr[i++] = path->node;
            //FCNT(free(nodes_arr));
            
            return (nodes_arr);
           }
        }
    return (nodes_arr);
}

size_t  get_path_len(t_path *path)
{
    size_t i;
    
    i = 0;

    while (path)
    {
        path = path->next;
        i++;
    }
    return (i);
}

void    print_path_arr(t_hash **arr, size_t path_len)
{
        size_t i = 0;
        
        i = 0;
        while (i < path_len)
            printf("%s->", arr[i++]->node_name);
}

void    print_move(t_list *q_top, t_hash **arr)
{
    while(q_top)
    {
        printf("\nL%d-%s", q_top->val, arr[q_top->index]->node_name);
        q_top->index++;
        q_top = q_top->prev;
    }
    
}





void    move_ants(t_hash **arr, size_t arr_size, t_graph *graph)
{     
    
    size_t num_ants_end;
    t_list *q_top;
    t_list *q_bottom = NULL;
    size_t ant_cnt;
    size_t num_ants_st = graph->ants_num;

    num_ants_end = 0;
    ant_cnt = 1;
    (void)(arr_size);

    add_new(&q_bottom, ant_cnt);
    q_top = q_bottom;
    num_ants_st--;
    ant_cnt++;
    print_move(q_top, arr);
    printf("\n");
    
    while (q_top){
    if (q_top->index + 1 > arr_size)
    del_from_top(&q_top);
    if (num_ants_st > 0)
    add_new(&q_bottom, ant_cnt);
    print_move(q_top, arr);
    ant_cnt++;
    num_ants_st--;
    printf("\n");
    
    }
    
}




void    delete_double_nodes(t_graph *graph)
{
    t_paths *paths;
    t_path *path;
    t_hash **arr;
    paths = graph->begin_path;
     
    size_t path_len;
    
    while(paths)
    {
        path = paths->path;
        path_len = get_path_len(path) / 2;
        arr = clean_path(path->next, path_len);
        paths = paths->next;
        printf("\n");
        //print_path_arr(arr, path_len);
        printf("\n");
        move_ants(arr, path_len, graph);
    }
    printf("\n");
}