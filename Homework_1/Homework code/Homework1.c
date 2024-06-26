/*--------------------------------------------------------------------
Name: 	Brandon Ramos
Date: 	8/20/2020	
Course: CSCE 236 Embedded Systems (Fall 2020) 
File: 	Homework1.c 
HW/Lab:	Homework 1, programming component

Purp:	A brief description of what this program does and 
		the general solution strategy. 

Doc:	<list the names of the people who you helped>
		<list the names of the people who assisted you>


Academic Integrity Statement: I certify that, while others may have 
assisted me in brain storming, debugging and validating this program, 
the program itself is my own work. I understand that submitting code 
which is the work of other individuals is a violation of the honor   
code.  I also understand that if I knowingly give my original work to 
another individual is also a violation of the honor code.
--------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
char fullname[13] = "Brandon Ramos";
/**
 * Return your user name
 **/
char* getFullName(void){
  //  return a pointer to a _global_ variable that
  //  contains your full name
  char *name = fullname;
  return name;
}


//returns a pointer to the
// same _global_ variable that contains your full name, but that
// starts at your last name
char* getLastName(void){
  char *name = fullname;
    for(int i=0; i<strlen(getFullName());i++){
      if(*name++==' '){
      //name++;
      return name;
      }
  }
}


/**
 * Gets the ith character of the user name or returns '!' if the name
 * is not that long.
 **/
char getFullNameChar(int i){
  char *name = getFullName();

  //  return the ith character of name or '!' if an out
  //  of bounds index is requested.  Do _not_ use strlen or equivalent
  //  functions to determine the length of the string, instead, write
  //  your own code to determine the length of the string (look for
  //  the null termination of the name string: '\0')
for(int j=0;j<=i;j++){
  name = getFullName();
  name+=j;
  if(*name=='\0'){
    return '!';
  }
}
  return name[0];
}

/**
 * Print the results of the string operation tests
 **/
void stringOperations(void){
  char *name = getFullName();

  printf("Name: %s\n",name);
  printf("LastName: %s\n",getLastName());
  printf("Name[0]: %c\n",getFullNameChar(0));
  printf("Name[4]: %c\n",getFullNameChar(4));
  printf("Name[%d] (last): %c\n",(int)strlen(name)-1,
         getFullNameChar(strlen(name)-1));
  printf("Name[%d] (oob): %c\n",(int)strlen(name),
         getFullNameChar(strlen(name)));
  printf("Name[%d] (oob): %c\n",(int)strlen(name)+10,
         getFullNameChar(strlen(name)+10));
  printf("\n");
}

/**
 * Print the output of various bit operations
 **/
void bitOperations(void){
  int varA = 0x81914;
  int varB = 0x10236;

  ////////////////////////// Student Code //////////////////////////
  // Complete the following print statements by ouputing the value
  // after doing the bit operations indicated in the comments.  You
  // should not periminately modifiy the value of the variables.
  // You also should _not_ hard code the result.

  int output,temp;
  // Output the value (1 or 0) of bit 3 (zero referenced) in varA and varB
  output = (varA>>2)&1;
  printf("Bit 3 in varA: %#x\n",
           output);
  output = (varB>>2)&1;
  printf("Bit 3 in varB: %#x\n",
           output);


  // Output the value of varA after setting bit 5 (zero referenced) to 0
  output = (1<<4)^varA;
  printf("Bit 5 set to 0 varA: %#x\n",
           output);


  // Output the value of varB after setting bit 7 (zero referenced) to 1
  output = (1<<6)|varB;
  printf("Bit 7 set to 1 varB: %#x\n",
           output);
  
  // Output the value of the varA after setting the 3-5 bits
  // (inclusive) of varA to the lower 3 bits of varB.
  output = varB & 0x7;
  temp = varA & ~(0x7<<2);

  output = (output<<2);

  output = temp | output;
  printf("varA after...: %#x\n",
           output);
}

/**
 * Main function that calls the corresponding functions
 **/
int main(){
  printf("CSCE 236 HW1 Output\n");
  printf("-------------------\n");
  stringOperations();
  bitOperations();
  return(0);
}