/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:58 by haalouan          #+#    #+#             */
/*   Updated: 2024/05/11 21:56:39 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_str_replace(const char *tab, const char *key, const char *value)
{
    size_t key_len;
    size_t value_len;
    char *occurrence;
    size_t new_size;
    
    if ( !tab || !key || !value)
        return ft_strdup(tab);
    key_len = ft_strlen(key);
    value_len = ft_strlen(value);
    occurrence = ft_strstr(tab, key);
    if (!occurrence)
        return ft_strdup(tab);
    new_size = ft_strlen(tab) - key_len + value_len + 1;
    char *new_str = (char *)malloc(new_size);
    if (!new_str)
        return NULL;
    memcpy(new_str, tab, occurrence - tab);
    new_str[occurrence - tab] = '\0';
    strcat(new_str, value);
    strcat(new_str, occurrence + key_len);
    return new_str;
}

char *add_$(char *str)
{
    char *value;
    int i = 0;
    int j = 0;

    value = malloc(ft_strlen(str) + 2);
    if (!value)
        return NULL;
    value[i] = '$';
    i++;
    while (str[j])
    {
        value[i] = str[j];
        i++;
        j++;
    }
    value[i] = '\0';
    return value;
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
            // value = add_$(value);
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

char *remove_$(char *tab, int check, char *value)
{
    int i = 0;
    int k = 0;
    int chk = 0;
    while (tab && tab[i] != '\0')
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
        if (tab && (tab[i] == ' ' || tab[i] == '\t') && value && value[0] != ' ')
        {
            tab[k] = ' ';
            k++;

            while (tab[i] == ' ' || tab[i] == '\t')
                i++;
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


char **expend_in_double_quote(char **tab, int i, int *j, t_env *env_list)
{
    char *key;
    char *value;

    key = 0;
    value = 0;
    // while (tab && tab[i] && tab[i][*j])
    // {
        if (tab && tab[i] && tab[i][*j] == '$' && tab[i][*j + 1] != '\"')
        {
            key = get_env_key(tab[i], *j);
            value = get_env_value(key, env_list);
            if (key && value)
            {
                tab[i] = ft_str_replace(tab[i], key, value);
                tab[i] = remove_$(tab[i], 1, value);
                tab = change_tab(tab, tab[i] + *j);
                int i = 0;
                while (tab[i])
                {
                    printf("%s\n", tab[i]);
                    i++;
                }
            }
            else
            {
                tab[i] = ft_str_replace(tab[i], key, "");
                tab[i] = remove_$(tab[i], 1, value);
            }
        }
    //     j++;
    // }
    return tab;
}
