#pragma once
#include <iostream>
#include <stdint.h>

typedef struct tuple_ tuple_;
typedef struct relation relation;
typedef struct hash_table hash_table;
typedef struct array_int array_int;
typedef struct bucket bucket;
typedef struct result result;
typedef struct b_chain b_chain;
typedef struct bucket_hash bucket_hash;


struct tuple_ {
  uint64_t key;
  uint64_t payload;
};

struct relation {
  tuple_ * tuples;
  uint64_t num_tuples;
};

struct array_int{
  int64_t * data;
  int64_t length;
};

struct hash_table{
  array_int psum;
  relation * rel;
};

struct bucket{
  int64_t low;
  int64_t high;
};

struct b_chain {
  int64_t *Bucket;
  int64_t *Chain;
};

struct bucket_hash {
  bucket *b;
  hash_table *ht;
};




result * radixHashJoin(relation * rel_R, relation * rel_S);
void compareBuckets(bucket_hash *sm,bucket_hash *lg,b_chain *bc,result *res_list,bool isReversed);
b_chain * indexingSmallBucket(bucket_hash *small);
bool isPrime(uint64_t n);
inline int findNextPrime(uint64_t n);
inline int64_t h2(int64_t num);
hash_table * reorderRelation(relation * rel);
relation * createRelation(relation * rel, array_int psum_original);
array_int createPsum(array_int hist);
array_int createHistogram(relation * rel);
void freeHashTableAndComponents(hash_table *);
