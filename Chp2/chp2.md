# Chapter 2 Arrays and Structure

## Contents
1. [Arrays](#1-arrays)
2. [Dynamically Allocated Arrays](#2-dynamically-allocated-arrays)
3. [Structure and Unions](#3-structure-and-unions)
4. [Examples](#4-examples)

## 1. Arrays
## 2. Dynamically Allocated Arrays
## 3. Structure and Unions
## 4. Examples
### Polynomials

[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp2/polynomial_addition_v2.cpp)

### Sparse Matrices

[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp2/)

### String

#### Pattern Matching: KMP Algorithm
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp2/KMP_v2.cpp)


### Identifier
**Identifier** is a name we give to each variables.

_c.f._
- Start with english or underscore( _ ; usually for system variables)
- Use only english, numbers and under score
- Upper and lower case are different 
- Can be consist maximum 63 characters
- Can not use _keywords_ such as double, int, switch, if, else, return, static etc.

### Types
**Type** is a set of values and a set of operations that can be applied on those values.

_i.e._ There are mainly four types.

- void: literally _empty_ type, meaning _undefined_.
- integral
     - boolean: gets only two values - 0,1 - which represents true and false.
     - character: gets only one character as ASCII code (i.e. 1 byte; 0~255(2^8))
     - integer: gets integer numbers and this varies from short to long long integer. Each type varies in the size(size can be checked with the function '_sizeof( )_') of the memory.
- floating-point
     - real: varies from float to long double with different size.
     - imaginary
     - complex
- derived
     - pointer
     - enumerated type
     - union
     - array
     - structure

### Variables and Constants

**Variables** are the space that gets value, while **constant** is the number that does not alter along the program.
```c
const float pi=3.141592 //constants
bool fact;
short maxItems;
long long national_debt;
float payRate=0; //variable initialization (this stage is indispensable if we use the same variable repeatedly) 
char code, kind;
int a, b;
```

### Others

There are three more things to note-Literal Constants, Defined Constants, Memory Contstants.

i.e. There are three types of constant

- Literal Constant: Non-named constants. This is generated if we just type a number.

```c
a=b*5; //5 is literal constant
```

- Defined Constant: The constant that does not varies alond the program; Defined before the main function starts.

```c
#define SALES_TAX_RATE .0825
```

- Memory Constant: The constant that does not varies alond the program; Defined after the main function.

```c
const float Pi=3.141592;
```
