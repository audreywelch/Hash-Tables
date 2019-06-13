#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****
  Basic hash table key/value pair
 ****/
typedef struct Pair {
  char *key;
  char *value;
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable {
  int capacity; // number of buckets/array size
  Pair **storage;
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  Pair *pair = malloc(sizeof(Pair));
  pair->key = strdup(key);
  pair->value = strdup(value);

  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  if (pair != NULL) {
    free(pair->key);
    free(pair->value);
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/

// Time Complexity: O(n) where n is the length of the input string
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


/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  // Allocate memory for the BasicHashTable struct
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));

  // Set initial valus for capacity
  ht->capacity = capacity;

  // Allocate memory for the storage to hold the capacity number pairs (key, value)
  ht->storage = calloc(capacity, sizeof(Pair *));

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  // Hash the key to get the index
  unsigned int hash_index = hash(key, ht->capacity);

  // Create a pair with the key/value
  Pair *pair = create_pair(key, value);

  // Create a variable to hold the hash index
  Pair *currently_stored_pair = ht->storage[hash_index];

  // If the stored pair already
  if (currently_stored_pair != NULL) {
    // Compare the keys - If they don't match...
    if (strcmp(key, currently_stored_pair->key) != 0) {
      // Print a warning
      printf("Warning: You are overwriting a previous value in the Hash Table\n");
    }
    // Otherwise, delete the pair that was previously in that index
    destroy_pair(currently_stored_pair);
  }

  // Insert the pair in the hashed index
  ht->storage[hash_index] = pair;

}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // Hash the key to get the index
  int hash_index = hash(key, ht->capacity);

  // If there is an existing entry and if they match...
  if (ht->storage[hash_index] != NULL && strcmp(key, ht->storage[hash_index]->key) == 0)  {
    
    // If they match, remove by freeing up the memory
    destroy_pair(ht->storage[hash_index]);
    // Set garbage pointer to NULL for later checks
    ht->storage[hash_index] = NULL;

  } else {
    // If not, print an error
    fprintf(stderr, "Cannot remove key: %s\n", key);
  }

}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{

  // Hash the key to get the index
  int hash_index = hash(key, ht->capacity);

  // Check if there is a valid entry in the slot
  if (ht->storage[hash_index] != NULL) {

    // If they match, return the value
    if (strcmp(ht->storage[hash_index]->key, key) == 0) {
      printf("Key is: %s\n", ht->storage[hash_index]->value);
      return ht->storage[hash_index]->value;

    // If they don't match, print an error
    } else {
      printf("Keys don't match\n");
      return NULL;
    }
  // If the slot is NULL, print an error
  } else {
    printf("Keys don't match\n");
    return NULL;
  }
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  // Loop through each pair in the hash table's capacity
  for (int i = 0; i < ht->capacity; i++) {
    // If there is a pair, destory it
    if (ht->storage[i] != NULL) {
      destroy_pair(ht->storage[i]);
    }
  }
  // Free all storage
  free(ht->storage);

  // Free the hash table
  free(ht);
}


#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL) {
    printf("...gone tomorrow. (success)\n");
  } else {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
