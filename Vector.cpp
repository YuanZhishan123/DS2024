typedef int Rank;
#ifndef HEADER_FILE
#define HEADER_FILE
#define DEFAULT_CAPACITY 3
#include<stdlib.h>
#include<iostream>
#endif
using namespace std;
template <typename T> class Vector{
protected:
	Rank _size;int _capacity;T* _elem;
	void copyFrom(T const*a,Rank lo,Rank hi)//复制数组A[lo,hi)
	{
		_elem=new T[_capacity=(hi-lo)*2];
		_size=0;
		while(lo<hi)
		{
			_elem[_size++]=a[lo++];
		}
	}
	void expand()//扩容 
	{
		if(_size<_capacity) return;
		if(_capacity<DEFAULT_CAPACITY) _capacity=DEFAULT_CAPACITY;
		T*oldelem=_elem;
		_elem=new T[_capacity <<=1];
		for(int i=0;i<_size;i++)
			_elem[i]=oldelem[i];
		delete [] oldelem;
		
	}
	void shrink()
	{
		if(_capacity<DEFAULT_CAPACITY) return;
		if(_size<<2 > _capacity) return;
		T * oldElem=_elem;
		_elem=new T[_capacity>>=1];
		for(int i=0;i<_size;i++)
		{
			_elem[i]=oldElem[i];
		}
		delete [] oldElem;
	}
	

public:
	//构造函数 
	Vector(int c=DEFAULT_CAPACITY,int s=0, T v=0)
	{_elem=new T[_capacity=c];for(_size=0;_size<s;_elem[_size++]=v);}//容量为c,规模为s，所有元素初始为v 
	//析构函数
	~Vector(){delete [] _elem;}
	//只读接口 
	int size()const{return _size;}//规模 
	bool empty()const{return !_size;}//判空 
	Rank find(T const& e)const//无序整体查找 
	{
		return find(e,0,_size);
	}
    Rank find(T const& e,Rank lo,Rank hi)const  //无序区间查找 返回最后的符合的秩 
	{
		while((lo<hi--)&&(e != _elem[hi]));
		if(hi<lo) return -1;
		else
		return hi;
	}                                        
	Rank search(T const &e,Rank lo,Rank hi);//有序区间查找(未完成) 
	
	//有序整体查找 （未完成）
	//可写接口 
	
	void mergeSort() {  //归并排序 
        mergeSort(0, _size);  
    }  
  
    void mergeSort(Rank lo, Rank hi) {  
        if (hi - lo < 2) return;  
        Rank mi = (lo + hi) / 2;  
        mergeSort(lo, mi);  
        mergeSort(mi, hi);  
        merge(lo, mi, hi);  
    }  
  
    void merge(Rank lo, Rank mi, Rank hi) {  
        T* a = _elem + lo;  
        int lb = mi - lo;  
        T* b = new T[lb];  
        for (Rank i = 0; i < lb; ++i) {  
            b[i] = a[i];  
        }  
        int lc = hi - mi;  
        T* c = _elem + mi;  
        Rank i = 0, j = 0, k = lo;  
        while (j < lb && k < hi) {  
            if (b[j] <= c[k - mi]) {  
                a[i++] = b[j++];  
            } else {  
                a[i++] = c[k++];  
            }  
        }  
        while (j < lb) {  
            a[i++] = b[j++];  
        }  
        while (k < hi) {  
            a[i++] = c[k++];  
        }  
        delete[] b;  
    }  
	bool bubble(Rank lo,Rank hi)//冒泡单趟 
		{
			bool sorted=true;
			while(lo++<hi)
			{
				if(_elem[lo-1]>_elem[lo])
				{
					sorted=false;
					swap(_elem[lo-1],_elem[lo]);
				}
			}
			return sorted;
		}
	void bubbleSort(Rank lo,Rank hi)//冒泡排序
	{
		while(!bubble(lo,hi--));
	}
	void unsort(Rank lo,Rank hi)//置乱
	{
		T*a=_elem+lo;
		for(Rank i=hi-lo;i>0;i--)
			swap(a[i-1],a[rand() %i]);
	} 
	void unsort(){unsort(0,_size);}//整体置乱 
	Rank insert(Rank r,T const&e)//在r位置插入
	{
		expand();
		for(int i=_size;i>r;i--)
			_elem[i]=_elem[i-1];
			_size++;
			_elem[r]=e;
		return r;
	} 
	Rank insert(T const&e) {insert(_size,e);}//默认末尾插入 
	T remove(Rank r){T e=_elem[r];remove(r,r+1);return e;}//删除秩为r的元素
	int remove(Rank lo,Rank hi)//删除[lo,hi)的元素
	{
		if(hi==lo) return 0;
		while(hi<_size) _elem[lo++]=_elem[hi++];
		_size=lo;
		shrink();
		return hi-lo;
	}
	int deduplicate() //无序去重 
	{  
    int oldSize = _size;  
    Rank i = 1;  
    while (i < _size) {  
        Rank pos = find(_elem[i], 0, i);  
        if (pos >= 0) {   
            remove(i);  
            
        } else {  
            i++;   
        	}  
    	}  
    shrink();  
    return oldSize - _size;  
	}
	T &operator[] (Rank r)const//重载运算符[]
	{
		return _elem[r];
	}
	Vector<T>&operator= (Vector<T> const &a)//重载运算符=
	{
		if(_elem) delete [] _elem;
		copyFrom(a._elem,0,a.size());
		return *this;
	} 
};
