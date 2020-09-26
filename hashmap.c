#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  long position;
  Pair* a =(createPair(key,value));
  position = hash(key,map->capacity);
  while (map->buckets[position]!=NULL)
  {
    position =(position+1);
    if (position>=(map->capacity))
    {
      position =(position-(map->capacity));
    }
  }
  map->buckets[position] =a;
  map->size =((map->size)+1);
  if (((map->size)/(map->capacity))>0.7)
  {
    enlarge(map);
  }
}

void insertRehashed(Pair** NewBuckets, HashMap * map, long i)
{
  long position;
  char* key;
  key =(char*)calloc(((strlen(map->buckets[i]->key))+1),sizeof(char));
  void* value;
  value =(void*)calloc(1,sizeof(void));
  strcpy(key,map->buckets[i]->key);
  value =map->buckets[i]->value;
  Pair* a =(createPair(key,value));
  position = hash(key,map->capacity);
  NewBuckets[position] =(a);
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  map->capacity =((map->capacity)*2);  
  Pair** pivot;
  pivot =(Pair**)calloc(map->capacity,sizeof(Pair*));
  for (long i =(0);i<((map->capacity)/2);i =(i+1))
  {
    insertRehashed(pivot,map,i);
  }
  map->buckets =(Pair**)calloc(map->capacity,(sizeof(Pair*)));
  map->buckets =(pivot);
  pivot =NULL;
  free(pivot);
}


HashMap * createMap(long capacity) {
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (Pair **) calloc (capacity,sizeof(Pair *));
  map->capacity = capacity;
  map->current = -1;
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

void * searchMap(HashMap * map,  char * key) {   
  /*if (map->capacity==0)
  {
    return NULL;
  }
  long position;
  position =(hash(key,map->capacity));
  printf ("Holi%ld",position);
  long count =0;
  while ((strcmp(key,map->buckets[position]->key))!=0)
  {
    position =(position+1);
    if (position>=(map->capacity))
    {
      position =(position-(map->capacity));
    }
    if (count>=map->capacity)
    {
      return NULL;
      break;
    }
    count++;
  }
  void* output;
  output =(void*)calloc(1,sizeof(void));
  output =(map->buckets[position]->value);
  map->current =(position);
  return (output);*/
  return NULL;
}

void * firstMap(HashMap * map) {

    return NULL;
}

void * nextMap(HashMap * map) {

    return NULL;
}
