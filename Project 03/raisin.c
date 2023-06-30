/*Name : Kyumin Hwang
  University Directory ID: khwang77
  Nine-digits ID : 119134092
  Section number : 0205
  I pledge on my honor that I have not given or received any unauthorized
  assistance on this assignment*/
#include "raisin.h"
#include <stdio.h>

/* Prototype of the is_valid functiton*/
int is_valid(unsigned int instruction);

/* This function gets integer instructiton and interpret it and print the 
   instruction line. If the instruction line is not valid, it should return 0, 
   if it is valid, it should print 1 instead. By interpretting the instructiton,
   It will print the insructiton's opcode ,register1,register2, and address 
   operand. */
unsigned short print_instruction(unsigned int instruction) {
  int op_value = instruction >> 27; /* saves integer opvalue*/
  int register1 = (instruction >> 22) & 31; /* saves register1 value*/
  int register2 = (instruction >> 17) & 31; /* saves register2 value*/
  int address = instruction & 131071; /* saves address value */
  /* short value that will be used to represent validity*/
  unsigned short valid = 0;

  /* Check for the validity */
  /* The opvalue should be not bigger than21 , register 1,2 should not be 
     more than 18 and address should be divisible by 4 */
  if (is_valid(instruction) == 1) {
    /* Prints the opcode instruction*/
    if (op_value == HALT)
      printf("halt\t");
    else if (op_value == SYSCALL)
      printf("syscall\t");
    else if (op_value == ADD)
      printf("add\t");
    else if (op_value == SUB)
      printf("sub\t");
    else if (op_value == MUL)
      printf("mul\t");
    else if (op_value == QUOT)
      printf("quot\t");
    else if (op_value == MOD)
      printf("mod\t");
    else if (op_value == AND)
      printf("and\t");
    else if (op_value == OR)
      printf("or\t");
    else if (op_value == NEG)
      printf("neg\t");
    else if (op_value == NOT)
      printf("not\t");
    else if (op_value == EQL)
      printf("eql\t");
    else if (op_value == NEG)
      printf("neq\t");
    else if (op_value == LT)
      printf("lt\t");
    else if (op_value == LE)
      printf("le\t");
    else if (op_value == GT)
      printf("gt\t");
    else if (op_value == GE)
      printf("ge\t");
    else if (op_value == MOVE)
      printf("move\t");
    else if (op_value == LW)
      printf("lw\t");
    else if (op_value == SW)
      printf("sw\t");
    else if (op_value == LI)
      printf("li\t");
    else if (op_value == BRANCH)
      printf("branch\t");

    /* Prints the register1 */
    if (op_value != SYSCALL && op_value != HALT && op_value != BRANCH)
      printf("R%d \t", register1);

    /* Prints the register2 */
    if (op_value >= 2 && op_value <= 8)
      printf("R%d \t", register2);
    else if (op_value >= 11 && op_value <= 17)
      printf("R%d \t", register2);

    /* Prints the address */
    if (op_value == 20)
      printf("%d", address);
    else if (op_value >= 18 && op_value <= 21)
      printf("%05d", address);
    /* change validitiy to 1 */
    valid = 1;
    printf("\n");
  }
  return valid;
}

/* This function will gets integer array of instruction, start address,
   program size, and data segment size as a parameter.
   Using this parameters, this function will simulate the operating system that
   loads machine language program into MAD Raisin's memory to execute.Memory 
   consists of instruction and actual data parts.
   If the valid parameters are given and printed well, 1 should be returned
   and if not 0 should be returned. */
int load_program(unsigned int memory[],
		 const unsigned int program[],
		 unsigned int start_addr, unsigned short pgm_size, unsigned
		 short data_segment_size) {
  int i = 0; /* will be used in for loop*/
  int j = 0; /* Will be used in for loop*/
  int valid = 0; /* Check the validity of the instruction*/

  /* Check the validty of the parameter */
  /* If the program size is bigger than the memory size, should just return 0
     and do nothing*/
  if (start_addr / 4 < NUM_WORDS && start_addr % 4 == 0 && pgm_size <= 
      NUM_WORDS && start_addr / 4 + pgm_size <= NUM_WORDS && data_segment_size 
      != pgm_size) {
    /*For loop that copies program data to MAD Raisin memory*/
    for (i = start_addr / 4, j = 0; i < start_addr / 4 + pgm_size; i++, j++) {
      memory[i] = program[j];
    }
    valid = 1;
  }
  return valid;
}

/* This function converts machine language to assembly language*/
/*  This function will gets integer array of instruction, start address,
    program size, and data segment size as a parameter. Starting from the 
    start address, this function will read and print the instruction. If the 
    parameter and the instruction is not valid it should just return 0 and
    print nothing. If is valid it should return 1 and print instructions data.*/
int unsigned short disassemble(const unsigned int memory[], unsigned int
			       start_addr, unsigned int pgm_size,
			       unsigned int data_segment_size) {
  int i = 0; /* Integer that will be used at the for loop */

  short valid = 0; /*short value to save the validity states*/
  int inst_valid = 1; /* Integer value that states the validity of 
			 instruction*/

  /* Checks for the validity of the instruction part */
  if (start_addr / 4 < NUM_WORDS && start_addr % 4 == 0 && pgm_size <=
      NUM_WORDS && start_addr / 4 + pgm_size <= NUM_WORDS && 
      data_segment_size != pgm_size) {
    for (i = start_addr / 4; i < start_addr / 4 + pgm_size - 
	   data_segment_size; i++) {
      if ((is_valid(memory[i])) == 0)
	inst_valid = 0;
    }
  }
  /* Checks for the validity of the parameters and prints instructions and 
     data if the parameters are valid */
  if (start_addr / 4 < NUM_WORDS && start_addr % 4 == 0 && pgm_size <=
      NUM_WORDS &&
      start_addr / 4 + pgm_size <= NUM_WORDS && data_segment_size != pgm_size &&
      inst_valid == 1) {
    /*Prints instruction */
    for (i = start_addr / 4; i < start_addr / 4 + pgm_size - 
	   data_segment_size; i++) {
      print_instruction(memory[i]);
    }
    /* Prints data */
    for (i = start_addr / 4 + pgm_size - data_segment_size; i < start_addr /
	   4 + pgm_size; i++) {
      printf("%08x\n", memory[i]);
    }
    valid = 1;
  }
  return valid;
}
/* This function gets instruction as a parameter and checks whether
   the instruction is valid or not */
/* If the instruction is valid it will return 1 otherwise it wll 
   return 0 */
int is_valid(unsigned int instruction) {
  int op_value = instruction >> 27; /* saves integer opvalue*/
  int register1 = (instruction >> 22) & 31; /* saves register1 value*/
  int register2 = (instruction >> 17) & 31; /* saves register1 value*/
  int address = instruction & 131071; /* saves address value */
  int valid = 1; /* interger value that will be used to represent validity*/

  /*Checks whether there is valid opcode value*/
  if (op_value >= 23)
    valid = 0;
  /* Checks for the register1 value is valid or not */
  if (op_value != SYSCALL && op_value != HALT && op_value != BRANCH) {
    if (register1 > 17)
      valid = 0;
  }
  /* Checks for the register1 value is valid or not */
  if (op_value >= 2 && op_value <= 8) {
    if (register2 > 17)
      valid = 0;
  } else if (op_value >= 11 && op_value <= 17) {
    if (register2 > 17)
      valid = 0;
  }
  /*Checks for the address value that is valid or not*/
  if (op_value >= 18 && op_value <= 19) {
    if (address % 4 != 0)
      valid = 0;
  }
  if (op_value == 21) {
    if (address % 4 != 0)
      valid = 0;
  }
  return valid;
}

