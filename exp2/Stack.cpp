#include "Vector.cpp"
template <typename T> 
class Stack:public Vector <T>{
public:

	void push(const T &e){
		this->insert(e);
	}
	T pop(){
		return this->remove(this->size()-1);
	}
	T & top(){
		return (*this)[this->size()-1];
	}
};
