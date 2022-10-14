#include "stdio.h"
#ifndef HASHTABLE__HASH_TABLE_H_
#define HASHTABLE__HASH_TABLE_H_

typedef ssize_t ht_value_t;

typedef struct {
  char* key;
  ht_value_t value;
} ht_item_t;

typedef struct {
  size_t base_capacity;
  size_t capacity;
  size_t size;
  ht_item_t** items;
} ht_hash_table_t;

ht_hash_table_t* ht_create(void);
ht_hash_table_t* ht_create_sized(size_t base_capacity);
void ht_destroy(ht_hash_table_t* ht);

void ht_insert(ht_hash_table_t* ht, const char* key, ht_value_t value);
ht_value_t ht_search(const ht_hash_table_t* ht, const char* key);
void ht_delete(ht_hash_table_t* ht, const char* key);

#endif  // HASHTABLE__HASH_TABLE_H_
