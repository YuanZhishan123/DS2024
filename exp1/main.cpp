#include <iostream>
#include<stdlib.h> 
#include<time.h>
#include<math.h>
#include"Vector.h"
using namespace std;
class Complex{
	private:
		double _real,_imag;
	public:
		Complex()
		{
			_real=double(rand());
			_imag=double(rand());
		}
		Complex(double a,double b)
		{
			_real=a;
			_imag=b;
		}
		double real()
		{
			return _real;
		}
		
		double imag()
		{
			return _imag;
		}
		double modulus() 
		{
			return pow((pow(_real,2)+pow(_imag,2)),0.5);
		}
		void Out()
		{
			cout<<"�ø���Ϊ:"<<_real<<"+"<<_imag<<"i"<<"ģΪ��"<<pow((pow(_real,2)+pow(_imag,2)),0.5)<<endl;
		}
};
int main(int argc, char** argv) {
	srand(time(NULL));
	int a=rand();
	int sa=0;//��ʵ��ͬ���� 
	Complex c(0,0);
	Complex c1,c2,c3;//��������� 
	Vector<Complex> m(a,0,c);
	cout<<"����"<<a<<"������"<<endl; 
	for(int i=0;i<a;i++)
	{
		Complex r;r.Out();
		m[i]=r;
	}
	//����
	m.unsort();
	//��ͬ���� 
 	
	//������� 
	m.insert(0,c1);
	m.insert(m.size()/2,c2);
	m.insert(c3);
	return 0;
}
