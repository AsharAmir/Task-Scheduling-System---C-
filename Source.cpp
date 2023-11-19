//22i-2420 ASHAR AMIR SE-B ASSIGNMENT 2 (DS)


#include <iostream>
using namespace std;
#include "Header.h"
#include <cstdlib>  

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


int main()
{
    //initialisers  
    skillStruct* skills = nullptr;
    resourcesStruct* resources = nullptr;
    projectStruct* project = new projectStruct;
    project->id = 1;
    project->duration = 0;
    project->tasks = nullptr;

    //menu helpers
    int choice;
    int taskIdIncrement = 0;   
    int resourceIdIncrement = 1; 
    int numResources = 0;        

    do
    {
        system(CLEAR_SCREEN);
        cout << "+----+----------------------------------------------+\n";
        cout << "|              Task Scheduling System               |\n";
        cout << "+----+----------------------------------------------+\n";
        cout << "| 1  | Add Skill                                    |\n";
        cout << "| 2  | Add Resource                                 |\n";
        cout << "| 3  | Add Task                                     |\n";
        cout << "| 4  | Calculate Schedule                           |\n";
        cout << "| 5  | Print Critical Tasks                         |\n";
        cout << "| 6  | Completion Time With Resources               |\n";
        cout << "| 7  | Completion Time With Resource Proficiency    |\n";
        cout << "| 8  | Set Task Duration                            |\n";
        cout << "| 9  | Set Nth Task Duration                        |\n";
        cout << "| 10 | Print Task Dependency List                   |\n";
        cout << "| 11 | Exit                                         |\n";
        cout << "+----+----------------------------------------------+\n";
        cout << "Enter your choice (1-11): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int skillId, proficiency;
            cout << "Enter Skill ID and its Proficiency level (0/1): ";
            cin >> skillId >> proficiency;
            addSkill(skills, skillId, proficiency);
            cout << "Skill added successfully!" << endl;
            break;
        }
        case 2:
        {
            int numResourceEntries;
            cout << "Enter the number of resources to add: ";
            cin >> numResourceEntries;

            for (int i = 0; i < numResourceEntries; ++i)
            {
                int skillId;
                bool available;

                cout << "Enter Skill ID and Availability (1 for available & 0 for unavailable): ";
                cin >> skillId >> available;

                addResources(resources, resourceIdIncrement, available, skills);
                resourceIdIncrement++;
                numResources++;
            }
            cout << "Resources added successfully!" << endl;
            break;
        }
        case 3:
        {
            int numTasks;
            cout << "Enter the number of tasks to add: ";
            cin >> numTasks;

            for (int i = 0; i < numTasks; ++i)
            {
                int duration, skillId, dependencyId, resourceId;
                taskStruct* dependency = nullptr;

                do
                {
                    cout << "Enter Duration, Skill ID, Dependency ID (or -1 if no dependency), and Resource ID: ";
                    cin >> duration >> skillId >> dependencyId >> resourceId;

                    if (dependencyId != -1)
                    {
                        dependency = getTask(project->tasks, dependencyId);
                        if (dependency == nullptr)
                        {
                            cout << "Task with the specified dependency not found.\n";
                        }
                    }
                } while (dependency == nullptr && dependencyId != -1);

                resourcesStruct* selectedResource = nullptr;
                int attempts = 3; //before going back to the menu.

                while (attempts > 0)
                {
                    selectedResource = getResource(resources, resourceId);

                    if (selectedResource == nullptr)
                    {
                        cout << "Resource with the specified ID not found. Please try again.\n";
                        cout << "Enter a valid Resource ID: ";
                        cin >> resourceId;
                        attempts--;
                    }
                    else
                    {
                        break; 
                    }
                }

                if (selectedResource == nullptr)
                {
                    cerr << "Task addition canceled." << endl;
                    continue;
                }

                try
                {
                    if (addTasks(project, taskIdIncrement, duration, skillId, dependency, selectedResource))
                    {
                        taskIdIncrement++; // Increment the task ID
                        cout << "Task added successfully!" << endl;
                    }
                }
                catch (const exception& e) //try catch block
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }
            break;
        }
        case 4:
            calculateBasicSchedule(project);
            cout << "Schedule calculated successfully!" << endl;
            break;
        case 5:
            printCriticalTasks(project);
            break;
        case 6:
            completionTimeWithResources(project);
            cout << "Completion time with resources calculated successfully!" << endl;
            break;
        case 7:
            completionTimeWithResourceProficiency(project);
            cout << "Completion time with resource proficiency calculated successfully!" << endl;
            break;
        case 8:
        {
            int newDuration;
            cout << "Enter the new Duration for all tasks: ";
            cin >> newDuration;
            setTaskDuration(project->tasks, newDuration);
            cout << "Duration set successfully for all tasks!" << endl;
            break;
        }
        case 9:
        {
            int taskID, newDuration;
            cout << "Enter the Task ID and its new duration: ";
            cin >> taskID >> newDuration;
            if (set_nth_task_duration(project->tasks, taskID, newDuration))
            {
                cout << "Task duration set successfully!" << endl;
            }
            else
            {
                cerr << "Invalid task ID, Task not found." << endl;
            }
            break;
        }
        case 10:
        {
            int taskID;
            cout << "Enter Task ID to print its dependency list: ";
            cin >> taskID;
            taskStruct* targetTask = getTask(project->tasks, taskID);
            if (targetTask != nullptr)
            {
                printTaskDependencyList(targetTask);
            }
            else
            {
                cerr << "Invalid task ID, Task not found." << endl;
            }
            break;
        }
        case 11:
            cout << "Terminating the program..\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 11);

    //delete project->tasks;
    delete project; //free up

    return 0;
}