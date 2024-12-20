#include"Stack.cpp"
#include<string>
#include<cmath>
#define N_OPTR 9 //运算符总数
using namespace std;


 const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
    /*              |-------------------- 当 前 运 算 符 --------------------| */
    /*              +      -      *      /      ^      !      (      )      \0 */
    /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
    /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
    /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
    /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',    ' ',   ' ',
    /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};
int change(char s){
	if(s=='+') return 0;
	else if(s=='-')return 1;
	else if(s=='*')return 2;
	else if(s=='/')return 3;
	else if(s=='^')return 4;
	else if(s=='!')return 5;
	else if(s=='(')return 6;
	else if(s==')')return 7;
	else if(s=='\0')return 8;
}
char priority(char x,char y){
	int xc=change(x);
	int yc=change(y);
	return pri[xc][yc];
}
double calcu(double num){
	double x=1;
	for(int i=1;i<=int(num);i++)
	x*=i;
	return double(x);
}
double calcu(double num1,char s,double num2){
	if(s=='+') return double(num1)+double(num2);
	else if(s=='-')return double(num1)-double(num2);
	else if(s=='*')return double(num1)*double(num2);
	else if(s=='/')return double(num1)/double(num2);
	else if(s=='^')return pow(double(num1),double(num2));
}
double evaluate(string expression) {
    Stack<double> values; 
    Stack<char> ops; 

    for (int i = 0; i < expression.length(); i++) {
        if (isspace(expression[i])) continue;

      
        if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;  
        }
            
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
            
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(calcu(val1,op,val2));
            }
            ops.pop();
        }
        else if(expression[i] == '!'){
        	values.push(calcu(values.pop()));
		}
         
        else {
           
            while (!ops.empty() && !(priority(ops.top(),expression[i])=='<')) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(calcu(val1,op,val2));
            }
            ops.push(expression[i]);
        }
    }

    
    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(calcu(val1,op,val2));
    }

   
    return values.top();
}

int main(){
string a="2+3!*(1+2)^2";
cout<<a<<"="<<evaluate(a)<<endl;	
return 0;
}
