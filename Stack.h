#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//————————————————————————————————————————————————————————————————————————————————

#define STACK_DEBUG

#ifdef STACK_DEBUG 
    #define ON_DEBUG(...) __VA_ARGS__
#else  
    #define ON_DEBUG(...)
#endif

#define STACKCTOR(stack, capacity) \
        StackCtor(&stack, capacity ON_DEBUG(, #stack, __FILE__, __LINE__))


//————————————————————————————————————————————————————————————————————————————————

typedef double Stack_Elem_t;
const Stack_Elem_t canary = 0xEDA;

//————————————————————————————————————————————————————————————————————————————————

enum Stack_Error_t : size_t
{
    STACK_OK               = 0,
    STACK_ERR_NULL         = 1, //stack NULL.
    STACK_ERR_DATA         = 2, //data NULL.
    STACK_ERR_CAPACITY     = 3, //capacity <= 0.
    STACK_ERR_SIZE_NEG     = 4, //size < 0.
    STACK_ERR_OVERFLOW     = 5, //size > capacity.
    STRUCKT_L_CANARY_FALSE = 6,
    STRUCKT_R_CANARY_FALSE = 7,
    STACK_L_CANARY_FALSE   = 8,
    STACK_R_CANARY_FALSE   = 9,
};

//————————————————————————————————————————————————————————————————————————————————

struct Stack_t
{
    Stack_Elem_t left_cock = canary;

    ON_DEBUG (const char* var_name;
              const char* file;
              int line;)

    Stack_Elem_t* point_stack_data;

    Stack_Elem_t* data;
    size_t size;
    size_t capacity;

    Stack_Elem_t right_cock = canary;
};

//————————————————————————————————————————————————————————————————————————————————



//————————————————————————————————————————————————————————————————————————————————

void my_assert(bool condition, const char* message, const char* file, int line);

#ifndef NDEBUG
    #define MY_ASSERT(condition, message) my_assert((condition), (message), __FILE__, __LINE__) 
#else 
    #define MY_ASSERT(condition, message)
#endif

//————————————————————————————————————————————————————————————————————————————————
void StackDump(const char* log_filename, size_t errors, Stack_t* stack_name);

void StackDtor(Stack_t* stack);

Stack_Elem_t* StackCtor(Stack_t* stack, size_t capacity ON_DEBUG(, const char* name, const char* file, int line));

void StackPush(Stack_t* stack, Stack_Elem_t num);

Stack_Elem_t StackPop(Stack_t* stack);

bool StackIsEmpty(Stack_t* stack);

bool StackIsFull(Stack_t* stack);

enum Stack_Error_t StackVerify(const Stack_t* stack);
