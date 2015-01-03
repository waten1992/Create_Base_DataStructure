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
    BinTree *t1 , *t2 ;
    int index = 0 ; //统计 根节点 左子树的 右孩子 个数
    t1 = T->Left ; //左孩子
    t2 = T->Right ; //右孩子
    int a[10] = {0}; //存储临时 左子树的 右孩子 值
    printf("The Non Recursion Traversal \n" );
    printf("The root node: %d \n" , T->data );

    printf("The Left tree : \n");
    while(t1 != NULL)
    {
        printf("%d \t" , t1->data );
        if ( t1->Right != NULL )
            a[index++] = t1->Right->data; //保存 右孩子
        t1 = t1->Left ;
    }

    for (int j = 0 ; j < index ; j++ ) //输出左子树的 右孩子
        printf("%d \t" , a[j]);
    printf("\nThe Root Left Child Tree of Right child tree Count: %d" , index ) ;

    printf("\nThe Right tree : \n") ;
    while(t2 != NULL)  //遍历右子树
    {
        printf("%d \t" , t2->data ) ;
        if ( t2->Left != NULL )
            printf("%d \t" , t2->Left->data);
        t2 = t2->Right;
    }

    printf("\n");
    free(t1); // 释放掉临时节点 ， 避免内存泄漏
    free(t2); // 释放掉临时节点
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
