/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:12 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/11 22:13:34 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *protect_env(char *str)
{
    char *value;
    int i = 0;
    int j = 0;

    value = malloc(ft_strlen(str) + 2 + 1);
    value[j] = '\"';
    j++;
    while (str && str[i])
    {
        value[j] = str[i];
        i++;
        j++;
    }
    value[j] = '\"';
    j++;
    value[j] = '\0';
    return value;
}

int ft_size(char **tab)
{
    int i = 0;
    while (tab && tab[i])
        i++;
    return i;
}

char **add_quotes(char **str)
{
    char *new;

    int i = 0;
    int j = 0;
    int k = 0;
    while (str && str[i])
        i++;
    i--;
    new = malloc(ft_strlen(str[i]) + 2);
    if (!new)
        return NULL;
    new[k] = '\"';
    k++;
    while (str && str[i] && str[i][j])
    {
        new[k] = str[i][j];
        k++;
        j++;
    }
    new[k] = '\0';
    str[i] = ft_substr(new, 0, ft_strlen(new));
    return str;
}

int count_str(char **str)
{
    int i= 0;

    while (str && str[i])
    {
        i++;
    }
    return i;
}

// char *ft_copy(char *str, char *str2, char *str3)
// {
//     int i=0;
//     str = malloc(ft_strlen(str2) + 1);
//     if (!str)
//         return NULL;
//     while (str && str[i] && str2 && str2[i] && str3)
//     {
//         if (str2 + i && str3 && ft_strcmp(str2 + i, str3) == 0)
//         {
//             str[i] = '\0';
//             break;
//         }
//         str[i] = str2[i];
//         i++;
//     }
//     // printf("****%s\n", str);
//     // printf("****%s\n", str2);
//     // printf("****%s\n", str3);
//     return str;
// }

char **change_tab(char **old_tab, char *str)
{
    char **new_str = ft_split(str, ' ');
    new_str = add_quotes(new_str);
    int size = ft_size(old_tab);
    int size2 = ft_size(new_str);
    int i = 0;
    int j = 0;
    char **new_tab = malloc(sizeof(char *) * (size + size2 + 1) + 1);
    if (!new_tab)
        return NULL;
    while (i < size + size2)
    {
        new_tab[i] = NULL;
        i++;
    }
    i = 0;
    while (i < size + size2)
    {
        if (ft_strcmp(old_tab[i], str) == 0 && count_str(new_str) != 1)
        {
            while (i < size + size2)
            {
                new_tab[i] = new_str[j];
                j++;
                i++;
            }
            break;
        }
        // new_tab[i] = ft_copy(new_tab[i], old_tab[i], str);
        new_tab[i] = old_tab[i];
        printf("+++%s\n", new_tab[i]);
        printf("+++%s\n", str);
        i++;
    }
    new_tab[i] = NULL;
    return new_tab;
}

char **continue_expend(char **tab, int i, int *j, t_env *env_list)
{
    char *key;
    char *value;

    key = 0;
    value = 0;
    key = get_env_key(tab[i], *j);
    value = get_env_value(key, env_list);
    value = protect_env(value);
    if (key && value)
    {
        tab[i] = ft_str_replace(tab[i], key, value);
        tab[i] = remove_$(tab[i], 1, value);
        tab = change_tab(tab, tab[i] + *j);
    }
    else
    {
        tab[i] = ft_str_replace(tab[i], key, "");
        tab[i] = remove_$(tab[i], 1, value);
    }
    return tab;
}
char **expend(char **tab, t_env *env_list)
{
    int i;
    int j;

    i = 0;
    while (tab && tab[i])
    {
        j = 0;
        while (tab && tab[i] && tab[i][j])
        {
            if (tab && tab[i] && tab[i][j] == '\"')
            {
                j++;
                while (tab && tab[i] && tab[i][j] != '\"')
                {
                    if (tab && tab[i] && tab[i][j] == '$')
                    {
                        tab = expend_in_double_quote(tab, i, &j, env_list);
                        return tab;
                    }
                    j++;
                }
                if (tab && tab[i] && tab[i][j] == '\"')
                    j++;
            }
            else if (tab && tab[i] && tab[i][j] == '\'')
            {
                j++;
                while (tab && tab[i] && tab[i][j] && tab[i][j] != '\'')
                    j++;
                if (tab && tab[i] && tab[i][j] == '\'')
                    j++;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && tab[i][j + 1] != '\"' && tab[i][j + 1] != '\'')
            {
                tab = continue_expend(tab, i, &j, env_list);
                return tab;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && (tab[i][j + 1] == '\'' || tab[i][j + 1] == '\"'))
            {
                tab[i] = remove_$(tab[i], 1, "1337");
            }
            else if (tab && tab[i] && tab[i][j])
                j++;
        } 
        i++;
    }
    return tab;
}