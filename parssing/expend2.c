/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:58 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/08 19:24:02 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_str_replace(const char *source, const char *pattern, const char *replacement)
{
    size_t pattern_len;
    size_t replacement_len;
    char *occurrence;
    size_t new_size;
    
    if ( !source || !pattern || !replacement)
        return ft_strdup(source);
    pattern_len = ft_strlen(pattern);
    replacement_len = ft_strlen(replacement);
    occurrence = ft_strstr(source, pattern); 
    if (!occurrence)
        return ft_strdup(source);
    new_size = ft_strlen(source) - pattern_len + replacement_len + 1;
    char *new_str = (char *)malloc(new_size);
    if (!new_str)
        return NULL;
    memcpy(new_str, source, occurrence - source);
    new_str[occurrence - source] = '\0';
    strcat(new_str, replacement);
    strcat(new_str, occurrence + pattern_len);
    return new_str;
}


char *get_env_value(char *key, t_env *export_i)
{
    t_env *tmp;
    char *value;
    // int i = 0;

    if (!key)
        return NULL;
    tmp = export_i;
    while (tmp)
    {
        if (!strcmp(tmp->key, key))
        {
            value = strdup(tmp->value);
            return (value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

char *get_env_key(char *str, int i)
{
    char *key = NULL;
    if (!str)
        return NULL;
    while (str && str[i] && str[i] != '$')
        i++;
    if (str && str[i] == '$')
    {
        i++;
        int key_start = i;
        while (str && str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            i++;
        key = (char *)malloc((i - key_start + 1) * sizeof(char)); // Exclude the last '$' from the key length
        if (!key)
            exit(EXIT_FAILURE);
        strncpy(key, &str[key_start], i - key_start);
        key[i - key_start] = '\0';
    }
    return (key);
} 

char *remove_$(char *tab, int check)
{
    int i = 0;
    int k = 0;
    int chk = 0;

    while (tab && tab[i])
    {
        if (tab && tab[i] == '\'' && check == 0)
        {
            i++;
            while (tab && tab[i] && tab[i] != '\'')
                i++;
            k = i;
        }
        if (tab && tab[i] == '$' && chk == 0)
        {
            i++;
            chk = 1;
        }
        tab[k] = tab[i];
        if (tab[i])
        {
            i++;
            k++;
        }
        else
            break;

    }
    if (tab[k])
        tab[k] = '\0';
    return tab;
}


int expend_in_double_quote(char **tab, int i, int j, t_env *env_list)
{
    char *key;
    char *value;

    key = 0;
    value = 0;
    while (tab && tab[i] && tab[i][j] && tab[i][j] != '\"')
    {
        if (tab && tab[i] && tab[i][j] == '$')
        {
            key = get_env_key(tab[i], j);
            value = get_env_value(key, env_list);
            if (key && value)
            {
                tab[i] = ft_str_replace(tab[i], key, value);
                tab[i] = remove_$(tab[i], 1);
            }
            else
            {
                tab[i] = ft_str_replace(tab[i], key, "");
                tab[i] = remove_$(tab[i], 1);
            }
        }
        j++;
    }
    return j;
}
