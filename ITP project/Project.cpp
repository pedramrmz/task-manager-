#include <iostream>
#include <conio.h>
#include <string>
#include <bits/stdc++.h>
#include <limits>

#include "TextTable.h"

using namespace std;

struct task
{
    // char *title = (char *)malloc(100 * sizeof(char));
    // char *descr = (char *)malloc(400 * sizeof(char));

    string title;
    string descr;
    int prior;
    int ydeadline, mdeadline, ddeadline;
};

int handleShowCommands(char key, struct task *ts, int taskCount);

// void copy_char(char *source, char *dest)
// {
//     int len = 0;
//     while (source[len] != '\0')
//         len++;
//     for (int i = 0; i < len; i++)
//         dest[i] = source[i];
// }

// void newTask(struct task *t, int index, char *T, char *D, int P, int YD, int MD, int DD)

void newTask(struct task *t, int index, string T, string D, int P, int YD, int MD, int DD)
{
    t[index].title = T;
    t[index].descr = D;
    t[index].prior = P;
    t[index].ydeadline = YD;
    t[index].mdeadline = MD;
    t[index].ddeadline = DD;
}

void deleteRow(struct task *ts, int deleteIndex, int &taskCount)
{
    struct task task;
    for (int i = deleteIndex - 1; i < taskCount; i++)
    {
        task = ts[i];
        ts[i] = ts[i + 1];
        ts[i + 1] = task;
        taskCount--;
    }
}

void printAll(struct task *ts, int taskCount)
{
    TextTable t('-', '|', '+');

    t.add("");
    t.add("Title");
    t.add("Description");
    t.add("Priority");
    t.add("Deadline");
    t.endOfRow();

    string deadline;
    int index = 1;

    for (int i = 0; i < taskCount; i++)
    {
        deadline = to_string(ts[i].ydeadline) 
            + '/' + to_string(ts[i].mdeadline) 
            + '/' + to_string(ts[i].ddeadline);

        t.add(to_string(index++));
        t.add(ts[i].title);
        t.add(ts[i].descr);
        t.add(to_string(ts[i].prior));
        t.add(deadline);

        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
}

// void print(struct task t)
// {
//     cout << "title: " << t.title << "\n";
//     cout << "descr: " << t.descr << "\n";
//     cout << "prior: " << t.prior << "\n";
//     cout << "deadline: " << t.ydeadline << '/' << t.mdeadline << '/' << t.ddeadline << "\n";
//     getch();
// }

// void swap(struct task &t1, struct task &t2)
// {
//     struct task tmp;
//     tmp = t1;
//     t1 = t2;
//     t2 = tmp;
// }

bool compareTask(struct task t1, struct task t2)
{
    if (t1.prior > t2.prior)
    {
        return 1;
    }

    return 0;
}

void taskSorter(struct task *ts, int taskCount)
{
    sort(ts, &ts[taskCount], compareTask);
}

// void mySort(struct task *t, int n)
// {
//     int j = 0;
//     while (t[j].prior < t[j + 1].prior)
//     {
//         swap(t[j], t[j + 1]);
//         j++;
//         if (j == n)
//             break;
//     }
// }

string readString(string caption)
{
    string myString;
    bool firstRun = true;

    cout << "enter the " + caption + ": \n";
    getline(cin, myString);

    while (myString == "")
    {
        if (!firstRun)
            cout << "Incorrect, enter the " + caption + ":\n";
        getline(cin, myString);
        firstRun = false;
    }

    return myString;
}

int readInteger(string caption)
{
    int number;
    cout << "enter the " + caption + ": \n";
    cin >> number;

    while (1)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect, enter the " + caption + ":\n";
            cin >> number;
        }
        if (!cin.fail())
            break;
    }

    return number;
}

int readIntegerWithMax(string caption, int maximum)
{
    int myNumber;
    myNumber = readInteger(caption);

    while (myNumber > maximum)
    {
        cout << "Entered number is bigger than " << maximum << ", enter a smaller number:\n";
        cin >> myNumber;
    }

    return myNumber;
}

void handleAddTask(struct task *ts, int &taskCount)
{
    int prior;
    int ydeadline;
    int mdeadline;
    int ddeadline;
    string title;
    string descr;

    title = readString("title");
    descr = readString("description");
    prior = readInteger("priority");
    ydeadline = readIntegerWithMax("year", 2022);
    mdeadline = readIntegerWithMax("month", 12);
    ddeadline = readIntegerWithMax("day", 31);

    newTask(ts, taskCount, title, descr, prior, ydeadline, mdeadline, ddeadline);
    taskCount++;
}

void printMenu(struct task *ts, int &taskCount)
{
    int flag = 1;
    while (flag)
    {
        cout << "\033[3;102;30mwelcom to my task manager\033[0m"
            << "\n";

        cout << "                    1)add a new task"
             << "\n";
        cout << "                       2)show tasks"
             << "\n";
        cout << "                          3)exit"
             << "\n";

        int number;
        cin >> number;

        switch (number)
        {
        case 1:
            handleAddTask(ts, taskCount);
            break;
        case 2:
            // clear screen
            cout << "\033[2J\033[1;1J";

            char showCommandKey;

            printAll(ts, taskCount);

            cout << "\nFor Sorting Enter S";
            cout << "\nFor Deleteing Enter D";
            cout << "\nEnter M for going to the menu\n";

            cin >> showCommandKey;

            handleShowCommands(showCommandKey, ts, taskCount);
        case 3:
            flag = 0;
            break;
        default:
            cout << "you are not in 1-3\n"
                 << endl;
        }
    }
}

int handleShowCommands(char key, struct task *ts, int taskCount)
{
    switch (key)
    {
    case 'S':
        // for (int i = 0; i <= taskCount; i++)
        //     mySort(&ts[i], taskCount);

        taskSorter(ts, taskCount);
        printAll(ts, taskCount);
        getch();
        printMenu(ts, taskCount);
        break;
    case 'D':
        cout << "\n Enter the row index you wish to delete.";
        int deleteIndex;
        cin >> deleteIndex;
        while (deleteIndex > taskCount)
        {
            cout << "\n Index is out of range.";
            cin >> deleteIndex;
        }

        deleteRow(ts, deleteIndex, taskCount);
        printAll(ts, taskCount);
        getch();
        printMenu(ts, taskCount);
        break;
    case 'M':
        printMenu(ts, taskCount);
        break;
    default:
        cout << "invalid command";
    }

    return 0;
}

//**************************************************************
int main()
{
    struct task tasks[1000];
    int i = 0;
    printMenu(tasks, i);

    return 0;
}