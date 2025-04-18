#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Stack
{
    NODE *top;
};
Stack *initializeStack()
{
    Stack *s = new Stack;
    if (s == NULL)
    {
        return NULL;
    }
    s->top = NULL;
    return s;
}
NODE *CreateNode(int key)
{
    NODE *newNode = new NODE;
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->key = key;
    ;
    newNode->p_next = NULL;
    return newNode;
}
void Push(Stack *s, int key)
{
    NODE *newNode = CreateNode(key);
    if (newNode == NULL)
    {
        return;
    }
    if (s->top == NULL)
    {
        s->top = newNode;
    }
    else
    {
        newNode->p_next = s->top;
        s->top = newNode;
    }
    return;
}
int Pop(Stack *s)
{
    if (s->top == nullptr) 
    {
        return -1;
    }
    NODE* Pop = s->top;
    int res = Pop->key;
    s->top = Pop->p_next;
    delete Pop;
    return res;
}

int size(Stack *s)
{
    int count = 0;
    NODE *curr = s->top;
    while (curr != NULL)
    {
        count++;
        curr = curr->p_next;
    }
    return count;
}
bool isEmpty(Stack *s)
{
    if (s->top == NULL)
    {
        return true;
    }
    return false;
}
void printStack(Stack* s, ofstream& outfile) {
    if (isEmpty(s)) {
        outfile << "EMPTY";
    }
    Stack *tempStack=initializeStack();
    NODE* temp = s->top;
    while (temp) {
        Push(tempStack, temp->key);
        temp = temp->p_next;
    }
    while (!isEmpty(tempStack)) {
        int key = tempStack->top->key;
        outfile << key << " ";
        Pop(tempStack);
    }
    delete tempStack;
    outfile << "\n";
}
int main()
{
    ifstream fs;
    fs.open("input.txt");
    ofstream of;
    of.open("output.txt");   
    Stack *s=initializeStack();
    string cmt;
    while(fs>>cmt)
   { 
    if(cmt=="init")
    {
        delete s;
        s=initializeStack();
    }
    else if (cmt=="push")
    {
        int key;
        fs>> key;
        Push(s,key);
    }
    else if(cmt=="pop")
    { 
        int val = Pop(s);
    }
    printStack(s,of);
   }
   fs.close();
   of.close();
   delete s;
   return 0;
}
