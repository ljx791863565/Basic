#include <iostream>
#include <cstddef>

#define INIT_SIZE 100
class MyVector
{
public:
	MyVector()
		:size_(INIT_SIZE)
	{
		data_ = new int[size_];
	}

	~MyVector()
	{
		delete [] data_;
		data_ = nullptr;
	}
	MyVector(const MyVector &mv)
	{
		size_ = mv.size_;
		data_ = new int[size_];
		std::copy(mv.data_, mv.data_ + mv.size_, data_);
	}

	MyVector(MyVector && mv)
	{
		size_ = mv.size_;
		data_ = mv.data_;
		mv.size_ = 0;
		mv.data_ = nullptr;
	}

private:
	int *data_;
	size_t size_;
};


int main(int argc, const char *argv[])
{
	MyVector mv;
	MyVector mv1 = mv;
	MyVector mv2 = std::move(mv);
	return 0;
}
