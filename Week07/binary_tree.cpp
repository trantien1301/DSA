#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct NODE
{
    int key;
    NODE *p_right;
    NODE *p_left;
};
NODE *createNode(int key)
{
    NODE *newNode = new NODE;
    newNode->key = key;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}
vector<int> NLR(NODE *pRoot)
{
    if (!pRoot)
    {
        vector<int> res;
        res.push_back(pRoot->key);
        NLR(pRoot->p_left);
        NLR(pRoot->p_right);
        return res;
    }
}
vector<int> LNR(NODE *pRoot)
{

    if (!pRoot)
    {
        vector<int> res;
        LNR(pRoot->p_left);
        res.push_back(pRoot->key);
        LNR(pRoot->p_right);
        return res;
    }
}
vector<int> LRN(NODE *pRoot)
{

    if (!pRoot)
    {
        vector<int> res;
        LNR(pRoot->p_left);
        LNR(pRoot->p_right);
        res.push_back(pRoot->key);
        return res;
    }
}
vector<vector<int>> LevelOrder(NODE *pRoot)
{
    if (!pRoot)
    {
        return nullptr;
    }
    vector<vector<int>> res;
    int level = 0;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty())
    {
        int len =q.size;
        res.push_back({});
        for (int i=0,i<len;i++)
        {
            
        }
    }
    
}
