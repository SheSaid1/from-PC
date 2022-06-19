
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <map>
#include <vector>

using namespace std;
/* Node Structure */
struct BstNode
{
    int data;
    BstNode *left;
    BstNode *right;
};

/* Create New Node */
BstNode *createNode(int data)
{
    BstNode *newNode = new BstNode();

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* Insert Node in Binary Search Tree */
BstNode *insertNode(BstNode *root, int data)
{
    if (root == NULL)
        root = createNode(data);
    else if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    return root;
}

/* Search Node Value in Binary Search Tree */
bool searchNode(BstNode *root, int data)
{   cout<<root->data<<" ";
    if (root == NULL)
        return false;
    else if (data == root->data)
        return true;
    else if (data < root->data)
        return searchNode(root->left, data);
    else
        return searchNode(root->right, data);
}

/* Find Minimal Node Value in Binary Search Tree */
BstNode *findMinNode(BstNode *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}
BstNode *findMaxNode (BstNode *root)
{
    while (root->right!=NULL)
        root=root->right;
    return root;
}

BstNode *findSecondMaxNode (BstNode *root)
{   BstNode * root2 = new BstNode;
    while (root->right!=NULL)
        {   root2=root;
            root=root->right;
        }
        if (root->left==NULL)
        {
            return root2;
        }
        else
            return findMaxNode (root->left);
}

/* Delete Node in Binary Search Tree */
BstNode *deleteNode(BstNode *root, int data)
{
    if (root == NULL)
        return root;
    else if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL)
        {
            BstNode *temp = root->right;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            BstNode *temp = root->left;
            root = root->left;
            delete temp;
        }
        else
        {
            BstNode *min2 = findMinNode(root->right);
            root->data = min2->data;
            root->right = deleteNode(root->right, min2->data);
        }
    }
    return root;
}

int heightOfBinaryTree(BstNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 +
        max(heightOfBinaryTree(root->left),
            heightOfBinaryTree(root->right));
    }
}

int  searchNodee(BstNode *root, int data)
{ //int value=1;
   // cout<<root->data<<endl;
    if (root == NULL)
        return 0;
    else if (data == root->data)
        return 1;
    else if (data < root->data)
        return 1+searchNodee(root->left, data);
    else
        return 1+searchNodee(root->right, data);
}

 void Pirnt_tree (BstNode *root )
 {

       if (root!=NULL)
       {
           if(root->left!=NULL)
           {
               Pirnt_tree(root->left);
           }
           cout<<root->data<<endl;
           Pirnt_tree(root->right);
       }
}

void Pirnt_list (BstNode *root )
 {

       if (root!=NULL)
       {
           if(root->left!=NULL)
           {
               Pirnt_list(root->left);
           }
           if ( (root->right!=NULL && root->left==NULL) || (root->right==NULL && root->left!=NULL))
           {
               cout<<root->data<<endl;
           }

           Pirnt_list(root->right);
       }


}


void abl (BstNode *root,bool & b )
 {

       if (root!=NULL)
       {
           if(root->left!=NULL)
           {
               abl(root->left,b);
           }
           if  ( root->right!=NULL ||  root->left!=NULL )
           {
              int a=heightOfBinaryTree(root->left);
              int c=heightOfBinaryTree(root->right);
              if (abs (a-c)>1)
                b=false;

           }

          abl (root->right,b);
       }


}



void Creat(const string &s )
{
    ifstream input(s);
    BstNode *root=NULL;
    vector <int> v;
    map<int,int> m;
    int i=0;
    input>>i;
    m[i]++;
    v.push_back(i);
    root=insertNode(root,i);

    while (i!=0)
    {   if (m[i]>0)
        {
            input>>i;
            continue;
        }
        else
        {
        root=insertNode(root,i);
        m[i]++;
        v.push_back(i);
        input>>i;
        }

    }
    //cout<<heightOfBinaryTree(root);
    //cout<< findSecondMaxNode(root)->data;
    bool b=true;
    abl(root,b);
    if (b)
    cout<<"YES";
    else cout<<"NO";


}

int main()
{ /*
    BstNode *root = NULL;

     Insert Node with Value
    root = insertNode(root, 12);
    root = insertNode(root, 15);
    root = insertNode(root, 5);
    root = insertNode(root, 53);
    root = insertNode(root, 98);
    root = insertNode(root, 0);

     Search Node by Value
    std::cout << searchNode(root, 53) << std::endl;
    std::cout << searchNode(root, 42) << std::endl;
    std::cout << searchNode(root, 15) << std::endl;

     Delete Node by Value
    root = deleteNode(root, 53);
    root = deleteNode(root, 15);

     Search Node by Value
    std::cout << searchNode(root, 53) << std::endl;
    std::cout << searchNode(root, 15) << std::endl; */
    Creat("input.txt");
    //cout<<"all is ok";
    return 0;
}
