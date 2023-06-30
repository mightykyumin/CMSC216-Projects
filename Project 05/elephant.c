#include "elephant.h"
#include <stdio.h>

Elephant new_elephant(enum type which_type, unsigned int id,
                      unsigned short weight, float trunk_length){
  Elephant elephant; 
  elephant.elephant_type = which_type;
  elephant.id = id;
  elephant.weight = weight;
  elephant.trunk_length = trunk_length;

  return elephant;
}
unsigned short init_elephant(Elephant *const el_ptr, enum type which_type,
                             unsigned int id, unsigned short weight,
                             float trunk_length){
  if(el_ptr == 0)
    return 0;
  el_ptr -> elephant_type = which_type;
  el_ptr -> id = id;
  el_ptr -> weight = weight;
  el_ptr -> trunk_length = trunk_length;
  return 1;
}


enum type get_type(Elephant el){
  return el.elephant_type;

}

unsigned int get_id(Elephant el){
  return el.id;
}


unsigned short get_weight(Elephant el){
  return el.weight;
}

float get_trunk_length(Elephant el){
  return el.trunk_length;
}

void print_elephant(Elephant el){
  if(el.elephant_type == 0)
    printf("AFRICAN ");
  else
    printf("ASIAN ");
  printf("%d ",el.id);
  printf("%d ",el.weight);
  printf("%g\n",el.trunk_length);
}

unsigned short compare(Elephant el, Elephant e2){
  if(el.elephant_type == e2.elephant_type && el.id == e2.id && el.weight == 
     e2.weight && el.trunk_length == e2.trunk_length)
    return 1;
  else
    return 0;
}

unsigned short change_id(Elephant *const el_ptr, unsigned int new_id){
  if(el_ptr == 0)
    return 0;
  el_ptr->id = new_id;
  return 1 ;
}
unsigned short copy(Elephant *const el_ptr1, const Elephant *const el_ptr2){

  if(el_ptr1 == 0||el_ptr2 == 0)
     return 0;
  el_ptr1 -> elephant_type = el_ptr2 -> elephant_type;
  el_ptr1 -> id = el_ptr2 -> id ;
  el_ptr1 -> weight =  el_ptr2 -> weight;
  el_ptr1 -> trunk_length = el_ptr2 -> trunk_length;
  return 1;
}

