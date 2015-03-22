/*
LL(1)语法分析
LL(1)简要的介绍：
    LL(1)分析是一种不带回溯的非递归自顶向下的语法分析方法，第一个L:
    自顶向下分析是从左向右扫描输入串 ，第二个L:
    最左推导
实验原理：
LL(1)分析法基本思想：
    根据输入串的当前符号唯一确定选择某条规则进行推导，当这个输入符号和推导的第一个符号相同时，在取下一个符号，继续确定下一个推导的选择规则，直到推导出被分析的输入串为止。
LL(1)分析器由分析表和分析栈 和控制程序组成如图：
    本实验的LL(1)表基于编译原理教材的P53 表3.1 如图：

*/


/*Author:waten
  Time : 2014-6-5 21:22
  Name : LL(1)  analyse table interpreter progame
  Source : comiler  p53 table of 3.1
代码：
*/

#include <iostream>
#include<malloc.h>
using namespace std;


struct stack_table
{
    int  data[100];
    int tops;
};

int LL1_table[4][5]=
{
    {1,-1,-1,-1,-1},
    {2,-1,-1,11,12},
    {-1,-1,-1,3,-1},
    {-1,4,13,-1,-1},
};

char Vt[] = { 'a' , 'b' , 'l' , 'd' , '#'} ;
char Vn[] = {'A','m','B','n'} ;

void InitStack(stack_table *&s)
{
    s = (stack_table *)malloc(sizeof(stack_table));
    s->tops = -1;
}
int push(stack_table *&s , int  e)
{
    if (s->tops == 99)
    {
        cout<<"The stack is full !"<<endl;
        return 0;
    }
    s->tops++;
    s->data[s->tops] = e ;
    cout<<"push:"<<(char)s->data[s->tops]<<endl;
    return 4;
}

int push_sybmol(stack_table *&s , int  e)
{
    if (s->tops == 99)
    {
        cout<<"The stack is full !"<<endl;
        return 0;
    }
    s->tops++;
    s->data[s->tops] = e ;
    cout<<"push_sybmol :"<<(char)s->data[s->tops]<<endl;
    return 4;
}
int pop(stack_table *&s ,int e)
{
    if(s->tops == -1)
    {
        cout<<"it is empty stack now!"<<endl;
        return 0;
    }
    e = s->data[s->tops];
    cout<<"pop:"<<(char)s->data[s->tops]<<endl;
    s->tops--;
    return 3 ;
}
int dis_symbol(stack_table *s) //
{
    int temp ;
    temp = s->tops ;

    if(temp == -1)
    {
        cout<<"the stack is empty now!"<<endl;
        return 0;
    }
    while(temp != -1)
    {
        cout<<(char)s->data[temp]<<"\t";
        temp--;
    };
    cout<<endl;
    return 1;
}
int match(char x)  // check x weather Vt or not
{
    int temp=0;
    for(temp ; temp <sizeof(Vt); temp++)
        if ( x == Vt[temp])
            return 1;
    return 0;
}
int match_Vn(char Vn_input)
{
    int temp=0;
    for(temp ; temp <sizeof(Vn); temp++)
        if (Vn_input == Vn[temp])
            break;
    return temp;
}

int match_Vt(char Vt_input)
{
    int temp=0;
    for(temp ; temp <sizeof(Vt); temp++)
        if (Vt_input == Vt[temp])
            break;
    return temp;
}

int lookup_LL1_table(char Vn_input , char Vt_input)
{
    int i , j ;
    i = match_Vn(Vn_input);
    j = match_Vt(Vt_input);
    return LL1_table[i][j];
}


int main()
{
    char x,current_store[2],pop_mem[100]; //current_store->stroe the current symbol  ; x -> store input anal_table character
    char *input = new char [20] ;
    int temp ,pop_mem_index = 0 ;
    stack_table *anal_stack ;
    InitStack(anal_stack) ;
    cout<<"please input a string:"<<endl;
    cin>>input;
    //cout << "Hello world!" << endl;
    push( anal_stack , '#');
    push( anal_stack , 'A');
    current_store[0] = *input; //store the first symbol character
    do
    {
        cout<<"the current of stack:";
        dis_symbol(anal_stack);

        x =  anal_stack->data[anal_stack->tops] ;
        cout<<"x="<<x<<endl;
        temp = match(x);
        cout<<"the temp:"<<temp<<endl;
        if (temp)
        {
            if (current_store[0] != '#')
            {
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                input++;
                current_store[0] = *input;
                cout<<"current_store[0]"<<*input<<endl;
            }
            else
            {
                cout<<" SUCCESS!!!!!"<<endl;
            }
        }
        else
        {
            int value ;
            value = lookup_LL1_table(anal_stack->data[anal_stack->tops] , current_store[0]); //the current of top anal_stack and Vt;
            switch(value)
            {
            case -1:
                cout<<"Something is wrong !"<<endl;
                return 0;
            case 1:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                push( anal_stack , 'm');
                push( anal_stack , 'a') ;
                break ;
            case 2:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                push( anal_stack , 'l') ;
                push( anal_stack , 'B') ;
                push( anal_stack , 'A') ;
                break ;
            case 3:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                push( anal_stack , 'n');
                push( anal_stack , 'd') ;
                break ;
            case 4:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                push( anal_stack , 'n') ;
                push( anal_stack , 'b' ) ;
                break ;
            case 11:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                break ;
            case 12:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                break ;
            case 13:
                pop( anal_stack , pop_mem[pop_mem_index] );
                pop_mem_index++ ;
                break ;
            }

        }

    }
    while( x != '#');
    if( '#'  == anal_stack->data[anal_stack->tops])
        cout<<"OK"<<endl;
    else
        cout<<"Wrong"<<endl;
    return 0;
}

