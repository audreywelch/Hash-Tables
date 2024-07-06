#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the 
  next `LinkedPair` in the list of `LinkedPair` nodes. 
 */
typedef struct LinkedPair {
  char *key;
  char *value;
  struct LinkedPair *next;
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable {
  int capacity;
  LinkedPair **storage;
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  pair->key = strdup(key);
  pair->value = strdup(value);
  pair->next = NULL;

  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
unsigned int hash(char *str, int max)
{
  unsigned long hash = 5381;
  int c;
  unsigned char * u_str = (unsigned char *)str;

  while ((c = *u_str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % max;
}

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  // Allocate memory for the Hash Table struct
  HashTable *ht = malloc(sizeof(HashTable));

  // Set initial values for capacity
  ht->capacity = capacity;

  // Allocate memory for the storage to hold the capacity
  ht->storage = calloc(capacity, sizeof(LinkedPair *));

  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // Hash the key to get the index
  unsigned int hash_index = hash(key, ht->capacity);

  // Create a linked pair with the key/value
  LinkedPair *linked_pair = create_pair(key, value);

  // Create a variable that references the hashed index
  LinkedPair *currently_stored_pair = ht->storage[hash_index];

  // If a pair already exists in this hashed index
  if (currently_stored_pair != NULL) {
    // Set the currently stored pair's `next` to the the linked pair to be inserted
    currently_stored_pair->next = linked_pair;
  }

  // Otherwise, the slot was empty, and the pair should be inserted into the hashed index
  ht->storage[hash_index] = linked_pair; 
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{
  // Hash the key to get the index
  int hash_index = hash(key, ht->capacity);

  // If there is an an existing entry and they match,
  if (ht->storage[hash_index] != NULL && strcmp(key, ht->storage[hash_index])) {

    // if the entry has a next, change that next entry to be the head


  }

  

  // If they don't match, move down the linked list, checking the nodes

}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  // Hash the key to get the index
  int hash_index = hash(key, ht->capacity);

  // Check if there is a valid entry in the slot
  if (ht->storage[hash_index] != NULL) {

    // Set the current pair to a variable
    LinkedPair *current_pairs_pointer = ht->storage[hash_index];

    // While more Linked Pair's exist
    while (current_pairs_pointer->next != NULL) {
      // If they match, return the value
      if (strcmp(current_pairs_pointer->key, key) == 0) {
        return current_pairs_pointer->value;
      }
      // Set the current pair to the next pair
      current_pairs_pointer = current_pairs_pointer->next;
    }
    
    // When no more Linked Pair's exist, and if they match, return the value
    if (strcmp(current_pairs_pointer->key, key) == 0) {
        return current_pairs_pointer->value;
      }

  }

  // Otherwise, print an error
  fprintf(stderr, "unable to retrieve an entry with key: %s\n", key);

  return NULL;
}

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{

}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  HashTable *new_ht;

  return new_ht;
}


#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  int old_capacity = ht->capacity;
  ht = hash_table_resize(ht);
  int new_capacity = ht->capacity;

  printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
