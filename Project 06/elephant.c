#include <stdio.h>
#include "elephant.h"
#include <string.h>
#include <stdlib.h>

Elephant *new_elephant(const char name[], enum type which_type,
                       unsigned int id, unsigned short weight,
                       float trunk_length){
  Elephant *elephant = malloc(sizeof(Elephant));
  

  if(name == NULL)
    return NULL;
 
  elephant->name = malloc(sizeof(char)*strlen(name)+1);
  strcpy(elephant->name, name);
  elephant->elephant_type = which_type;
  elephant->id = id;
  elephant->weight = weight;
  elephant->trunk_length = trunk_length;

  return elephant;
}
unsigned short get_type(const Elephant *const el_ptr,
                        enum type *const type_ptr){
  if(el_ptr == NULL || type_ptr ==NULL)
    return 0;
 
  *type_ptr = el_ptr->elephant_type;
  return 1;
}

const char *get_name(const Elephant *const el_ptr){
  char *new_name;
  if(el_ptr == NULL|| el_ptr-> name == NULL)
    return NULL;
  new_name= malloc(sizeof(char) *strlen(el_ptr->name)+1);
 
  strcpy(new_name,el_ptr->name);
  return new_name;


}


void print_elephant(const Elephant *const el_ptr){
  if(el_ptr == NULL || el_ptr-> name ==NULL)
    return;
  printf("%s ",el_ptr->name);
  if(el_ptr->elephant_type==0)
    printf("AFRICAN ");
  else if(el_ptr->elephant_type==1)
    printf("ASIAN ");
  printf("%d ",el_ptr->id);
  printf("%d ",el_ptr ->weight);
  printf("%.2f\n",el_ptr -> trunk_length);
}


short compare(const Elephant *const el_ptr1, const Elephant *const el_ptr2){
  if(el_ptr1 == NULL || el_ptr2 == NULL)
    return -1;
  if(el_ptr1->name == NULL || el_ptr2->name == NULL)
    return -1;
  if(strcmp(el_ptr1->name, el_ptr2->name)==0 && el_ptr1->elephant_type == el_ptr2->
	    elephant_type && el_ptr1->id == el_ptr2->id && el_ptr1->weight == el_ptr2->
	    weight && el_ptr1->trunk_length == el_ptr2 -> trunk_length){
       return 1;
     }
     else
       return 0;

     }

  unsigned short change_name(Elephant *const el_ptr, const char new_name[]){
    
    if(el_ptr == NULL|| new_name == NULL)
      return 0;
    
    if(el_ptr->name !=  NULL){

      free(el_ptr->name);
      
    }
    el_ptr->name = malloc(sizeof(char)*strlen(new_name)+1);
    strcpy(el_ptr->name,new_name);
    return 1;
  }

  unsigned short copy(Elephant *const el_ptr1, const Elephant *const el_ptr2)
  {
    if(el_ptr1 == NULL || el_ptr2 == NULL)
      return 0;
    if(el_ptr1->name == NULL || el_ptr2->name == NULL)
      return 0;
    free(el_ptr1->name);
    
    el_ptr1->name = malloc(sizeof(char)*strlen(el_ptr2->name)+1);
    strcpy(el_ptr1->name,el_ptr2->name);
    el_ptr1->elephant_type = el_ptr2->elephant_type;
    el_ptr1->id = el_ptr2->id;
    el_ptr1->weight = el_ptr2->weight;
    el_ptr1->trunk_length = el_ptr2->trunk_length;
    return 1;

  }
