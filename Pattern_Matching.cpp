#include <iostream>
#include <cstdlib>

struct stack
{
    int size;
    int top;
    char *arr;
};

int isEmpty(stack *ptr)
{
    return (ptr->top == -1);
}

int isFull(stack *ptr)
{
    return (ptr->top == ptr->size - 1);
}

void push(stack *ptr, char val)
{
    if (isFull(ptr))
    {
        std::cout << "Stack Overflow! Cannot push " << val << " to the stack" << std::endl;
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

char pop(stack *ptr)
{
    if (isEmpty(ptr))
    {
        std::cout << "Stack Underflow! Cannot pop from the stack" << std::endl;
        return '\0';
    }
    else
    {
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

int parenthesisMatch(const char *exp)
{
    stack *sp = new stack;
    sp->size = 100;
    sp->top = -1;
    sp->arr = new char[sp->size];

    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(')
        {
            push(sp, '(');
        }
        else if (exp[i] == ')')
        {
            if (isEmpty(sp))
            {
                delete[] sp->arr;
                delete sp;
                return 0;
            }
            pop(sp);
        }
    }

    int result = isEmpty(sp);

    delete[] sp->arr;
    delete sp;

    return result;
}

int main()
{
    std::cout << "Enter an expression with parentheses: ";
    std::string expression;
    std::getline(std::cin, expression);

    if (parenthesisMatch(expression.c_str()))
    {
        std::cout << "The parentheses are matching" << std::endl;
    }
    else
    {
        std::cout << "The parentheses are not matching" << std::endl;
    }

    return 0;
}
