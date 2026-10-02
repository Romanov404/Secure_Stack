#include "Stack.h"

//______________ASSERT______________

void my_assert(bool condition, const char *message, const char *file, int line)
{
    if (!condition)
    {
        printf("\n============\n"
        "ERROR: %s\n"
        "FILE: %s\n"
        "LINE: %d\n"
        "\n============\n", 
        message, file, line);

        exit(1);
    }
}
//————————————————————————————————————————————————————————————————————————————————




//————————————————————————————————————————————————————————————————————————————————

Stack_Elem_t* StackCtor(Stack_t* stack, size_t capacity ON_DEBUG(, const char* var_name, const char* file, int line))
{
    MY_ASSERT(stack != NULL, "stack is NULL");
    MY_ASSERT(capacity > 0, "capacity <= 0");

    Stack_Elem_t* point_stack_data = (Stack_Elem_t*)calloc(capacity + 2, sizeof(Stack_Elem_t));
    MY_ASSERT(point_stack_data != NULL, "point_stack_data is NULL");
    
    stack->point_stack_data = point_stack_data;
    
    stack->point_stack_data[0] = canary;
    //--
    stack->data = point_stack_data + 1;
    stack->size = 0;
    stack->capacity = capacity;
    //--
    stack->point_stack_data[capacity + 1] = canary;


    #ifdef STACK_DEBUG
        stack->var_name = var_name; 
        stack->file = file;
        stack->line = line;
    #endif
    
    return point_stack_data; 
}

//————————————————————————————————————————————————————————————————————————————————

void StackDtor(Stack_t *stack)
{
    ON_DEBUG (const char* name; const char* file; int line;)

    MY_ASSERT(StackVerify(stack) == 0, "StackVerify failed");

    free(stack->point_stack_data);

    stack->point_stack_data = NULL;
    stack->data = NULL;
    stack->capacity = 0;
    stack->size = 0;
}

//————————————————————————————————————————————————————————————————————————————————

void StackPush(Stack_t *stack, Stack_Elem_t num)
{
    size_t err = StackVerify(stack);

    if (err == 0)
    {
        MY_ASSERT(StackVerify(stack) == 0, "StackVerify failed");

        if (stack->size >= stack->capacity)
        {
            size_t new_capacity = (stack->capacity) * 2;

            Stack_Elem_t* new_point_data = (Stack_Elem_t *)realloc(stack->point_stack_data, (new_capacity + 2) * sizeof(Stack_Elem_t));
            MY_ASSERT(new_point_data != NULL, "realloc_size is NULL");

            stack->point_stack_data = new_point_data;
            stack->data = new_point_data + 1;

            for (size_t i = stack->capacity; i < new_capacity; i++)
            {
                stack->data[i] = 0;
            }

            stack->capacity = new_capacity;
            stack->point_stack_data[stack->capacity + 1] = canary;
        }
        
        stack->data[stack->size] = num;
        stack->size++;

        MY_ASSERT(stack->size <= stack->capacity, "size > capacity, overflow capacity");
    }
    else
    {
        ON_DEBUG(StackDump("log_stack", err, stack));
        exit(EXIT_FAILURE);
    }
}

//————————————————————————————————————————————————————————————————————————————————

Stack_Elem_t StackPop(Stack_t *stack)
{
    MY_ASSERT(stack != NULL, "stack is NULL");
    MY_ASSERT(stack->size > 0, "size is negative");

    size_t err = StackVerify(stack);

    if (err == 0)
    {
        Stack_Elem_t value = stack->data[stack->size - 1];
        stack->size--;
        stack->data[stack->size] = 0;

        return value;
    }
    
    else
    {
        ON_DEBUG(StackDump("log_stack", err, stack));
        exit(EXIT_FAILURE);
    }
    
}

//————————————————————————————————————————————————————————————————————————————————

void StackDump(const char* log_filename, size_t error, Stack_t* stack)
{
    FILE* log_file = fopen(log_filename, "a");
    
    if (log_file == NULL)
    {
        printf("File if NULL");
        exit(EXIT_FAILURE);
    }

    fprintf(log_file, "_______________STACK DUMP_______________\n");

    if (stack == NULL)
    {
        fprintf(log_file, "ERROR: Stack pointer is NULL (code: %zu)\n", error);
        fprintf(log_file, "________________________________________\n\n");
        fclose(log_file);
        return;
    }
    fprintf(log_file, "Stack_t \"%s\" at adress: [%p] , created by [file: %s, line: %u]\n", stack->var_name, stack, stack->file, stack->line);

    if(error == STACK_ERR_NULL)
        fprintf(log_file, "ERROR: Stack Pointer is NULL\n");
        
    if(error == STACK_ERR_DATA)
        fprintf(log_file, "ERROR: Stack Data Pointer if NULL\n");

    if(error == STACK_ERR_CAPACITY)
        fprintf(log_file, "ERROR: Caracity is sero or negative\n");

    if(error == STACK_ERR_SIZE_NEG)
        fprintf(log_file, "ERROR: Stack Size is negative\n");

    if(error == STACK_ERR_OVERFLOW)
        fprintf(log_file, "ERROR: Size > Capacity\n");

    if(error == STRUCKT_L_CANARY_FALSE)
        fprintf(log_file, "ERROR: Your Left Cock (cock of STRUCT) is DAMAGE\n");
    if(error == STRUCKT_R_CANARY_FALSE)
        fprintf(log_file, "ERROR: Your Right Cock (cock of STRUCT) is DAMAGE\n");

    if(error == STACK_L_CANARY_FALSE)
        fprintf(log_file, "ERROR: Your Left Cock (cock of STACK) is DAMAGE\n");
    if(error == STACK_R_CANARY_FALSE)
        fprintf(log_file, "ERROR: Your Right Cock (cock of STACK) is DAMAGE\n");
    
            
    if (stack != NULL)
    {
        fprintf(log_file, "size = %zu\n" 
                          "capacity = %zu\n"  
                          "data adress is [%p]\n",
                          stack->size, stack->capacity, stack->data);
    }

    fprintf(log_file, "\t {\n");

    int i = 0;
    if (stack->data != NULL && stack->capacity > 0)
    {
        for (size_t i = 0; i < stack->capacity; i++)
        {
            if (i < stack->size)
            {
                fprintf(log_file, "\t\t*[%zu] = %lg\n", i, stack->data[i]);
            }
            else
            {
                fprintf(log_file, "\t\t [%zu] = %lg\n", i, stack->data[i]);
            }
        }
        
        fprintf(log_file, "\t }\n");
    }
    else
    {
        fprintf(log_file, "ERROR Stack Data Pointer is NULL\n");
    }

    fprintf(log_file, "________________________________________\n\n\n");
    
    fclose(log_file);
}

//————————————————————————————————————————————————————————————————————————————————

enum Stack_Error_t StackVerify(const Stack_t *stack)
{
    if (stack == NULL)
        return STACK_ERR_NULL;

    if (stack->data == NULL)
        return STACK_ERR_DATA;

    if (stack->capacity <= 0)
        return STACK_ERR_CAPACITY;
    
    if (stack->size > stack->capacity)
        return STACK_ERR_OVERFLOW;

    if (stack->left_cock != canary)
        return STRUCKT_L_CANARY_FALSE;
    if (stack->right_cock != canary)
        return STRUCKT_R_CANARY_FALSE;
    
    if (stack->point_stack_data == NULL || stack->data != stack->point_stack_data + 1)
        return STACK_ERR_DATA;

    if (stack->point_stack_data[0] != canary)
        return STACK_L_CANARY_FALSE;
    
    if (stack->point_stack_data[stack->capacity + 1] != canary)
        return STACK_R_CANARY_FALSE;


    return STACK_OK;
}

//————————————————————————————————————————————————————————————————————————————————




//————————————————————————————————————————————————————————————————————————————————

bool StackIsEmpty(Stack_t *stack)
{
    MY_ASSERT(StackVerify(stack) == 0, "StackVerify failed");

    return stack->size == 0;
}

//————————————————————————————————————————————————————————————————————————————————

bool StackIsFull(Stack_t *stack)
{
    
    MY_ASSERT(StackVerify(stack) == 0, "StackVerify failed");

    return stack->size >= stack->capacity;
}

//————————————————————————————————————————————————————————————————————————————————
