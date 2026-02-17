#include "../include/todo.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<Todo> AllTodos;

Todo parseAndReturnTodo(string line) {
    if (line.empty() || line.front() == '#') return Todo{}; // empty struct

    stringstream ss(line);
    string token;
    vector<string> fields;

    while (getline(ss, token, '$')) {
        fields.push_back(token);
    }

    if (fields.size() < 4) {
        cerr << "Invalid line: " << line << endl;
        return Todo{};
    }

    int ID = stoi(fields[0]);
    string name = fields[1];
    string details = fields[2];
    bool isDone = stoi(fields[3]);

    return Todo::createTodo(name, details, ID, isDone);
}


void load(fstream* file)
{
    string line;
    while(std::getline(*file,line))
    {
        AllTodos.push_back(parseAndReturnTodo(line));
    }
}

void viewTODOS(void)
{
    for(const auto& x : AllTodos)
    {
        if(x.ID == -1) continue;

        string c = x.isDone ? "✔" : "X";

        std::cout << x.ID << "-"<< x.name << "-" << x.details << "- Done: "<< c << std::endl;
    }
}

void insertTodo(Todo td, ofstream* file)
{
    int x = td.isDone ? 1 : 0;
    *file << "\n" << td.ID << "$" << td.name << "$" << td.details << "$" << x << std::endl;
}

int markTodoAsDoneAndRewriteTODOS(int todoID, ofstream* file)
{
    bool found = false;
    for(auto& t: AllTodos)
    {
        if(t.ID == todoID)
        {
            t.isDone = true;
            found = true;
        }
    }

    if(!found)
        return -1;


    for(const auto& t : AllTodos)
    {
        if (t.ID == -1) continue;
        int x = t.isDone ? 1 : 0;
        *file << "\n" << t.ID << "$" << t.name << "$" << t.details << "$" << x << std::endl;
    }

    return 1;
}

int main(int argc, char** argv)
{
    
    fstream todoFile("./todos/todos", ios::in | ios::out | ios::app);
    ofstream appendfile("./todos/todos", ios::app);
    ofstream truncfile;


    if(!todoFile || !todoFile.is_open())
    {
        std::cout << "File couldn't be opened!" << std::endl;
        return 1;
    }

    load(&todoFile);

    int lastID = AllTodos.size() ? AllTodos.back().ID : -1;
    char option;
    string name;
    string details;
    Todo td;
    int todoID;
    int stat;
    int deleter;
    bool exists;

    std::cout << "Welcome! Please pick an action:" << std::endl;
    std::cout << "1-View TODOs\n2-Add TODO\n3-Mark a TODO as done\n4-Delete a TODO" << std::endl;
    
    option_select:
    std::cout << "Option: ";
    std::cin  >> option;
    
    switch (option)
    {
    case '1':
        viewTODOS();
        goto option_select;
        break;
        
    case '2':
        std::cin.ignore();
        std::cout << "Provide the name of the TODO: ";
        getline(std::cin, name);
        std::cout << "Provide the details for the TODO: ";
        getline(std::cin, details);

        td = Todo::createTodo(name,details,lastID);
        insertTodo(td, &appendfile);
        AllTodos.push_back(td);
        lastID++;
        goto option_select;
        break;

    case '3':
        viewTODOS();
        std::cout << "Select the TODO ID to modify" << std::endl;
        std::cin >> todoID;
        truncfile = ofstream("./todos/todos", ios::trunc);
        stat = markTodoAsDoneAndRewriteTODOS(todoID, &truncfile);
        
        if(stat == -1)
        {
            std::cout << "No TODO with the ID found!" << std::endl;
        }
        goto option_select;
        break;
    
    case '4':
        viewTODOS();
        std::cout << "Select a TODO to delete" << std::endl;
        std::cin >> deleter;
        exists = false;
        for(auto& f : AllTodos)
        {
            if(deleter == f.ID)
            {
                f.ID = -1;
                exists = true;
                goto option_select;
            }
        }
        if(!exists)
        {
            std::cout << "TODO doesn't exist!" << std::endl;
            goto option_select;
        }
        
        break;

    default:
        std::cout << "Undefined choice, use 1,2,3 or 4!\n";
        return 1;
        break;

    }
    
    todoFile.close();
    appendfile.close();
    return 0;
}