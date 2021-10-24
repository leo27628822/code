#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


//function prototype
double procedence[6]={'(','+','-','*','/','^'};//operator的優先順序
double procedence1[6]={0,1,1,2,2,3};
double compute(double *);
void string_to_double(char *expression,double *postfix);
void infix_to_postfix(double *,double *);
double cmp(double pro);
int count(char *expression,int j);



int main(int argc,char *argv[])
{
	char expression[50], *expression1=argv[2];//宣告一個字串array 和一個字串指標來接所輸入的字串
	int c=0;
	int x;
	double result;
	double stack1[50];
	double postfix[50];
	char num[50];
	int position=0,j=0,i=0,k=0,m,n=0,len,counter=0;//i,j,k是用來計算的值


	len=strlen(expression1);//得到expression的長度
	expression1[len+1]='\0';

	if (argc==3&&strcmp("-p",argv[1])==0)
		string_to_double(expression1,postfix);
	/********************************************判斷做那一項指令***********************/
	else if ((argc==3&&strcmp("-te",argv[1])==0)||(argc==3&&(strcmp("-t",argv[1])==0)||(argc==3&&strcmp("-e",argv[1])==0)||(strcmp(argv[1],"-c")==0)))
		{
		for (m=0;expression1[m]!='\0';m++)//把資料一個個放進下一個array儲存因為不要改變它的array
		   if (expression1[m]!=' ')
			   expression[n++]=expression1[m];
		   expression[n]='\0';
		   n=0;
	for (i=0;expression[i]!='\0';i++)
			{if (expression[0]=='-'||expression[i]=='-'&&(expression[i-1]=='+'||expression[i-1]=='-'||expression[i-1]=='/'||expression[i-1]=='*'||expression[i-1]=='^'||expression[i-1]=='('||expression[i-1]==')'))
			  if (expression[i]=='-'&&expression[i+1]!='('&&expression[i-1]!=')')
				expression[i]='_';}
	for (i=0;expression[i]!='\0';i++)
		if (expression[i]=='\n')
			expression[i]='\0';
	while (expression[j]!='\0')
		{

  for (;expression[j]!='\0'&&expression[j]!='+'&&expression[j]!='-'&&expression[j]!='/'&&expression[j]!='*'&&expression[j]!='^'&&expression[j]!='('&&expression[j]!=')';j++)
			num[k++]=expression[j];
			num[k]='\0';

			k=0;

		for (i=0;num[i]!='\0';i++)//檢察被除是否等於0
			{if (num[i]=='_')
				num[i]='-';}
		if (stack1[c-1]=='-'&&expression[j]=='('&&c-1==0)
			{c--;
			stack1[c++]=-1;}

		if (num[0]!='\0')
			stack1[c++]=atof(num);
		if (stack1[c-1]=='0')
			{printf("error,divisor cannot be zero\n");
			return 0;}
			counter=count(expression,j);

			if (counter!=0&&j!=0&&expression[j]=='('&& (stack1[c-1]!='\0'&&stack1[c-1]!='+'&&stack1[c-1]!='-'&&stack1[c-1]!='/'&&stack1[c-1]!='*'&&stack1[c-1]!='^'&&stack1[c-1]!='('))
				stack1[c++]='*';

		if(expression[j]=='+'||expression[j]=='-'||expression[j]=='/'||expression[j]=='*'||expression[j]=='^'||expression[j]=='('||expression[j]==')')
		stack1[c++]=expression[j];//放進運算元



		j++;
		}
	stack1[c]='\0';


	infix_to_postfix(stack1,postfix);
	/********************************************te**************************/
	if (strcmp("-te",argv[1])==0||strcmp("-t",argv[1])==0)
	{for (i=0;postfix[i]!='\0';i++)
		if(postfix[i]=='+'||postfix[i]=='-'||postfix[i]=='/'||postfix[i]=='*'||postfix[i]=='^'||postfix[i]=='('||postfix[i]==')')
		{x=(int)postfix[i];
		printf("%c ",x);}
		else
		printf("%g ",postfix[i]);
		}

	}
	printf("\n");

	 result=compute(postfix);
	 if (result!=EOF)
	 if ((argc==3&&strcmp("-te",argv[1])==0)||(argc==3&&strcmp("-e",argv[1]))==0||(argc==3&&strcmp("-p",argv[1])==0))
		 printf("result=%g\n",result);
	 else if (strcmp(argv[1],"-c")==0)
			 printf("legal\n");
	 return 0;
}
int count(char *expression,int j)
{	int i=0;
	for (;expression[j]!='\0';j++)
		if (expression[j]=='+'||expression[j]=='-'||expression[j]=='/'||expression[j]=='*'||expression[j]=='^')
			i++;
		return i;
}
double compute(double *postfix)
{	double stack[50];
	int i,j=0;
	double op1,op2;
	double result,x;

	for (i=0;postfix[i]!='\0';i++)
		{if (postfix[i]!='\0'&&postfix[i]!='+'&&postfix[i]!='-'&&postfix[i]!='/'&&postfix[i]!='*'&&postfix[i]!='^')
			stack[j++]=postfix[i];
		 else
			 x=postfix[i];
		 if (x=='+')
			{op1=stack[--j];
		   if (j<=0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		     op2=stack[--j];
		   if (j<0)
			{printf("\nerror,illegal expression.");
			return EOF;}
			 stack[j++]=(op2+op1);}
		 else if (x=='-')
			{op1=stack[--j];
		  if (j<=0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		     op2=stack[--j];
		   if (j<0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		   if (op2==0)
			 stack[j++]=(op1-op2);
		   else
			 stack[j++]=(op2-op1);}
	    else  if (x=='*')
			{op1=stack[--j];
		 if (j<=0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		     op2=stack[--j];
		if (j<0)
			{printf("\nerror,illegal expression.");
			return EOF;}
			 stack[j++]=(op2*op1);}
		else if (x=='/')
			{op1=stack[--j];
		 if (j<=0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		     op2=stack[--j];
			if (j<0||op1==0)
			{printf("\nerror,illegal expression.");
			return EOF;}
			 stack[j++]=(op2/op1);}
		else if (x=='^')
			{op1=stack[--j];
			 if (j<=0)
			{printf("\nerror,illegal expression.");
			return EOF;}
		     op2=stack[--j];
			  if (j<0)
			{printf("\nerror,illegal expression.");
			return EOF;}
			 stack[j++]=pow(op2,op1);}
			x=0;
			 }
		   if (j-1>0)
		   {printf("\nerror,illegal expression.");
		   return EOF;}
			 result=stack[0];
			return result;
}




void infix_to_postfix(double *infix,double *postfix)
{	int i,k=-1,j=-1;
	double temp[50],x,y;
	for (i=0;infix[i++]!='\0';)
		{x=infix[i-1];

		if (x=='(')
		temp[++k]=x;
	    else if (x==')')//輸入為),則內輸出堆疊內運算字
			while (k>=0  && (x=temp[k--])!='(')
				   postfix[++j]=x;
	     else if (x=='+'||x=='-'||x=='*'||x=='/'||x=='^')//輸入為運算子，小于堆疊中的值，將堆疊中運算字輸出，
                                                         //如大于等于堆疊中所指運算字，將輸入的運算子放入
														 //堆疊
			{y=temp[k];//優先順序
		     while (cmp(y)>cmp(x))
				{postfix[++j]=temp[k--];
				y=temp[k];}
			 temp[++k]=x;
			}
		 else
			 postfix[++j]=x;
		}
	while (k>=0)
		postfix[++j]=temp[k--];
	postfix[++j]='\0';
}

double cmp(double pro)//比較兩運算子優先權
{	int i=0;
	for (i=0;i<6;i++)
     if (procedence[i]==pro)
	  return procedence1[i];
	 return -1;
}

void string_to_double(char *expression,double *postfix)//字串變為函數
{
	int i=0,j=0,k=0;
	char num[50];
	while (expression[i]!='\0')
	{for (;expression[i]!=' '&&expression[i]!='\0';i++)//檢查字串是否結束
		if (expression[i]!=' ')
			num[j++]=expression[i];
		num[j]='\0';
	if (num[0]!='\0')
	{if (num[j-1]!='+'&&num[j-1]!='-'&&num[j-1]!='/'&&num[j-1]!='*'&&num[j-1]!='^')
		postfix[k++]=atof(num);
	else
		postfix[k++]=expression[i-1];
	}

	i++;
	j=0;
	}
	postfix[k]='\0';
}
