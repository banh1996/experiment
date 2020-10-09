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
    memcpy(map->table[map->count].key, key);
    memcpy(map->table[map->count].value, value);
    map->count++;
}

char * map_lookup(struct map_st *map, char ch)
{
    for (int i = 0; i < map->count; i++)
    {
        if (map->table[i].key[map->ch_match_num[i]] == ch)
        {
            map->ch_match_num[i]++;
            if (map->ch_match_num[i] == 1)
                map->curent_match_count++;
            if (map->ch_match_num[i] == sizeof(map->table[i].key))
                return map->table[i].key;
        }
        else
        {
            if (map->table[i].key[0] == ch)
                map->ch_match_num[i] = 1;
            else
                map->ch_match_num[i] = 0;    
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    FILE *input_file, *output_file;
    struct map_st map;
    char *value;
    char *key;
    char str[MAP_KEY_LEN], ch;
    if (argc < 4)
    {
        printf("lack of arguments\n");
        return -1;
    }

    map_init(&map);

    for (int i = 2; i < argc; i=i+2)
    {
        map_add(&map, argv[i], argv[i+1]);
    }
    key = "year";
    value = map_lookup(&map, key);

    if ((input_file = fopen(argv[0], "r")) == NULL)
    {
        printf("not found input file\n");
        return -1;
    }

    if ((output_file = fopen(argv[1], "wb")) == NULL)
    {
        printf("cannot create output file\n");
        return -1;
    }

    while((ch = fgetc(input_file)) != EOF)
    {
        key = 
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}
