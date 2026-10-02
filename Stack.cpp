#include "StackFunctions.cpp"

int main(void)
{
    // Stack_t* bad_stack = NULL;
    // StackPush(bad_stack, 42);
    
    Stack_t stack;
    STACKCTOR(stack, 5);

    //stack.left_cock = 0xE;
    // stack.capacity = -13;
    // stack.point_stack_data[0] = 0xE;

    StackPush(&stack, 1);
    StackPush(&stack, 2);
    StackPush(&stack, 67);
    StackPush(&stack, 4);
    StackPush(&stack, 5);
    StackPush(&stack, 6);

    // stack.size = 100;

    // StackPush(&stack, 30);
    double a = StackPop(&stack);
    double b = StackPop(&stack);
    double c = StackPop(&stack);
    double d = StackPop(&stack);
    double e = StackPop(&stack);
    double f = StackPop(&stack);

    StackDtor(&stack);
    printf("%lg %lg %lg %lg %lg %lg\n", a, b, c, d, e, f);
}


