/**
 描述：把链表按照奇偶数分开；
 
 思路：
       1-把相邻的先拆成2个链表
 
 */
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
protected:
    ListNode *head = new ListNode(-1);
public:

    ListNode *Separations() 
    {
        if (head->next == NULL || head->next->next == NULL)
            return head; //若为空链表或者只有一个元素
        else
        {
            ListNode *new_head = new ListNode(-1);
            ListNode *Tmp ,*Rear, *faster , *slower ;
            Rear = new_head; //指向新链表
            slower = head->next; //指向原链表
            faster = slower->next; //faster快一步
            while (faster != NULL ) //拆链表
            {
                Rear->next = faster ; //指向第一个元素
                if(faster->next == NULL)
                {
                    faster = faster->next;
                    slower->next = NULL;
                }
                else
                {
                    slower->next = faster->next ; //跳转到下一个元素
                    slower = slower->next; //指向原链表当前节点
                    faster = slower->next ; //指向slower下一个
                }
                Rear = Rear->next ;
                Rear->next = NULL ;
            }
            return new_head;
        }
    }

    void Tail_Insert(int item) //尾插法
    {
        ListNode * Rear , * Current ;
        Rear = head;
        while (Rear->next != NULL) //找到最后的
        {
            Rear = Rear->next;
        }
        Current = new ListNode(item); //新建节点
        Current->next = Rear->next;
        Rear->next = Current ;
        Rear = Rear->next;
        Rear->next = NULL ;
#if 0 //for test !
        cout<<Current->data<<endl;
#endif
    }

    void Display_List() //有头结点的输出程序
    {
        ListNode *Tmp ;
        Tmp = head->next ;
        while(Tmp != NULL)
        {
            cout<<Tmp->val<<"->";
            Tmp = Tmp->next;
        }
        cout<<"NULL"<<endl;
    }

};

int main()
{
    int a[] = {1,2,3,4,5};
    Solution A;
    for (int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
        A.Tail_Insert(a[i]);
    A.Display_List();
    cout<<"After Sparation -->"<<endl;
    A.Separations();
    A.Display_List();
    return 0 ;
}

/*
The answer as follow--->
1->2->3->4->5->NULL
After Sparation -->
1->3->5->NULL

Process returned 0 (0x0)   execution time : 0.022 s
Press any key to continue.
*/
