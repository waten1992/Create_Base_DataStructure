/*
LR语法分析
LR简要的介绍：
    LR分析是一种自底向上的进行规范规约的语法分析方法，
    L:自左向右扫描    R:自底向上的进行规约。
实验原理：
LR分析器基本思想：
    1-记住历史--记住已经移进和规约整个符号串
    2-展望未来--根据产生式推测未来可能遇到的输入符号
    3-认情现实--根据现实所输入的字符串确定栈顶符号是否构成产生式的句柄
    LR分析表是 LR分析器核心分， 包括一张ACTION 和GOTO表。
    具有移进、规约、接受、报错 4个动作
    本实验的的文法是G[E]:
    E->E+E | E*E | (E) | i , 基于编译原理教材的P90 表3.21 如图：
*/

//代码：
#if 1
/*
作者：何文官
SLR(1)来源：编译原理  第三版 P90 表3.21
  BUG 已经解决；
       总结：规约：1-符号栈  POP(原来栈顶符号)  PUSH(规约的左部)
		   2-状态栈  POP(当前的栈顶符号) 规约几个右部就POP几个
		   3-新的状态 = 查GOTO（状态栈顶，符号栈顶的元素）
		   4-PUSH(新状态)

	     移进：1- 新状态 = 查表ACTIONG(当前状态栈顶，输入串)
		   2- 状态栈 PUSH(新状态)
		   3- 符号栈 PUSH(输入串当前字符)
*/
#include<iostream>
#include<malloc.h>

using namespace std;

int action[10][7]=   //ACTION 的二维数组
{
    { 3 , -1 , -1 , 2  , -1 , -1 , 1  },
    {-1 , 4  ,  5 , -1 , -1 , 44 , -1 },
    { 3 , -1  , -1 , 2 , -1 , -1 , 6 },
    { -1 , 104  , 104 , -1 , 104 , 104 , -1 },
    { 3 , -1  , -1 , 2 , -1 , -1 , 7 },
    { 3 , -1  , -1 , 2 , -1 , -1 , 8 },
    { -1 , 4  , 5 , -1 , 9 , -1 , -1 },
    { -1 , 101 , 5 , -1 , 101 , 101 , -1 },
    { -1 , 102 , 102 , -1 , 102 , 102 , -1 },
    { -1 , 103 , 103 , -1 , 103 , 103 , -1 }
};
// s state :0-9 ; r :100-104

struct stack_table
{
    int  data[100];
    int tops;
};
/*
    have two type : char (smybol_table)& int(state_table) ,change type char to int is ok ;
    so i use struct in int

*/
int state[]= {0,1,2,3,4,5,6,7,8,9}; //状态
char input_match[] = { 'i' , '+' , '*' , '(' , ')' , '#' ,'E'};
int store_pop_stack_smybol[128]= {0} ,store_pop_stack_state[128]= {0};
int store_pop_smybol_index = 0 , store_pop_state_index = 0;
int lookup_table_action(char input_char ,int state_of_stack) //action table
{
    int temp=0;
    for(temp ; temp <sizeof(input_match); temp++)
        if (input_char == input_match[temp])
            break;
    if(temp >= 7)
    {
        cout<<" YOU know something is happend! ,It is not'good !"<<endl;
        return -44;
    }

    return action[state_of_stack][temp];

}

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
    cout<<"push:"<<s->data[s->tops]<<endl;
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
int pop(stack_table *&s ,int &e)
{
    if(s->tops == -1)
    {
        cout<<"it is empty stack now!"<<endl;
        return 0;
    }
    e = s->data[s->tops];
    s->tops--;
    return 3 ;
}
int dis_symbol(stack_table *s) //展示目前的符号栈状态
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


int dis(stack_table *s) //展示目前的栈状态
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
        cout<<s->data[temp]<<"\t";
        temp--;
    };
    cout<<endl;
    return 1;
}

int re_value(stack_table *symbol_stack ,stack_table *state_stack,int re_num) //
{
    switch(re_num)
    {
    case 100:
        cout<<"POP 'E' out of symbol stack !"<<endl;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;

        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标

        push_sybmol(symbol_stack,'S');
        break;
    case 101:
        cout<<"POP 'E+E' out of symbol stack !"<<endl;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;

        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标


        push_sybmol(symbol_stack,'E');
        break;
    case 102 :
        cout<<"POP 'E*E' out of symbol stack !"<<endl;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;

        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标


        push_sybmol(symbol_stack,'E');
        break;
    case 103:
        cout<<"POP '(E)' out of symbol stack !"<<endl;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;

        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标
        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标

        push_sybmol(symbol_stack,'E');
        break;
    case 104:
        cout<<"POP 'i' out of symbol stack !"<<endl;
        pop(symbol_stack,store_pop_stack_smybol[store_pop_smybol_index]);
        store_pop_smybol_index++;

        pop( state_stack,store_pop_stack_state[store_pop_state_index]); //把 规约状态 栈顶元素POP
        store_pop_state_index++; //POP出去的下标

        push_sybmol(symbol_stack,'E');
        break;
    }
    return 2;
}

int main()
{
    int i = 0 , current_return ,temp=0;
    stack_table *state_stack , *symbol_stack;
    InitStack(state_stack);
    InitStack(symbol_stack);
    char *input = new char [20];

    cin>>input;

    push(state_stack,state[i]);//首先把状态0压栈
    push_sybmol(symbol_stack,'#');//首先把符号#压栈

    while(input != NULL)
    {
        current_return = lookup_table_action(input[i],state_stack->data[state_stack->tops]); //调用action表
        cout<<"current_return:"<<current_return<<endl;

        if(current_return == 44)
        {
            cout<<"SUCCESS ACC!!!!!!"<<endl ;//终止
            return 1;
        }
        else if (current_return >= 100 && current_return <= 104)
        {
            re_value(symbol_stack ,state_stack,current_return); /*规约 ,将之前符号栈顶POP，把规约的符号的压入栈中*/
            cout<<"POP the current stack:"<< state_stack->data[state_stack->tops]<<endl;

            current_return = lookup_table_action(symbol_stack->data[symbol_stack->tops],state_stack->data[state_stack->tops]);//查找GOTO表，
            if( current_return == -1)
            {
                cout<<"Somthing is bad"<<endl;
                return 1 ;
            }
            else
            {
                cout<<"push state  into stack $$$$$ " ;
                push(state_stack,current_return);//在把新的状态栈PUSH，到栈中
            }
            /*规约，调用栈顶状态的元素，和非终结符，查GOTO表，转到新状态，将之前栈顶除去，把新状态的压入栈中，回退终结符*/
        }

        else if (current_return >= 0 && current_return <= 9)
        {
            cout<<"push state  into stack $$$$$ " ;
            push(state_stack,current_return);//将N状态压入状态栈
            cout<<"push symbol  into stack move on " ;
            push_sybmol(symbol_stack,input[i]);//符号入栈
            //将N状态压入状态栈，并将终结符压入符号栈
            input++;//吃进新的符号串
        }
        else
        {
            cout<<"something wrong"<<endl;
            return 2;
        }

        cout<<"The cuurent of input string :\t"<<input<<endl;
        cout<<"THE Current  stack of state:"<<endl;
        dis(state_stack);
        cout<<"THE Current  stack of symbol_stack:"<<endl;
        dis_symbol(symbol_stack);

    }

    return 1;
}

#endif



