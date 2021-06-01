#include <iostream>
#include <string>
#include <chrono>
using namespace std;

class SmartPTR
{
private:
	int* _counter = nullptr;
	int* _data;
public:
	SmartPTR()
	{
		_data = new int;
		_counter = new int(0);
		*_counter = 1;
	}

	SmartPTR(int data)
	{
		_counter = new int(0);
		_data = new int;
		*_counter = 1;
		*_data = data;
	}

	~SmartPTR()
	{
		*_counter = *_counter - 1;
		if (*_counter <= 0)
		{
			delete[] _data;
			delete _counter;
		}
	}

	SmartPTR& operator=(const SmartPTR& ptr)
	{
		if (_data == ptr._data)
			return *this;

		if (_data != nullptr)
			delete[] _data;
		_data = ptr._data;

		_counter = ptr._counter;

		*_counter = *_counter + 1;

		return *this;
	}

	SmartPTR& operator=(SmartPTR&& ptr) noexcept
	{
		if (_data != nullptr)
			delete[] _data;
		_data = ptr._data;
		ptr._data = nullptr;
		return *this;
	}

	int& operator*()
	{
		return *_data;
	}

};

class CString
{
private:
	int some = 0;
	SmartPTR smartPTR;
public:
	CString()
	{
		*smartPTR = some;
	}


	CString(int val)
	{
		some = val;
		*smartPTR = some;
	}

	CString(CString&& sctr) = default;

	CString& operator=(const CString& cstr)
	{
		cout << "Data before copying: " << *smartPTR << endl;
		smartPTR = cstr.smartPTR;
		cout << "Data after copying: " << *smartPTR << endl;

		return *this;
	}

	CString& operator=(const CString&& cstr) noexcept
	{

		smartPTR = cstr.smartPTR;

		return *this;
	}
};

int main()
{
	CString CS1(1);
	CString CS4(4);
	CString CS11(11);
	CString CS44(44);

	cout << "CS4 = CS1;" << endl;
	CS4 = CS1;

	cout << "CS44 = CS11;" << endl;
	CS44 = CS1;

	cout << "CS4 = CS44;" << endl;
	CS4 = CS44;
}