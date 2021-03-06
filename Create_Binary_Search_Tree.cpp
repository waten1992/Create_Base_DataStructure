#include <iostream>
using namespace std;

typedef int ElementType ;
typedef struct TreeNode * Position ;
typedef struct TreeNode * ATree ;
struct TreeNode
{
    ElementType Element ;
    ATree       Left    ;
    ATree       Right   ;
    int         Level   ;
};

ATree Initialize(ATree  root)
{
    if (root == NULL)
    {
        root = new struct TreeNode ;
        if (root == NULL)
            cout<<"OUT OF SPACE !"<<endl;
        root->Right = root->Left = NULL;
        root->Level = 0 ;
        cout<<"It is initial success !"<<endl;
    }
}

ATree Insert(ElementType Item , ATree T )
{
    if ( T == NULL )
    {
        T = new struct TreeNode ;
        if ( T == NULL)
        {
            cout<<"OUT OF SPACE !"<<endl;
        }
        else
        {
            T->Element = Item   ;
            T->Level = 1        ;
            T->Right = T->Left = NULL ;
        }
    }
    else if ( Item < T->Element ) //Insert left Tree
    {
        T->Left = Insert( Item , T->Left ) ;
    }
    else if ( Item > T->Element ) //Insert Right Tree
    {
        T->Right = Insert(Item , T->Right ) ;
    }
    /*Otherwise it's duplicate , do nothing */

    return T ;
}
int Pre_Traversal(ATree root)
{
    if( root == NULL )
       return NULL ;
    ATree Tmp ;
    Tmp = root ;
    cout<<Tmp->Element ; // out the current Element 
    Pre_Traversal(Tmp->Left) ; //Recursion call left child
    Pre_Traversal(Tmp->Right); //Recursion call Right child
    return 0 ;
}


int Pre_Traversal_iterator(ATree root) //previous traversal iterator 
{
    if( root == NULL )
       return NULL ;
    ATree Tmp = NULL ;  //declare the temp point 
    stack <ATree> v ;  //declare stack store node

    v.push(root); //push the root into stack

    while(!v.empty())
    {
        Tmp = v.top(); //get the stack top vaule 
        v.pop();      // pop the top of stack
        cout<<Tmp->Element ; // out the current Element

        if (Tmp->Right != NULL)
            v.push(Tmp->Right);
        if (Tmp->Left != NULL)
             v.push(Tmp->Left) ;
    }
    delete Tmp ; // delete the Tmp memory
    return 0 ;
}

int Mid_Traversal(ATree root)
{
    if( root == NULL )
       return NULL ;
    ATree Tmp ;
    Tmp = root ;
    Mid_Traversal(Tmp->Left) ;  //Recursion call left child
    cout<<Tmp->Element ;        // out the current Element 
    Mid_Traversal(Tmp->Right) ; //Recursion call Right child
    return 0 ;
}
int main()
{   ATree root = NULL ;
    
    int  len , a[] = {5,4,6,2,1,6,7,8,9} ;
    len = sizeof(a)/sizeof(a[0]) ;
    
    for(int i = 0 ; i < len ; i++)
        root = Insert( a[i] , root ) ;
        
    cout<<"The Previous Traversal as follow : ";
    Pre_Traversal(root) ;
    
    cout<<endl<<"The Middle Traversal as follow : ";
    Mid_Traversal(root) ;
    
    cout<<endl<<"The Previous Iterator Traversal as follow : ";
    Pre_Traversal_iterator(root) ;
    
    return 0 ;
}



/*
The Answer as follow ----->

The Middle Traversal as follow : 12456789
The Previous Traversal as follow : 54216789
The Previous Iterator Traversal as follow : 54216789
Process returned 0 (0x0)   execution time : 0.032 s
Press any key to continue.




*/
