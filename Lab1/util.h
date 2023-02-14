#pragma once
#include <iostream>

namespace util
{
	void CleanWcin()
	{
		if (char(std::wcin.peek()) == '\n')
			std::wcin.ignore();

		if (std::wcin.fail())
		{
			std::wcin.clear();
			std::wcin.ignore(32767, '\n');
		}
	}


	std::wstring to_wstring(int number)
	{
		int size = 0;

		// вычисляем кол-во разрядов числа
		for (int temp_num = number; temp_num != 0; size++)
		{
			temp_num /= 10;
		}

		wchar_t* wc_number = new wchar_t[size];
		for (int i = size - 1; number != 0; i--)
		{
			int temp = number % 10;
			temp += 48;
			wc_number[i] = temp;
			number /= 10;
		}
		wcscat(wc_number, L"\0");

		return std::wstring(wc_number);
	}
}
