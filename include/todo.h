#pragma once
#include <fstream>
#include <cstring>
#include <vector>

struct Todo;

using namespace std;

extern fstream todoFile;
extern vector<Todo> AllTodos;
extern int lastID;

void viewTODOS(void);
void load(fstream* file);
void insertTodo(Todo td, ofstream* file);
Todo parseAndReturnTodo(string line);
int markTodoAsDoneAndRewriteTODOS(int todoID, ofstream* file);

struct Todo
{
    unsigned int ID = -1;
    string name;
    string details;
    bool isDone;

    static Todo createTodo(string name, string details, int last)
    {
        Todo td;
        td.details = details;
        td.name    = name;
        td.ID = last + 1;
        td.isDone = false;

        return td;
    }

    static Todo createTodo(string name, string details, int id, bool isdone)
    {
        Todo td;
        td.details = details;
        td.name = name;
        td.ID = id;
        td.isDone = isdone;
        return td;
    }
};
