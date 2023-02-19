#include <iostream>
#include <ctime>
#include <time.h>
#include <iomanip>

#pragma warning(disable: 4996)

int  main()
{
	//���� ����������
	std::time_t timer = std::time(nullptr);
	std::tm temp = *std::localtime(&timer);
	
	//���� ������������� ��������� �������
	std::cout << "Timer\nInput time: (Min Sec)\n";
	std::cin >> std::get_time(&temp, "%M %S");

	timer = std::time(nullptr);
	std::tm end_timer = *std::localtime(&timer);
	end_timer.tm_min += temp.tm_min;
	end_timer.tm_sec += temp.tm_sec;

	
	while (true)
	{
		if (std::time(nullptr) == std::mktime(&end_timer)) break;
	}
	std::cout << "Ding! Ding! Ding!";
	return 0;
}
