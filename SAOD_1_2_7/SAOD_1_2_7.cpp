#include <iostream>
#include <set>
#include <locale>
#include <ctime>
#include <conio.h>

using namespace std;

struct QueueElement
{
    char info;
    QueueElement* next;
};

void InitQueue(QueueElement** begin, QueueElement** end) // Инициализация очереди
{
    *begin = new QueueElement;
    (* begin)->next = NULL;
    *end = *begin;
}

bool isEmpty(QueueElement* q) // Проверка очереди на пустоту
{
    if (q->next == NULL)
    {
        return true;
    }
    return false;
}

void Delete(QueueElement** Begin, QueueElement** End) // Удаление элемента из начала очереди
{
    if (!isEmpty(*Begin))
    {
        QueueElement* pTemp = (*Begin)->next;
        (*Begin)->next = pTemp->next;
        if (isEmpty(*Begin))
        {
            *End = *Begin;
        }
        delete pTemp;
    }
}

void Add(QueueElement** end, char info, bool& work) // Добавление элемента в конец очереди 
{
    try
    {
        QueueElement* newQ = new QueueElement;
        newQ->info = info;
        newQ->next = NULL;
        (*end)->next = newQ;
        *end = newQ;
    }
    catch (const std::exception&)
    {
        cout << "Очередь заполнена!";
        work = false;
    }
}

void PrintQueue(QueueElement* begin, QueueElement* end) // Вывод текущего состояния очереди
{
    if (isEmpty(begin))
    {
        cout << "Пусто";
    }
    else
    {
        QueueElement* current = begin->next;
        while (current != NULL)
        {
            cout << current->info << " ";
            current = current->next;
        } 
    }
}

void CleanMemory(QueueElement* begin) // очищение памяти 
{
    QueueElement* q = begin;
    while (begin != NULL)
    {
        begin = begin->next;
        delete q;
        q = begin;
    }
}

void Working(QueueElement* Begin, QueueElement* End) // работа случайной очереди 
{
    bool work = true;
    while (work)
    {
        int timeBegin = clock();
        char ch;
        while (clock() - timeBegin < 3000)
        {
            if (_kbhit() && (_getch() == 'q')) // реагирует на нажатие клавиши 'q'
            {
                work = false;
                break;
            }
        }
        if (!work)
        {
            CleanMemory(Begin);
            break;
        }
        cout << "Операция: ";
        int choice = (rand() % 99 + 1) % 2;
        int amount = rand() % 3 + 1;
        if (choice == 0)
        {
            cout << "Добавление ";
            for (int i = 0; i < amount; i++)
            {
                char letter = rand() % 26 + 65;
                Add(&End,letter,work);
            }
        }
        else
        {
            cout << "Удаление ";
            for (int i = 0; i < amount; i++)
            {
                Delete(&Begin,&End);
            }
        }
        cout << amount << " элементов(-а)\n";
        cout << "Текущая очередь: ";
        PrintQueue(Begin,End);
        cout<<"\n\n";
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL)); cout << "Датчик псевдослечайных чисел активирован ...\n";
    QueueElement* Begin;
    QueueElement* End;
    InitQueue(&Begin, &End);
    Working(Begin,End);
    return 0;
}