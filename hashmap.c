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

void insertReHashed(HashMap * map, char * key, void * value) 
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
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  Pair** pivot;
  map->capacity =((map->capacity)*2);  
  pivot =map->buckets;
  map->buckets =(Pair**)calloc(map->capacity,(sizeof(Pair*)));
  Pair* test;
  for (int i=0;i<(map->capacity)/2;i++)
  {
    test =(pivot[i]);
    if (test!=NULL)
    {
      insertReHashed(map,test->key,test->value);
    }
  }
  free(test);
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

void * searchMap(HashMap * map,  char * key)
{   
  if (map->capacity==0)
  {
    return NULL;
  }
  long position;
  position =(hash(key,map->capacity));
  long count =0;
  while (is_equal(key,map->buckets[position]->key)==0)
  {
    position =(position+1);
    count++;
    while(1)
    {
      if (map->buckets[position]==NULL)
      {
        count =(count+1);
        position =(position+1);
      }
      else
      {
        break;
      }
    }
    if (position>=(map->capacity))
    {
      position =(position-(map->capacity));
    }
    if (count>=(map->capacity)-1)
    {
      return NULL;
    }    
  }
  void* output;
  output =(void*)calloc(1,sizeof(void));
  output =(map->buckets[position]->value);
  map->current =(position);
  return (output);
}

void * firstMap(HashMap * map) {
  if (map==NULL)
  {
    return NULL;
  }
  map->current=0;
  while (1)
  {
    if ((map->buckets[map->current]==NULL)||(map->buckets[map->current]->key==NULL))
    {
      map->current =((map->current)+1);
    }
    else
    {
      break;
    }
  }
  return (map->buckets[map->current]->value);
}

void * nextMap(HashMap * map) {
  if (map->buckets==NULL)
  {
    return NULL;
  }
  printf("el current inicial es %ld\n",(map->current));
  map->current =((map->current)+1);
  while (1)
  {
    if (map->current>=map->capacity)
    {
      map->current =0;
      return NULL;
    }
    if ((map->buckets[map->current]==NULL)||(map->buckets[map->current]->key==NULL))
    {
      map->current =((map->current)+1);
    }
    else
    {
      break;
    }
  }
  printf("la talla de la tabla es %ld\n",map->capacity);
  printf("el current final es %ld\n",(map->current));
  return (map->buckets[map->current]->value);
}
