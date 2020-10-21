#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void map_init(struct map_st *map)
{
    memset(map, 0, sizeof(struct map_st));
}

void map_add(struct map_st *map, char *key, char *value)
{
    strcpy(map->table[map->count].key, key);
    strcpy(map->table[map->count].value, value);
    map->count++;
}

char * map_lookup(struct map_st *map, char *s)
{
    static char buffer[MAP_VALUE_LEN+1];
    char is_match = 0;
    if (s[0] == '\0')
        return NULL;

    int i, j = 0;
    while (*s != '\0')
    {
        for (i = 0; i < map->count; i++)
        {
            // compare the substring with the key
            if (strstr(s, map->table[i].key) == s)
            {
                strcpy(&buffer[j], map->table[i].value);
                j += strlen(map->table[i].value);
                s += strlen(map->table[i].key);
                is_match = 1;
                break;
            }
        }

        if (!is_match)
            buffer[j++] = *s++;
        is_match = 0;
    }

    buffer[j] = '\0';
    return buffer;
}

int main(int argc, char **argv)
{
    FILE *input_file, *output_file;
    struct map_st map;
    char *value;
    char str[MAP_KEY_LEN+1], ch, index = 0;
    if (argc < 5)
    {
        printf("too few arguments\n");
        return -1;
    }

    map_init(&map);

    for (int i = 3; i < argc - 1; i=i+2)
    {
        map_add(&map, argv[i], argv[i+1]);
    }

    if ((input_file = fopen(argv[1], "r")) == NULL)
    {
        printf("not found input file\n");
        return -1;
    }

    if ((output_file = fopen(argv[2], "wb")) == NULL)
    {
        printf("cannot create output file\n");
        return -1;
    }

    memset(str, 0, sizeof(str));
    while((ch = fgetc(input_file)) != EOF)
    {
        if (ch == ' ' || ch == '\n')
        {
            if ((value = map_lookup(&map, str)) != NULL)
            {
                fputs(value, output_file);
            }
            fputc(ch, output_file);
            index = 0;
        }
        else
        {
            str[index] = ch;
            index++;
            str[index] = '\0';
        }
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
