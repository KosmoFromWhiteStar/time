#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>


struct task_status
{
    std::time_t time_start = std::time(nullptr);
    std::time_t end_time;
    std::tm* time_start_point;
    std::string name;
};

bool compare(std::string word, std::string command)
{
    for (int i = 0; (i < command.length()) && (i < word.length()); i++)
    {
        if ((command[i] != word[i]) && (word[i] != command[i] + 32) && (word[i] != command[i] - 32))
            return false;
    }
    return true;
}

void end_task(task_status* task, std::map <std::string, std::time_t>* task_done)
{
    std::cout << "End task " << task->name << std::endl;
    task->end_time = std::time(nullptr);
    double val_time_dif = std::difftime(task->end_time, task->time_start);
    std::tm* nt = std::localtime(&task->end_time);

    nt->tm_min = 0;
    nt->tm_sec = val_time_dif;

    std::cout << "Time in " << task->name << " " << std::put_time(nt, "%M min %S sec") << std::endl;

    std::time_t temp_time = std::mktime(nt);
    std::pair <std::string, std::time_t> task_complete(task->name, temp_time);
    task_done->insert(task_complete);
}

void task_output(std::map <std::string, std::time_t>* list)
{
    for (std::map<std::string, std::time_t>::iterator im = list->begin();
        im != list->end(); im++)
    {
        std::tm* task_T = std::localtime(&(im->second));
        std::cout << "Task: " << im->first << " " << " it takes time: "
            << std::put_time(task_T, "%M:%S") << std::endl;
    }


}

int main()
{
    std::map <std::string, std::time_t> task_done;
    std::string command;
    bool task_active = false;
    task_status task_time;

    do {
        std::cout << "Input command: \n";
        std::cin >> command;

        if (compare(command, "begin")) {
            // Begin time task
            if (task_active)
            {
                end_task(&task_time, &task_done);
                goto t;
            }
            else {
            t:
                std::cout << "Input your task:";
                std::cin >> task_time.name;
                task_time.time_start = std::time(nullptr);
                task_time.time_start_point = std::localtime(&(task_time.time_start));
                task_active = true;
            }
        }
        else if (compare(command, "end"))
        {
            if (!task_active) std::cout << "Haven't active task\n";
            else
            {
                end_task(&task_time, &task_done);
                task_active = false;
            }

        }
        else if (compare(command, "status"))
        {
            //status on console
            if (task_active)
            {
                double val_time_dif = std::difftime(task_time.end_time, task_time.time_start);
                std::tm* nt = std::localtime(&task_time.end_time);

                nt->tm_min = 0;
                nt->tm_sec = val_time_dif;

                std::cout << "Time in " << task_time.name << " " << std::put_time(nt, "%M min %S sec") << std::endl;
            }
            task_output(&task_done);

        }
        else if (compare(command, "exit")) {
            std::cout << "Exit program";
            if (task_active) end_task(&task_time, &task_done);
            return 0;
        }
        system("pause");
    } while (true);
}