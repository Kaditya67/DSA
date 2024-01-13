#include <iostream>
#include <cstdlib>

struct Stack
{
    int size;
    int top;
    char *arr;
};

int isEmpty(Stack *ptr)
{
    return (ptr->top == -1);
}

int isFull(Stack *ptr)
{
    return (ptr->top == ptr->size - 1);
}

void push(Stack* ptr, char val)
{
    if(isFull(ptr))
    {
        std::cout << "Stack Overflow! Cannot push " << val << " to the stack\n";
    }
    else
    {
        ptr->top++;
        ptr->arr[ptr->top] = val;
    }
}

char pop(Stack* ptr)
{
    if(isEmpty(ptr))
    {
        std::cout << "Stack Underflow! Cannot pop from the stack\n";
        return -1;
    }
    else
    {
        char val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
    }
}

char stackTop(Stack* sp)
{
    return sp->arr[sp->top];
}

int match(char a, char b)
{
    if(a=='{' && b=='}') return 1;
    if(a=='(' && b==')') return 1;
    if(a=='[' && b==']') return 1;
    return 0;  
}

int parenthesisMatch(const char *exp)
{
    Stack *sp = new Stack;
    sp->size = 100;
    sp->top = -1;
    sp->arr = new char[sp->size];

    char popped_ch;

    for (int i = 0; exp[i] != '\0'; i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            push(sp, exp[i]);
        }
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if(isEmpty(sp))
            {
                return 0;
            }
            popped_ch = pop(sp);
            if(!match(popped_ch, exp[i]))
            { 
                return 0;  
            }
        }
    }

    if(isEmpty(sp))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int main()
{
    std::string expression;
    std::cout << "Enter the expression: ";
    std::cin >> expression;

    if(parenthesisMatch(expression.c_str()))
    {
        std::cout << "The parentheses are balanced";
    }
    else
    {
        std::cout << "The parentheses are not balanced";
    }

    return 0;
}
