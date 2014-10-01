#if 0
#include <iostream>
using namespace std;

//创建链表
struct Node
{
    int Element ;
    Node * next ;
};
int Insert(Node *head ,int i) //using head insert
{
    Node * p;
    p = new Node ;
    if (p == NULL)
        cout<<"it is wrong!!"<<endl;
    p->Element = i ;
    p->next = head->next; 
    head->next = p ;

    return 0;
}
void Init_Node(Node *&head)
{
    head = new Node  ;
    head->next = NULL;
    cout<<"It is init "<<endl;
}
int main()
{
    int i ;
    int a[5];
    Node * head ;
    
    Init_Node(head); // init list head 
    
    for(i = 0 ; i < 5 ; i++ ) // create array assign to list 
        Insert(head , i);
    
    while(head->next != NULL)  // show the list 
    {
        cout<<head->next->Element<<endl;
        head = head->next;
    }
    return 0 ;
}
#endif

/*
  Output :
          It is init
          4
          3
          2
          1
          0


*/
