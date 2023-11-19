//22i-2420 ASHAR AMIR SE-B ASSIGNMENT 2 (DS)
#pragma once
using namespace std;
#include <iostream>

// struct definition
struct skillStruct;
struct resourcesStruct;

struct resourcesStruct
{
    int id;
    bool isAvailable;
    skillStruct* skills;
    resourcesStruct* next;
};

struct taskStruct
{
    int id;
    int duration;
    int startTime;
    taskStruct* next;
    int skillID;
    taskStruct* dependencies;
    resourcesStruct* resources;
    int earlyStart;
    int earlyFinish;
    int lateStart;
    int lateFinish;
    //int slack; //trying
};

struct projectStruct
{
    int id;
    int duration;
    taskStruct* tasks;
};

struct skillStruct
{
    int id;
    int proficencyLevel;
    skillStruct* next;
};

void addSkill(skillStruct*& head, int id, int proficiencyLevel)
{
    // Create a new skill structure
    skillStruct* newSkill = new skillStruct;
    newSkill->id = id;
    newSkill->proficencyLevel = proficiencyLevel;
    newSkill->next = nullptr;

    if (head == nullptr)
    {
        head = newSkill;
        return;
    }
    skillStruct* current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newSkill;
}

resourcesStruct* getResource(resourcesStruct* resources, int resourceId)
{
    resourcesStruct* current = resources;
    while (current != nullptr)
    {
        if (current->id == resourceId)
        {
            // cout << "resource found!";
            return current;
        }
        current = current->next;
    }
    // cout << "resource not found!";
    return nullptr;
}

taskStruct* getTask(taskStruct*& tasks, int taskId)
{
    taskStruct* current = tasks;
    while (current != nullptr)
    {
        /*if (taskId == -1) return current;*/
        if (current->id == taskId)
        {
            // cout << "task found!" << endl;
            return current;
        }
        current = current->next;
    }
    // cout << "task not found!";
    return nullptr; // if task not found
}

void addResources(resourcesStruct*& head, int id, bool isAvailable, skillStruct* skills)
{
    resourcesStruct* newResources = new resourcesStruct;
    newResources->id = id;
    newResources->isAvailable = isAvailable;
    newResources->skills = skills;
    newResources->next = nullptr;

    // checks
    if (head == nullptr)
    {
        head = newResources;
        return;
    }

    resourcesStruct* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }

    curr->next = newResources;
}

bool addTasks(projectStruct*& head, int id, int duration, int skillID, taskStruct* dependencies, resourcesStruct* resources)
{
    // Check if the required resources are available
    resourcesStruct* currResource = resources;
    while (currResource != nullptr)
    {
        if (currResource->isAvailable == false)
        {
            cout << "Task cannot be scheduled because required resource isn't available" << endl;
            return false;
        }
        currResource = currResource->next;
    }

    taskStruct* newTask = new taskStruct;
    newTask->id = id;
    newTask->duration = duration;
    newTask->skillID = skillID;
    newTask->dependencies = dependencies;
    newTask->resources = nullptr; 
    newTask->next = nullptr;

    if (head->tasks == nullptr)
    {
        newTask->startTime = 0; 
    }
    else
    {
        int maxEndTime = -1;
        taskStruct* currDep = dependencies;
        while (currDep != nullptr)
        {
            if ((currDep->duration + currDep->startTime) > maxEndTime)
            {
                maxEndTime = currDep->duration + currDep->startTime;
            }
            currDep = currDep->next;
        }
        newTask->startTime = maxEndTime;
    }

    if (resources != nullptr)
    {
        if (newTask->resources == nullptr)
        {
            newTask->resources = resources;
        }
        else
        {
            //last resource
            resourcesStruct* lastResource = newTask->resources;
            while (lastResource->next != nullptr)
            {
                lastResource = lastResource->next;
            }

            // new resources to the end of the list
            lastResource->next = resources;
        }
    }

    // intiailsiing
    if (head->tasks == nullptr)
    {
        head->tasks = newTask;
    }
    else
    {
        taskStruct* curr = head->tasks;
        while (curr->next != nullptr)
        {
            curr = curr->next;
        }
        curr->next = newTask;
    }

    return true;
}


void setTaskDuration(taskStruct* targetTask, int newDur) // setter for ALL
{
    taskStruct* curr = targetTask;
    while (curr != nullptr)
    {
        curr->duration = newDur;
        curr = curr->next;
    }
}

bool set_nth_task_duration(taskStruct* targetTask, int taskID, int newDur) // setter 
{
    taskStruct* curr = targetTask;
    while (curr != nullptr)
    {
        if (curr->id == taskID)
        {
            curr->duration = newDur;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void printTaskDependencyList(taskStruct* targetTask) //print dependencies of a specific task
{
    taskStruct* curr = targetTask;
    while (curr != nullptr)
    {
        cout << "Task ID: " << curr->id << endl;
        cout << "Task Duration: " << curr->duration << endl;
        cout << "Task Start Time: " << curr->startTime << endl;
        cout << "Task Skill ID: " << curr->skillID << endl;
        cout << "Task Dependencies: " << endl;
        taskStruct* currDep = curr->dependencies;
        while (currDep != nullptr)
        {
            cout << "Dependency ID: " << currDep->id << endl;
            currDep = currDep->next;
        }
        curr = curr->next;
    }
}

void calculateBasicSchedule(projectStruct* project) //task scheduling
{
    int taskCount = 0;
    int projectDuration = 0;
    taskStruct* currentTask = project->tasks;
    while (currentTask != nullptr)
    {
        projectDuration += currentTask->duration;
        currentTask = currentTask->next;
    }

    currentTask = project->tasks;
    int projectStartTime = 0; //null

    int LF = projectDuration; //lf 0 to start

    // backwardpass()
    while (currentTask != nullptr)
    {
        // ls
        currentTask->lateStart = LF - currentTask->duration;
        currentTask->lateFinish = LF;

        // lf
        if (currentTask->next != nullptr)
        {
            LF = currentTask->lateStart;
        }

        currentTask = currentTask->next;
    }

    currentTask = project->tasks; // restartrign

    // forwardpasss
    while (currentTask != nullptr)
    {
        // es
        int maxEF = 0;
        taskStruct* currDep = currentTask->dependencies; //currentdependency to traverse
        while (currDep != nullptr)
        {
            if (currDep->earlyFinish > maxEF)
            {
                maxEF = currDep->earlyFinish;
            }
            currDep = currDep->next;
        }
        currentTask->earlyStart = maxEF;
        currentTask->earlyFinish = currentTask->earlyStart + currentTask->duration; //ef

        int slack = currentTask->lateStart - currentTask->earlyStart;
        //currentTask->slack = currentTask->lateStart - currentTask->earlyStart;
        cout << "Task ID: " << currentTask->id << endl;
        cout << "Task Duration: " << currentTask->duration << endl;
        cout << "Task Early Start: " << currentTask->earlyStart << endl;
        cout << "Task Early Finish: " << currentTask->earlyFinish << endl;
        cout << "Task Late Start: " << currentTask->lateStart << endl;
        cout << "Task Late Finish: " << currentTask->lateFinish << endl;
        cout << "Task Slack: " << abs(slack) << endl;

        cout << "Resource Dependent on for Task " << currentTask->id << "# ";
        if (currentTask->resources != nullptr) 
        {
            //outputting the resources for the task
            resourcesStruct* currResource = currentTask->resources;
            while (currResource != nullptr)
            {
                cout << currResource->id << " ";
                currResource = currResource->next;
            }
        }
        else
        {
            cout << "none!";
        }
        cout << endl << endl;

        if (slack == 0)
        {
            cout << "Task # " << taskCount << " is Critical!" << endl;
        }

        projectStartTime = currentTask->earlyFinish;
        taskCount++;

        currentTask = currentTask->next;
    }
    cout << "Project Completion Time: " << projectDuration << endl;
}

void printCriticalTasks(projectStruct* project)
{
    int taskCount = 0;
    taskStruct* currentTask = project->tasks;

    while (currentTask != nullptr)
    {
        int slack = currentTask->lateStart - currentTask->earlyStart;
        if (slack == 0)
        {
            cout << "Critical Task ID: " << currentTask->id << " & (Duration: " << currentTask->duration << " days)" << endl;
        }

        currentTask = currentTask->next;
    }
    cout << "No critical tasks exist!" << endl;
}


void completionTimeWithResources(projectStruct* project)
{
    int projectDuration = 0;

    // Backward pass
    int LF = projectDuration;
    taskStruct* currentTask = project->tasks;
    while (currentTask != nullptr)
    {
        currentTask->lateFinish = LF;
        currentTask->lateStart = LF - currentTask->duration;

        if (currentTask->next != nullptr)
        {
            LF = currentTask->lateStart;
        }

        currentTask = currentTask->next; //next task
    }

    if (false) {
        int slack, maxDependencyFinishTime;
        taskStruct* allocatedTask = nullptr;
        int lowestLateStart = INT_MAX, lowestSlack = INT_MAX, lowestDuration = INT_MAX;
        resourcesStruct* resource = currentTask->resources;
        while (resource != nullptr)
        {
            taskStruct* newTaskToAllocate = project->tasks;
            while (newTaskToAllocate != nullptr)
            {
                //IMPLEMENTING THE NECESSARY CHECKS FOR THE RESOURCE PRIORITISATION
                if (newTaskToAllocate->resources == resource)
                {
                    if (newTaskToAllocate->lateStart < lowestLateStart) //if the late start is less than the lowest late start
                    {
                        lowestLateStart = newTaskToAllocate->lateStart;
                        allocatedTask = newTaskToAllocate;
                    }
                    else if (newTaskToAllocate->lateStart == lowestLateStart) //OTHERWISE IF EQUAL
                    {
                        if (slack < lowestSlack) //if the slack is less than the lowest slack
                        {
                            lowestSlack = slack;
                            allocatedTask = newTaskToAllocate;
                        }
                        else if (slack == lowestSlack)
                        {
                            if (newTaskToAllocate->duration < lowestDuration) //if the duration is less than the lowest duration
                            {
                                lowestDuration = newTaskToAllocate->duration;
                                allocatedTask = newTaskToAllocate;
                            }
                        }


                    }
                }
                newTaskToAllocate = newTaskToAllocate->next;
            }

            if (allocatedTask != nullptr) //if the task is llocated
            {
                allocatedTask->startTime = maxDependencyFinishTime;
                allocatedTask->earlyStart = allocatedTask->startTime;
                allocatedTask->earlyFinish = allocatedTask->earlyStart + allocatedTask->duration;
                projectDuration = max(projectDuration, allocatedTask->earlyFinish);

            }

            resource = resource->next;
        }
    }

    // Forward pass
    currentTask = project->tasks;
    while (currentTask != nullptr)
    {
        int maxDependencyFinishTime = 0;
        taskStruct* currDep = currentTask->dependencies;
        while (currDep != nullptr)
        {
            //PRIORITISING THE TASKS
            if (currDep->earlyFinish > maxDependencyFinishTime){ //maxDependencyFinishTime = currDep->earlyFinish; }
                maxDependencyFinishTime = currDep->earlyFinish;
            }
            currDep = currDep->next;
        }

        bool resourcesAvailable = true;
        resourcesStruct* currResource = currentTask->resources;
        while (currResource != nullptr)
        {
            if (!currResource->isAvailable)
            {
                resourcesAvailable = false;
                break;
            }
            currResource = currResource->next;
        }

        if (resourcesAvailable) //if the resources are available
        {
            currentTask->startTime = maxDependencyFinishTime;
        }
        else
        {
            currentTask->startTime = maxDependencyFinishTime + 1;
        }

        currentTask->earlyStart = currentTask->startTime;
        currentTask->earlyFinish = currentTask->earlyStart + currentTask->duration;
        projectDuration = max(projectDuration, currentTask->earlyFinish); //project duration is the max of the project duration &  the current task early finish

        currentTask = currentTask->next;
    }

    // Print the updated project schedule
    cout << "Updated Project Schedule with Resource Availability:" << endl;
    currentTask = project->tasks;
    while (currentTask != nullptr)
    {
        cout << "Task ID: " << currentTask->id << endl;
        cout << "Task Duration: " << currentTask->duration << " days" << endl;
        cout << "Task Early Start: " << currentTask->earlyStart << endl;
        cout << "Task Early Finish: " << currentTask->earlyFinish << endl;
        cout << "Task Late Start: " << abs(currentTask->lateStart) << endl;
        cout << "Task Late Finish: " << abs(currentTask->lateFinish) << endl;
        cout << "Task Start Time: " << abs(currentTask->startTime) << endl;
        cout << "Resource availability: ";

        if (currentTask->resources != nullptr)
        {
            resourcesStruct* currResource = currentTask->resources;
            while (currResource != nullptr)
            {
                cout << currResource->isAvailable << " ";
                currResource = currResource->next;
            }
        }
        else
        {
            cout << "None";
        }
        cout << endl << endl;

        currentTask = currentTask->next;
    }

    cout << "Project completion time with resource availability: " << projectDuration << " days" << endl;
}

void completionTimeWithResourceProficiency(projectStruct* project)
{
    //declarations
    int projectDuration = 0;
    taskStruct* currentTask = project->tasks;
    int minProficiencyLevel = INT_MAX;
    while (currentTask != nullptr)
    {
        int maxDependencyFinishTime = 0;
        taskStruct* currDep = currentTask->dependencies;
        while (currDep != nullptr)
        {
            if (currDep->earlyFinish > maxDependencyFinishTime)
            {
                maxDependencyFinishTime = currDep->earlyFinish;
            }
            currDep = currDep->next;
            //    if (currDep->earlyFinish > maxDependencyFinishTime)
            //    {
            //        maxDependencyFinishTime = currDep->earlyFinish;
            //    }
            //currDep = currDep->next;
        }
        bool resourcesAvailable = true;
        resourcesStruct* currResource = currentTask->resources;

        while (currResource != nullptr)
        {
            if (!currResource->isAvailable)
            {
                resourcesAvailable = false;
                break;
            }

            skillStruct* currSkill = currResource->skills;
            while (currSkill != nullptr)
            {
                if (currSkill->proficencyLevel < minProficiencyLevel) //proficiency level prioritization
                {
                    minProficiencyLevel = currSkill->proficencyLevel;
                }
                currSkill = currSkill->next;
            }

            currResource = currResource->next;
        }

        if (resourcesAvailable)
        {
            currentTask->startTime = maxDependencyFinishTime;
        }
        else
        {

            currentTask->startTime = maxDependencyFinishTime + 1;
        }

        currentTask->earlyStart = currentTask->startTime;
        currentTask->earlyFinish = currentTask->earlyStart + currentTask->duration;
        projectDuration = max(projectDuration, currentTask->earlyFinish);

        currentTask = currentTask->next;
    }

    cout << "Updated project schedule:" << endl;
    currentTask = project->tasks;
    while (currentTask != nullptr)
    {
        cout << "Task ID: " << currentTask->id << endl;
        cout << "Task Duration: " << currentTask->duration << " days" << endl;
        cout << "Task Early Start: " << currentTask->earlyStart << endl;
        cout << "Task Early Finish: " << currentTask->earlyFinish << endl;
        cout << "Task Late Start: " << abs(currentTask->lateStart) << endl;
        cout << "Task Late Finish:" <<abs( currentTask->lateFinish) << endl;
        cout << "Task Start Time: " << abs(currentTask->startTime) << endl;
        cout << "Task resource availability & proficiency: ";

        if (currentTask->resources != nullptr)
        {
            resourcesStruct* currResource = currentTask->resources;
            while (currResource != nullptr)
            {
                cout << "Resource ID: " << currResource->id;
                cout << " Availability: " << currResource->isAvailable;
                cout << " Proficiency Level: " << minProficiencyLevel;
                currResource = currResource->next;
            }
        }
        else
        {
            cout << "None";
        }
        cout << endl << endl;

        currentTask = currentTask->next;
    }

    cout << "Total project completion time with all the delays (resources & proficiencies): " << projectDuration << " days" << endl;
}
