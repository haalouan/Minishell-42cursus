/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:12 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/13 19:49:51 by haalouan         ###   ########.fr       */
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

char **change_tab(char **old_tab, char *str)
{
    int i = 0;
    i  = 0;
    i++;
    while (str && (str[i] == ' ' || str[i] == '\t'))
    {
        i++;
        str = str + i - 1;
        str[0] = '\"';
    }
    char **new_str = ft_split(str, ' ');
    new_str = add_quotes(new_str);
    int size = ft_size(old_tab);
    int size2 = ft_size(new_str);
    i = 0;
    int j = 0;
    char **new_tab = malloc(sizeof(char *) * (size + size2 + 1) + 1);
    if (!new_tab)
        return NULL;
    while (i <= size + size2)
    {
        new_tab[i] = NULL;
        i++;
    }
    i = 0;
    int k = 0;
    while (i < size + size2)
    {
        if (ft_strcmp(old_tab[k], str) == 0)
        {
            while (i < size + size2 && new_str && new_str[j])
            {
                new_tab[i] = new_str[j];
                j++;
                i++;
            }
            if (old_tab[k] && old_tab[k + 1])
                k++;
            else
                break;
        }
        if (old_tab[k])
        {
            new_tab[i] = old_tab[k];
            i++;
            k++;
        }
        else
            break;
    }
    new_tab[i] = NULL;
    return new_tab;
}

char **ft_realloc(char **tab, char *str)
{
    int i = 0;
    int j = 0;
    int count = 0;
    while (tab && tab[count])
        count++;
    char **new_tab = malloc(sizeof(char *) * (count + 1) + 1);
    if (!new_tab)
        return NULL;
    i = 0;
    while (i < count)
    {
        if (ft_strcmp(tab[i], str) == 0)
            i++; 
        new_tab[j] = tab[i];
        i++;
        j++;
    }
    new_tab[j] = NULL;
    return new_tab;
}

char **continue_expend(char **tab, int i, int *j, t_env *env_list)
{
    char *key;
    char *value;

    key = 0;
    value = 0; key = get_env_key(tab[i], *j);
    value = get_env_value(key, env_list);
    if (value)
        value = protect_env(value);
    if (key && value)
    {
        tab[i] = ft_str_replace(tab[i], key, value);
        tab[i] = remove_$(tab[i], 1, value);
        if (ft_strcmp(tab[0], "export") == 0)
            tab = change_tab(tab, tab[i] + *j);
        else
            tab = change_tab(tab, tab[i]);
    }
    else
    {
        tab[i] = ft_str_replace(tab[i], key, "");
        tab[i] = remove_$(tab[i], 1, value);
        if (tab[i][0] == '\0')
            tab = ft_realloc(tab, tab[i]);
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
                while (tab && tab[i] && tab[i][j] && tab[i][j] != '\"') {
                    // printf("{%s}\n", tab[i] + j);
                    if (tab && tab[i] && tab[i][j] == '$')
                    {
                        tab = expend_in_double_quote(tab, i, &j, env_list);
                        // return tab;
                        // continue;
                        // break;
                    }
                    else
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
                // return tab;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && tab[i][j + 1] != '\"' && tab[i][j + 1] != '\'')
            {
                tab = continue_expend(tab, i, &j, env_list);
                // return tab;
                // continue;
                // break;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && (tab[i][j + 1] == '\'' || tab[i][j + 1] == '\"'))
            {
                tab[i] = remove_$(tab[i], 1, "1337");
                // return tab;
                continue;
            }
            else if (tab && tab[i] && tab[i][j])
                j++;
        } 
        i++;
    }
    // i = 0;
    // while (tab[i] != NULL)
    // {
    //     printf("(%s)\n", tab[i]);
    //     i++;
    // }
    return tab;
}