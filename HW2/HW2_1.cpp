#include <iostream>
#include <string>
#include<vector>
using namespace std;

struct Stack 
{
    string array;   
    int capacity;   
    int top;        
};

Stack* createStack(int capacity) 
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array.resize(capacity);  
    return stack;
}

bool isEmpty(Stack* stack) 
{
    return stack->top == -1;
}

bool isFull(Stack* stack) 
{
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, char item) 
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) 
{
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

char peek(Stack* stack) 
{
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top];
}

void deleteStack(Stack* stack) 
{
    delete stack;
}

bool canExit(const string& entry_sequence, const string& exit_sequence) 
{
    int entry_index = 0;
    Stack* stack = createStack(entry_sequence.size());

    for (char exit_char : exit_sequence) 
    {
        while (entry_index < entry_sequence.size() && (isEmpty(stack) || peek(stack) != exit_char)) 
        {
            push(stack, entry_sequence[entry_index]);
            entry_index++;
        }

        if (!isEmpty(stack) && peek(stack) == exit_char) 
            pop(stack);
        else 
        {
            deleteStack(stack);
            return false;
        }
    }

    deleteStack(stack);
    return true;
}

int main() 
{
    using namespace std;

    string entry_sequence;
    string exit_sequence;

    getline(cin, entry_sequence);

    while (getline(cin, exit_sequence)) 
    {
        cout << (canExit(entry_sequence, exit_sequence) ? "yes" : "no") << endl;
    }

    return 0;
}
