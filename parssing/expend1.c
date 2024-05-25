/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:12 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/25 16:24:45 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *protect_env(char *str, int key)
{
    char *value;
    int i = 0;
    int j = 0;

    value = malloc(ft_strlen(str) + 2 + 1);
    value[j] = '\"';
    j++;
    if (key == 1)
    {
        while (str[i] == ' ' || str[i] == '\t')
        i++;
    }
    while (str && str[i])
    {
        value[j] = str[i];
        i++;
        j++;
    }
    if (key == 1 && (value[j - 1] == ' ' || value[j - 1] == '\t'))
    {
        j--;
        while (value[j] == ' ' || value[j] == '\t')
            j--;
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
    new = malloc(ft_strlen(str[i]) + 3);
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
    new[k] = '\"';
    new[k + 1] = '\0';
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

char *protect_new_str(char *str)
{
    char *s;
    int i = 0;
    int j = 1;

    s = NULL;
    s = malloc(ft_strlen(str) + 3);
    if (!s || !str)
        return str;
    s[0] = '\"';
    while (str && str[i])
    {
        s[j] = str[i];
        i++;
        j++;
    }
    s[j] = '\"';
    s[j + 1] = '\0';
    return s;
}

char *protect_new_tab(char *str)
{
    int i = 1;
    int k = 1;
    char *s = NULL;
    s = malloc(ft_strlen(str) + 1);
    if (!s)
        exit(EXIT_FAILURE);
    while (str && str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        s[0] = '\"';
        s[k] = str[i];
        k++;
        i++;
    }
    s[k] = '\0';
    return s;
}

char **change_tab(char **old_tab, char *str)
{
    int i = 0;
    char **new_str = NULL;
    new_str = ft_split(str, ' ');
    if (!new_str)
        return old_tab;
    // new_str = add_quotes(new_str);
    int size = ft_size(old_tab);
    int size2 = ft_size(new_str);
    if (size2 <= 1)
        return old_tab;
    i = 0;
    int j = 0;
    char **new_tab = NULL;
    new_tab = malloc(sizeof(char *) * (size + size2 + 1) + 1);
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
                if (new_str[j][0] == '>' || new_str[j][0] == '<' || new_str[j][0] == '|')
                    new_str[j] = protect_new_str(new_str[j]);
                new_tab[i] = new_str[j];
                // new_tab[i] = protect_new_tab(new_tab[i]);
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
    char **new_tab = NULL;
    new_tab = malloc(sizeof(char *) * (count + 1) + 1);
    if (!new_tab)
        return NULL;
    while (i <= count)
    {
        new_tab[i] = NULL;
        i++;
    }
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

int search_for_value(char *str, char *s)
{
    int i = 0;
    while (str && str[i] && str[i] != '=')
        i++;
    if (str[i] != '=')
        return 1;
    if (ft_strncmp(str, s, i) == 0)
        return 1;
    return 0;
}
char *expend_digit(char *str)
{
    int i = 1;

    while (str[i])
    {
        if (ft_isdigit(str[i]) == 1)
            i++;
        break;
    }
    return (str + i);
}

char **continue_expend(char **tab, int i, int *j, t_env *env_list, int in_her_doc)
{
    char *key;
    char *value;
    key = 0;
    value = 0;
    if (ft_isdigit(tab[i][*j + 1]) == 1)
    {
        tab[i] = expend_digit(tab[i]);
        return tab;
    }
    key = get_env_key(tab[i], *j);
    value = get_env_value(key, env_list);
    if (value)
        value = protect_env(value, 1);
    if (key && value)
    {
        tab[i] = ft_str_replace(tab[i], key, value);
        tab[i] = remove_$(tab[i], 1, value);
        if (search_for_value(tab[i], value) == 1 && in_her_doc == 0)
            tab = change_tab(tab, tab[i]);
        return tab;
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
char **expend(char **tab, t_env *env_list, int in_here_doc)
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
                while (tab && tab[i] && tab[i][j] && tab[i][j] != '\"') 
                {
                    if (tab && tab[i] && tab[i][j] == '$' && tab[i][j + 1] != '\0' && tab[i][j + 1] != '\"')
                    {
                        tab = expend_in_double_quote(tab, i, &j, env_list);
                        // j++;
                        // return tab;
                        // continue;
                        break;
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
                // return tab;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && tab[i][j + 1] != '\"' && tab[i][j + 1] != '\'' && tab[i][j + 1] != '\0')
            {
                if (ft_strcmp(tab[i - 1], "<<") == 0)
                    break;
                tab = continue_expend(tab, i, &j, env_list, in_here_doc);
                // return tab;
                // continue;
                // break;
            }
            else if (tab && tab[i] && tab[i][j] == '$' && (tab[i][j + 1] == '\'' || tab[i][j + 1] == '\"'))
            {
                tab[i] = remove_$(tab[i], 1, "1337");
                // return tab;
                // continue;
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