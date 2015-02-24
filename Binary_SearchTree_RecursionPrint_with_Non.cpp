#include <stdio.h>
#include <malloc.h>
#define ElementType int
/*
    Author:waten
    Date:2014-9-4 9:39
    描述： 二叉排序树的建立 ，前序递归和非递归遍历
*/

typedef struct BinTree *SearchTree;
struct BinTree
{
    int data;
    SearchTree Left ;
    SearchTree Right ;
};
SearchTree Make_Eempty(SearchTree T)
{
    if( T != NULL )
    {
        Make_Eempty(T->Left);
        Make_Eempty(T->Right);
    }
    return NULL ;
}

SearchTree Insert ( SearchTree &T , int key )
{
    if (T == NULL)
    {
        T = (SearchTree)malloc(sizeof(struct BinTree));
        if (T == NULL)
        {
            printf("out of space !\n");
            return NULL;
        }
        T->data = key ;
        T->Left = T->Right = NULL ;
    }
    else if ( key < T->data )
    {
        T->Left = Insert(T->Left , key );
    }
    else if( key > T->data )
    {
         T->Right = Insert(T->Right , key );
    }
    else
        ; //do nothing
    return T;
}
void PrintTree (BinTree *T) //递归调用 前序遍历
{
    if (T != NULL )
        {
            printf("%d \t" , T->data );
            PrintTree(T->Left);
           // printf("%d \t" , T->data ); //中序遍历
            PrintTree(T->Right);
        }
}

void NOT_RE(BinTree *T) //二叉树的 前序 非递归遍历
{
    // 有BUG 的代码 ,休要修改 
    //参见 https://github.com/waten1992/Leetcode_Interview_Collection/tree/master/Tree
}

int main()
{
    int len , a[] = {5,3,7,6,4,1,2,9,8,0};
    SearchTree T ;
    T =NULL;
    Make_Eempty(T);

    len = sizeof(a)/sizeof(a[0]);
    for(int i = 0 ; i < len  ; i++)
        Insert(T,a[i]);

    NOT_RE(T); //非递归调用
    printf("/*-----------------------------*/ \n");
    printf("The Pre Recursion Traversal :\n");
    PrintTree(T);
return 0;
}
/*
The Answer as follow ----->

The Non Recursion Traversal
The root node: 5
The Left tree :
3       1       0       4       2
The Root Left Child Tree of Right child tree Count: 2
The Right tree :
7       6       9       8
/*-----------------------------*/
The Pre Recursion Traversal :
5       3       1       0       2       4       7       6       9       8

Process returned 0 (0x0)   execution time : 0.030 s
Press any key to continue.



*/
