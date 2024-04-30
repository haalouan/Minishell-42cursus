/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/04/30 22:43:20 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void remove_quotes(t_list** list)
{
    int i;
    int k;
    int l;
    int j;

    i = 0;
    while (list[i])
    {
        k = 0;
        j = 0;
        //cmd
        while (list && list[i] && list[i]->cmd && list[i]->cmd[j] != '\0')
        {
            if (list && list[i] && list[i]->cmd && list[i]->cmd[j] && list[i]->cmd[j] == '\"')
            {
                j++;
                while (list && list[i] && list[i]->cmd && list[i]->cmd[j] && list[i]->cmd[j] != '\"')
                {
                    list[i]->cmd[k] = list[i]->cmd[j];
                    k++;
                    j++;
                }
                if (list && list[i] && list[i]->cmd && list[i]->cmd[j] == '\"')
                    j++;
            }
            if (list && list[i] && list[i]->cmd && list[i]->cmd[j] && list[i]->cmd[j] == '\'')
            {
                j++;
                // list[i]->cmd[k++] = list[i]->cmd[j++];
                while (list && list[i] && list[i]->cmd && list[i]->cmd[j] && list[i]->cmd[j] != '\'')
                {
                    list[i]->cmd[k] = list[i]->cmd[j];
                    k++;
                    j++;
                }
                if (list && list[i] && list[i]->cmd && list[i]->cmd[j] == '\'')
                    j++;
            }
            else if (list && list[i] && list[i]->cmd && list[i]->cmd[j] && list[i]->cmd[j] != '\"' && list[i]->cmd[j] != '\'')
            {
                list[i]->cmd[k] = list[i]->cmd[j];
                k++;
                j++;
            }
                
        }
        if (list[i] && list[i]->cmd)
            list[i]->cmd[k] = '\0';
        k = 0;
        j = 0;
        //redir
        while (list[i]->redir && list[i]->redir[j] != '\0')
        {
            if (list && list[i] && list[i]->redir && list[i]->redir[j] && list[i]->redir[j] == '\"')
            {
                j++;
                while (list && list[i] && list[i]->redir && list[i]->redir[j] && list[i]->redir[j] != '\"')
                {
                    list[i]->redir[k] = list[i]->redir[j];
                    k++;
                    j++;
                }
                j++;
            }
            if (list && list[i] && list[i]->redir && list[i]->redir[j] && list[i]->redir[j] == '\'')
            {
                
                // list[i]->redir[k++] = list[i]->redir[j++];
                j++;
                while (list && list[i] && list[i]->redir && list[i]->redir[j] && list[i]->redir[j] != '\'')
                {
                    list[i]->redir[k] = list[i]->redir[j];
                    k++;
                    j++;
                }
                j++;
            }
            else if (list && list[i] && list[i]->redir && list[i]->redir[j] && list[i]->redir[j] != '\"' && list[i]->redir[j] != '\'')
            {
                list[i]->redir[k] = list[i]->redir[j];
                k++;
                j++;
            }
        }
        if (list[i]->redir)
            list[i]->redir[k] = '\0';
        //args
        j = 0;
        while (list && list[i] && list[i]->args && list[i]->args[j])
        {
            l = 0;
            k = 0;
            while (list && list[i] && list[i]->args && list[i]->args[j] && list[i]->args[j][l])
            {
                if (list && list[i] && list[i]->args && list[i]->args[j] && list[i]->args[j][l] && list[i]->args[j][l] == '\"')
                {
                    l++;
                    while (list && list[i] && list[i]->args && list[i]->args[j][l] && list[i]->args[j][l] != '\"')
                    {
                        list[i]->args[j][k] = list[i]->args[j][l];
                        k++;
                        l++;
                    }
                    if (list && list[i] && list[i]->cmd && list[i]->cmd[j] == '\"')
                    l++;
                }
                if (list && list[i] && list[i]->args && list[i]->args[j] && list[i]->args[j][l] && list[i]->args[j][l] == '\'')
                {
                    // list[i]->args[j][k++] = list[i]->args[j][l++];
                    l++;
                    while (list && list[i] && list[i]->args && list[i]->args[j][l] && list[i]->args[j][l] != '\'')
                    {
                        list[i]->args[j][k] = list[i]->args[j][l];
                        k++;
                        l++;
                    }
                    if (list && list[i] && list[i]->cmd && list[i]->cmd[j] == '\'')
                    l++;
                }
                else if (list && list[i] && list[i]->args && list[i]->args[j] && list[i]->args[j][l] && list[i]->args[j][l] != '\"' && list[i]->args[j][l] != '\'')
                {
                    list[i]->args[j][k] = list[i]->args[j][l];
                    k++;
                    l++;
                }
            }
            if (list && list[i] && list[i]->args && list[i]->args[j])
                list[i]->args[j][k] = '\0';
            j++;
        }
        i++;
    }
}


void add_tab(char *line, char **tab, int len)
{
    int i = 0;
    if (!tab)
        exit(0);
    while (tab[i] != NULL)
        i++;
    tab[i] = malloc(len + 1);
    if (!tab[i])
        exit(0);
    ft_strncpy(tab[i], line, len);
}

void handele_word(char **le, char **tab)
{
    int i;
    char *line = *le;
    // (void)tab;
    i = 0;
    while (line[i] != '\0')
    {
        while (is_character(line[i]) == 1 && line[i] != '\0')
            i++;
        if (line[i] == '\'')
        {
            i++;
            while (line[i] != '\'' && line[i] != '\0')
                i++;
            if (line[i] == '\'')
                i++;
            if (is_character(*line) == 0 && *line != '\'' && *line != '\"')
                break;
        }
        else if (line[i] == '\"')
        {
            i++;
            while (line[i] != '\"' && line[i] != '\0')
                i++;
            if (line[i] == '\"')
                i++;
            if (is_character(line[i]) == 0 && *line != '\'' && *line != '\"')
                break;
        }
        else
            break;
    }
    *le += i;
    // int j = count_quote(line, i);
    add_tab(line , tab, i);
}


void handele_line(char **line, char **tab, t_check check)
{
    if (check.find_here_doc == 1)
    {
        add_tab(*line, tab, 2);
        *line += 2;
    }
    else if (check.find_append_op == 1)
    {
        add_tab(*line, tab, 2);
        *line += 2;
    }
    else if (check.find_pipe == 1)
    {
        add_tab(*line ,tab, 1);
        *line += 1;
    }
    else if (check.find_in_re == 1)
    {
        add_tab(*line, tab, 1);
        *line += 1;
    }
    else if (check.find_out_re == 1)
    {
        add_tab(*line, tab, 1);
        *line += 1;
    }
    else if (check.find_word == 1)
        handele_word(line, tab);
    else if (*line)
        *line += 1;
}


char **handele_parssing(char *line)
{
    int count = count_lists(line);
    printf("*-------------------------*\n");
    printf("|   nbr of cmds -> [%d]    |\n", count);
    printf("*-------------------------*\n");
    // return NULL;
    // exit(0);
    t_check check;
    int i = 0;
    char **tab = malloc(sizeof(char *) * (count + 1) + 1);
    if (!tab)
        exit(EXIT_FAILURE);
    while (i <= count)
    {
        tab[i] = NULL;
        i++;
    }
    while (*line != '\0')
    {
        check_init(&check);
        check_check(line, &check);
        handele_line(&line, tab, check);
    }
    return tab;
}

 char *ft_str_replace(const char *source, const char *pattern, const char *replacement)
{
     if ( !source || !pattern || !replacement)
    {

        return strdup(source);
    }
    size_t pattern_len = ft_strlen(pattern);
    size_t replacement_len = ft_strlen(replacement);
    
    char *occurrence = strstr(source, pattern); 
    if (!occurrence)
        return strdup(source);


    size_t new_size = ft_strlen(source) - pattern_len + replacement_len + 1;
    char *new_str = (char *)malloc(new_size);

    if (!new_str)
    {

        return NULL;
    }


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

    while (tab && tab[i])
    {
        if (tab && tab[i] == '\'' && check == 0)
        {
            i++;
            while (tab && tab[i] && tab[i] != '\'')
                i++;
            k = i;
        }
        if (tab && tab[i] == '$')
            i++;
        tab[k] = tab[i];
        i++;
        k++;
    }
    tab[i] = '\0';
    return tab;
}

void expend(char **tab, t_env *env_list)
{
    // (void)env_list;
    int i = 0;
    int j = 0;
    
    char *key = NULL;
    char *value = NULL;
    while (tab && tab[i])
    {
        j = 0;
        while (tab && tab[i][j])
        {
            if (tab && tab[i] && tab[i][j] == '\"')
            {
                j++;
                while (tab && tab[i] && tab[i][j] && tab[i][j] != '\"')
                {
                    if (tab && tab[i] && tab[i][j] == '$')
                    {
                        key = get_env_key(tab[i], j);
                        printf("%s\n", key);
                        printf("%s\n", value);
                        value = get_env_value(key, env_list);
                        if (key && value)
                        {
                            tab[i] = ft_str_replace(tab[i], key, value);
                            tab[i] = remove_$(tab[i], 1);
                        }
                    }
                    j++;
                }
            }
            if (tab && tab[i] && tab[i][j] == '\'')
            {
                j++;
                while (tab && tab[i] && tab[i][j] && tab[i][j] != '\'')
                    j++;
            }
            if (tab && tab[i] && tab[i][j] == '$')
            {
                if (tab[i][j + 1] == '\"' || tab[i][j + 1] == '\'' )
                {
                    tab[i] = remove_$(tab[i], 1);
                    break;
                }
                while ()
                key = get_env_key(tab[i], j);
                value = get_env_value(key, env_list);
                if (key && value)
                {
                    tab[i] = ft_str_replace(tab[i], key, value);
                    tab[i] = remove_$(tab[i], 1);
                }
            }
            if (tab && tab[i] && tab[i][j])
                j++;
        }
        i++;   
    }
}

int check(char **tab)
{
    int i = 0;
    if (!tab || !*tab)
        return 2;
    if (tab[0][0] == '>' || tab[0][0] == '<' || tab[0][0] == '|')
        return 1;
    while (tab[i])
    {
        if (tab[i] && tab[i][0] == '|' && tab[i + 1] && tab[i + 1][0] == '|')
            return 1;
        if (tab[i] && tab[i][0] == '<' && tab[i + 1] && tab[i + 1][0] == '<')
            return 1;
        if (tab[i] && tab[i][0] == '>' && tab[i + 1] && tab[i + 1][0] == '>')
            return 1;
        i++;
    }
    if (tab[i - 1][0] == '|' || tab[i - 1][0] == '<' || tab[i - 1][0] == '>')
        return 1;
    return 0;
}


t_list **parssing(char *line, t_env *env_list)
{
    char **tab = NULL;
    t_list **list = NULL;
    int count = 0;
    int size = 0;
    (void)env_list;
    if (ft_strlen(line) == 0)
        return NULL;
    add_history(line);
    if (count_quote(line, ft_strlen(line)) == 1)
    {
        handele_error();
        return NULL;
    }
    tab = handele_parssing(line);
    if (check(tab) == 2)
        return NULL;
    if (check(tab) == 1)
    {
        handele_error();
        return NULL;
    }
    count = count_lists(line);
    size = count_pipe(tab, count);
    list = (t_list **)malloc(sizeof(t_list *) * (size + 1) + 1);
    if (!list)
        exit(1);
    expend(tab, env_list);
    continue_parssing(list, tab, line);
    if (check_tab(list) == 1)
    {
        handele_error();
        return NULL;
    }
    remove_quotes(list);
    print_tab(tab, line, list);
    return list;
}