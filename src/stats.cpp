#include <iostream>
#include <vector>
#include "../inc/stats.hpp"

#define N_SIZE 40000000

Stats::Stats(Relation& rel, int col){
  this->relation = rel;
  this->column = this->relation->getColumn(col);
}

Relation* Stats::getRelation(){
  return this->relation;
}

void* Stats::getColumn(){
  return this->column;
}

uint64_t Stats::getTuple(const void* col, int tpl){
  return this->relation->getTuple(col, tpl);
}

uint64_t Stats::getTupleCount(){
  return this->relation->getTupleCount();
}

void Stats::setluf(){
  this->f = getTupleCount();
  this->l = this->u = getTuple(this->colum, 0);
  for(uint64_t i = 1; i< this->f; i++){
    uint64_t v = getTuple(this->column, i);
    if(v < this->l)
      this->l = v;
    else if(v > this->u)
      this->u = v;
  }
}

void Stats::setd(){
  this->d = bool_process((this->u - this->l + 1)<N_SIZE);
}

uint64_t Stats::bool_process(true){
  uint64_t count = 0;
  std::vector<bool> bool_vector((this->u - this->l + 1), false); (*)
  for(uint64_t i; i<this->f; i++)
    if(bool_vector[getTuple(this->column, i)-this->u] != true){
      bool_vector[getTuple(this->column, i)-this->u] = true;
      count ++;
    }
  return count;
}

uint64_t Stats::bool_process(false){
  uint64_t count = 0;
  std::vector<bool> bool_vector(N_SIZE, false); (*)
  for(uint64_t i; i<this->f; i++)
    if(bool_vector[getTuple(this->column, i)-this->u % N_SIZE] != true){
      bool_vector[getTuple(this->column, i)-this->u % N_SIZE] = true;
      count ++;
    }
  return count;
}

uint64_t Stats::getl(){
  return this->l;
}

uint64_t Stats::getu(){
  return this->u;
}

uint64_t Stats::getf(){
  return this->f;
}

uint64_t Stats::getd(){
  return this->d;
}

void Stats::setl(uint64_t v){
  this->l = v;
}

void Stats::setu(uint64_t v){
  this->u = v;
}

void Stats::setf(uint64_t v){
  this->f = v;
}

void Stats::setd(uint64_t v){
  this->d = v;
}
