/*
作者：何文官
时间：2014-5-12
用途：1-自能识别一个单词的状态自动机
      2-能去除空白符
      3-能识别关键字 while if else case switch
转换图的来源：编译原理教材 胡元义 第三版 P13 图2-5
缺点：1-不具备标识符重名报错功能；
版本：V1.0
*/

/*
作者：何文官
时间：2014-5-29
用途：1-自能识别单词的状态自动机
      2-能去除空白符
      3-能识别关键字 while if else case switch
转换图的来源：编译原理教材 胡元义 第三版 P13 图2-5
缺点：1-不具备标识符重名报错功能；
版本：V2.0
改进：可以识别一串单词，不仅仅是一个词
*/
/*
作者：何文官
时间：2014-5-30
用途：1-自能识别单词的状态自动机
      2-能去除空白符
      3-能识别关键字 while if else case switch
转换图的来源：编译原理教材 胡元义 第三版 P13 图2-5
缺点：1-不具备标识符重名报错功能；
版本：V2.0
改进：可以识别一串单词，不仅仅是一个词,修改大部分BUG
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void put_return(char s)
{
    printf("this is a :(%c,NULL)\n",s);
}

void lookup(char *source ,char *destion)/*填表*/
{
    int temp_local = 0 ;
    if( destion [ temp_local ] == '\0') //插入第一个符号
    {
        int  source_num=0,destion_num = 0;

        while( source[source_num] && source [ source_num ] != '#')

            destion[ destion_num++ ] = source [ source_num++ ] ;


        printf("this is a symbol:(%s,0x%x)\n",destion,destion); /*输出标识符，及其地址*/
        destion[ destion_num++ ] = source [ source_num++ ] ;//把#赋值给destion
    }
    else
    {
        int i = 0 ,c=0;
        for(i=0;  destion[i] != '\0' ; i++) //排除上次输入的单词
            c++;
        //   printf("c=%d\n",c);
        for(  ; source[i] != '#' ; i++ )
            destion[i] = source[i] ;
        printf("this is a symbol:(%s,0x%x)\n",destion+c,destion+8*c);
        destion[i] = source[i] ; //把#赋值给destion
        // printf("it is pretty good : %d \n",i);
    }
}


int main()
{
    char token[128]= {0} , token_digit[128]= {0} ,character[128]= {0} ,biaoshifu[128]= {0} ,digit_const[128]= {0} ;
    /*token 是存放单词符号字符串的数组
      character 是储存输入的字符串的数组
      biaoshifu 是储存标识符的数组
      digit_const  是储存常数的数组
    */
    char *com[]= {"while","if","else","switch","case"};

    int i,input=0,temp=0,run=0,start=0,start_digit=0,flag=0,mem_smybol_num=0 , mem_digit = 0;

    while(1)   /*获取键盘的输入*/
    {
        character[input] = getchar();

        if(character[input] =='\n')
            break;
        input++;
    };
    character[input] = '\0';
    while( character[run] )
    {

        switch(character[run])
        {

        case ' ':
            while(character[run] == ' ') /*去除空格*/
                run++; //吃进一个字符
            run--;//回退一个字符 ，因为最while循环 有一个run++;
            break;
        case 'a': /*识别标识符*/
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            while(isalnum(character[run]))
            {
                token[start] =character[run];
                start++;
                run++; /* 吃进新字符 */
                //  mem_smybol_num++;
            }
            run--; /*回退一个字符*/
            for(i =0 ; i<5 ; i++)  /*保留字的识别*/
                if( !strcmp(token,com[i]) )
                {
                    flag = 1 ;
                    break;
                }
            if( flag ) /*若是保留字，则返回保留字*/
            {
                printf("This is a reserve symbol:(%s ,%d)\n ",com[i],i+1);
                flag = 0 ; //清零，防止第二次非保留字，也进入保留字
                token[start] = '#' ;
                start++;
                lookup(token,biaoshifu);
            }
            else
            {
                token[start] = '#';
                start++;
                lookup(token,biaoshifu);

            }
            break;
        case '0':/*识别数字*/
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            while(isdigit(character[run]))
            {
                token_digit[start_digit] =character[run];
                start_digit++;
                run++;
            }
            run--;/*回退一个字符*/
            //printf("%s\n",token);
            lookup(token_digit,digit_const);
            break;

        case '<':
            run++;
            if(character[run] == '=')
                printf("(relop,LE)");
            else
            {
                run--;
                printf("(relop,LT)");
            }
            break;
        case '=':
            run++ ;
            if(character[run] == '=')
                printf("(relop,EQ) \n");
            else
            {
                run--;
                put_return('=');
            }
            break;
        case '+':
            put_return('+');
            break;
        case '-':
            put_return('-');
            break;
        case '*':
            put_return('*');
            break;
        case ';':
            put_return(':');
            break;
        default :
            printf("It is something wrong \n");
            break;
        }
        run++;
    };
    return 0;
}
