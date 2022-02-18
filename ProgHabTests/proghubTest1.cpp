#include <iostream>
class A
{
	int m_var;
public:	
	A() : m_var(0){}
	int const& getVarRef() const{return m_var;}
	int* getVarPtr() {return &m_var;}
};

int main(){
	A obj;
	{
		auto var = obj.getVarRef();
		var += 10;
	}
	std::cout << obj.getVarRef() << std::endl;
	std::cout << obj.getVarPtr() << std::endl;
	
	{
		auto var = obj.getVarPtr();
		std::cout << var << std::endl;
		*var += 10;
	}
	std::cout << obj.getVarRef();
	
	return 0;
}