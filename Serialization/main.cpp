#include "Serialization.h"

class A
{
	int* a;
	int b;
};

int main()
{
	Stream s;

	//int a[5]{1,2,3,4,5};
	int* ip = new int(10);
	int i = 100;

	s.write(i);
	s.write(ip);

	auto ip_ = s.read<int*>();
	auto i_ = s.read<int>();
	//auto a_ = s.read<int,5>();

	//std::cout << c << std::endl;
	//for (size_t i = 0; i < sizeof(a)/4; ++i)
	//	std::cout << a_[i];
	return 0;
}