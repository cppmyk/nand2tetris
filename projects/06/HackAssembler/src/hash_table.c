#include "hash_table.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define HT_PRIME_1 151
#define HT_PRIME_2 157
#define HT_INITIAL_BASE_CAPACITY 50

static ht_item_t HT_DELETED_ITEM = {NULL, -1};

static bool is_prime(size_t x) {
  assert(x >= 2);
  if (x < 4) return true;
  if (x % 2 == 0) return false;
  for (int i = 3; i < floor(sqrt((double)x)); i += 2) {
    if (x % i == 0) return false;
  }
  return true;
}

static size_t next_prime(size_t x) {
  while (!is_prime(x)) ++x;
  return x;
}

static ht_item_t* ht_create_item(const char* key, ht_value_t value) {
  ht_item_t* item = malloc(sizeof *item);
  item->key = strdup(key);
  item->value = value;
  return item;
}

ht_hash_table_t* ht_create_sized(size_t base_capacity) {
  ht_hash_table_t* ht = malloc(sizeof *ht);
  ht->base_capacity = base_capacity;

  ht->capacity = next_prime(base_capacity);
  ht->size = 0;
  ht->items = calloc(ht->capacity, sizeof(ht_item_t*));

  return ht;
}

static void ht_resize(ht_hash_table_t* ht, size_t base_capacity) {
  if (base_capacity < HT_INITIAL_BASE_CAPACITY) return;

  ht_hash_table_t* new_ht = ht_create_sized(base_capacity);
  for (int i = 0; i < ht->capacity; ++i) {
    ht_item_t* item = ht->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM)
      ht_insert(new_ht, item->key, item->value);
  }

  ht->base_capacity = new_ht->base_capacity;
  ht->size = new_ht->size;

  const size_t tmp_capacity = ht->capacity;
  ht->capacity = new_ht->capacity;
  new_ht->capacity = tmp_capacity;

  ht_item_t** tmp_items = ht->items;
  ht->items = new_ht->items;
  new_ht->items = tmp_items;

  ht_destroy(new_ht);
}

static void ht_resize_up(ht_hash_table_t* ht) {
  ht_resize(ht, ht->base_capacity * 2);
}

static void ht_resize_down(ht_hash_table_t* ht) {
  ht_resize(ht, ht->base_capacity / 2);
}

ht_hash_table_t* ht_create(void) {
  return ht_create_sized(HT_INITIAL_BASE_CAPACITY);
}

static void ht_delete_item(ht_item_t* item) {
  assert(item);
  free(item->key);
  free(item);
}

void ht_destroy(ht_hash_table_t* ht) {
  assert(ht);
  for (size_t i = 0; i < ht->capacity; ++i) {
    if (ht->items[i]) ht_delete_item(ht->items[i]);
  }
  free(ht->items);
  free(ht);
}

static int ht_hash(const char* str, int prime, size_t buckets_count) {
  long hash = 0;
  const size_t str_length = strlen(str);

  for (size_t i = 0; i < str_length; ++i) {
    hash += (long)(pow(prime, (double)(str_length - (i + 1)))) * str[i];
    hash %= (long)buckets_count;
  }

  return (int)hash;
}

static int ht_get_hash(const char* str, size_t buckets_count, int attempt) {
  const int hash_a = ht_hash(str, HT_PRIME_1, buckets_count);
  const int hash_b = ht_hash(str, HT_PRIME_2, buckets_count);

  return (hash_a + (attempt * (hash_b + 1))) % (int)buckets_count;
}

void ht_insert(ht_hash_table_t* ht, const char* key, ht_value_t value) {
  const size_t load = ht->size * 100 / ht->capacity;
  if (load > 70) ht_resize_up(ht);

  int i = 0;
  int index = ht_get_hash(key, ht->capacity, i);
  ht_item_t* item = ht_create_item(key, value);

  while (ht->items[index] && ht->items[index] != &HT_DELETED_ITEM) {
    if (ht->items[index]->key == key) {
      ht_delete_item(ht->items[index]);
      ht->items[index] = item;
      return;
    }
    ++i;
    index = ht_get_hash(key, ht->capacity, i);
  }

  ht->items[index] = item;
  ht->size++;
}

ht_value_t ht_search(const ht_hash_table_t* ht, const char* key) {
  int i = 0;
  int index = ht_get_hash(key, ht->capacity, i);
  ht_item_t* item = ht->items[index];

  while (item) {
    if (item != &HT_DELETED_ITEM)
      if (strcmp(item->key, key) == 0) return item->value;
    ++i;
    index = ht_get_hash(key, ht->capacity, i);
    item = ht->items[index];
  }

  return -1;
}

void ht_delete(ht_hash_table_t* ht, const char* key) {
  const size_t load = ht->size * 100 / ht->capacity;
  if (load < 10) ht_resize_down(ht);

  int i = 0;
  int index = ht_get_hash(key, ht->capacity, i);
  ht_item_t* item = ht->items[index];

  while (item) {
    if (item != &HT_DELETED_ITEM) {
      if (strcmp(item->key, key) == 0) {
        ht_delete_item(item);
        item = &HT_DELETED_ITEM;
        ht->size--;
      }
    }
    ++i;
    index = ht_get_hash(key, ht->capacity, i);
    item = ht->items[index];
  }
}

