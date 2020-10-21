#ifndef _MAP_H
#define _MAP_H

#define MAP_KEY_LEN 64
#define MAP_VALUE_LEN 64
#define MAP_TABLE_LEN 128

struct map_pair_st 
{
    char key[MAP_KEY_LEN];
    char value[MAP_VALUE_LEN];
};

struct map_st 
{
    struct map_pair_st table[MAP_TABLE_LEN];
    int count;
};

/* @brief
 * function to set 0 struct map_st
 * @params
 * input: *map: pointer to struct map_st
 */
void map_init(struct map_st *map);

/* @brief
 * function add a couple key-value (to replace value to key in text) to struct map
 * @params
 * input: *map: pointer to struct map_st
 *        *key: pointer to key
 *        *value: pointer to value
 */
void map_add(struct map_st *map, char *key, char *value);

/* @brief
 * function to replace all key in *s string by value that can be lookup in map
 * @params
 * input: *map: pointer to struct map_st
 *        *s: string between whitespaces or newline character
 * @return
 * pointer to the replaced string
 */
char * map_lookup(struct map_st *map, char *s);

#endif
