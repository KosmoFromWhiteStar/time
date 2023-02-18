#include <ctime>
#include <iostream>
#include <map>
#include <iomanip>

//Отключает индикатора ошибки не безопасной функции
#pragma warning(disable: 4996)

int main()
{
    std::map <std::time_t, std::string> date_birthday;
    std::time_t now = std::time(nullptr);
    std::tm now_date = *std::localtime(&now);

    std::cout << "Today " << std::put_time(&now_date, "%d.%m.%Y") << std::endl;
   

    //input friends
    do {
        std::time_t birthday = std::time(nullptr);
        std::tm date = *std::localtime(&birthday);

        std::cout << "Input birthday name name of your friend: " << std::endl;
        std::cout << "Day.month.year format" << std::endl;

        //ввод данных
        std::cin >> std::get_time(&date, "%d.%m.%Y");
        std::string name;
        std::cin >> name;
        if (name == "end") goto nex;


        //инициализация дат рождения в мапу
        date.tm_hour = 0;
        date.tm_min = 0;
        date.tm_sec = 0;
        date_birthday.insert(std::pair<std::time_t, std::string>(std::mktime(&date), name));
    } while (true);

nex:
    std::cout << std::endl;
    //вывод
    for (std::map<std::time_t, std::string>::iterator im = date_birthday.begin();
        im != date_birthday.end(); im++)
    {
        std::tm* temp_t = std::localtime(&(im->first));
        if(temp_t->tm_mon > now_date.tm_mon)
        {
            std::cout << std::put_time(temp_t, "%d.%m") << " " << im->second << std::endl;
        }
        else if (temp_t->tm_mon == now_date.tm_mon)
        {
            if (temp_t->tm_mday > now_date.tm_mday)
                std::cout << std::put_time(temp_t, "%d.%m") << " " << im->second << std::endl;
        }
    }

    return 0;
}