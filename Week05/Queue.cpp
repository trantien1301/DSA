#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Queue
{
    NODE *head;
    NODE *tail;
};
Queue *initializeQueue()
{
    Queue *q = new Queue;
    if (q == NULL)
    {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    return q;
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
void enqueue(Queue *q, int key)
{
    NODE *newNode = CreateNode(key);
    if (newNode == NULL)
    {
        return;
    }
    if (q->head == NULL)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        newNode->p_next = q->head;
        q->head = newNode;
    }
    return;
}
int dequeue(Queue *q)
{
    if(q->head==NULL)
    {
        return -1;
    }
    if(q->head==q->tail)
    {
        NODE *temp=q->tail;
        int res=temp->key;
        q->head=NULL;
        q->tail=NULL;
        delete temp;
        return res;
    }
    NODE* curr = q->head;
    while (curr->p_next != q->tail)
    {
        curr = curr->p_next;
    }
    NODE* temp = q->tail;
    int res= temp->key;
    q->tail = curr;
    q->tail->p_next = NULL;
    delete temp;
    return res;
}
int size(Queue *q)
{
    int count = 0;
    NODE *curr = q->head;
    while (curr != NULL)
    {
        count++;
        curr = curr->p_next;
    }
    return count;
}
bool isEmpty(Queue *q)
{
    if (q->head == NULL)
    {
        return true;
    }
    return false;
}
void printQueue(Queue* q, ofstream& outfile) {
    if (isEmpty(q)) {
        outfile << "EMPTY\n";
    }
    else
    {
        NODE* temp = q->head;
        while(temp!=NULL)
        {
            outfile<<temp->key<< " ";
            temp=temp->p_next;
        }
    outfile << "\n";
    }
}
int main()
{
    ifstream fs;
    fs.open("input.txt");
    ofstream of;
    of.open("output.txt");   
    Queue *q=initializeQueue();
    string cmt;
    while(fs>>cmt)
   { 
    if(cmt=="init")
    {
        delete q;
        q=initializeQueue();
    }
    else if (cmt=="enqueue")
    {
        int key;
        fs>> key;
        enqueue(q,key);
    }
    else if(cmt=="dequeue")
    { 
        int val = dequeue(q);
    }
    printQueue(q,of);
   }
   fs.close();
   of.close();
   delete q;
   return 0;
}