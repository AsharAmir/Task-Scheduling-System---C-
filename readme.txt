TASK SCHEDULING SYSTEM - readMe.txt

Purpose
This code is designed to manage a project's task schedule, skill & resource allocation, and calculate the essential metrics. It allows for an efficient management and analysis of a project's structure, tasks, resources and skills. The primary purpose of the project is to;

	- Task Scheduling 
		- Schedule tasks within a project, considering their dependencies and resource availabilities, and storing their information
	
	- Critical Path Analysis
		- Identify the critical tasks & a critical path within the project.

	- Project Completion Estimate
		- Calculate the project's completion time based on resource availability and proficiency.

Design
The code is structured around several key data structures:

	- skillStruct: Represents a skill with an ID and proficiency level.
	- resourcesStruct: Represents a resource with an ID, availability status, and associated skills.
	- taskStruct: Represents a task with an ID, duration, start time, dependencies, required skills, and other scheduling information.
	- projectStruct: Represents the entire project with an ID and a list of tasks.

The key functionality of the code includes:
	- addSkill: Adds a new skill to the skill structure.
	- addResources: Adds a new resource to the resource structure.
	- addTasks: Adds a new task to the project structure, considering dependencies and resource availability.
	- calculateBasicSchedule: Calculates and displays the project scheduling information such as early start, early finish, late start, and late finish times.
	- printCriticalTasks: Identifies and displays critical tasks in the project.
	- completionTimeWithResources: Calculates and displays project completion time, considering resource availability.
	- completionTimeWithResourceProficiency: Calculates and displays project completion time, considering the resource availability and proficiency levels.

Usage
The code usage can be vaguely described as follows:

	- Define the essential project data
	- Link the resources & skills to their respective tasks
	- Call the desired functions 

The menu operation is described as follows:

	- Initialise the data structure	
		- skillStruct* skills: Represents skills and their proficiency levels.
             - 'skillStruct* skills = nullptr;'
        - resourcesStruct* resources: Represents resources and their availability.
            - 'resourcesStruct* resources = nullptr;'
        - projectStruct* project: Represents the project, including its tasks and schedule information.
            - 'projectStruct* project = new projectStruct;'
        
    - Main Menu 
        - Add Skill (Option 1): Add a new skill by entering the Skill ID and its Proficiency level (0 or 1).

        - Add Resource (Option 2): Add one or more resources by specifying the number of resources to add and providing details such as Skill ID and availability (1 for available, 0 for unavailable).

        - Add Task (Option 3): Add tasks to the project by specifying the number of tasks to add. For each task, provide the following details:

            - Duration: Task duration in days.
            - Skill ID: The ID of the skill required for the task.
            - Dependency ID: The ID of any task that the current task depends on (or -1 if no dependency).
            - Resource ID: The ID of the resource assigned to the task.
            - Tasks are added to the project while considering dependencies and resource availability. Invalid resource or dependency IDs will be handled, and the user will be prompted to retry.

        - Calculate Schedule (Option 4): Calculate and display the project schedule, including early start, early finish, late start, late finish times, and task slack.

        - Print Critical Tasks (Option 5): Identify and print critical tasks in the project. These are tasks with zero slack, and any delay in their execution will result in a delay in the project's completion.

        - Completion Time With Resources (Option 6): Calculate and print the project completion time, considering resource availability. This option ensures tasks are scheduled based on resource availability.

        - Completion Time With Resource Proficiency (Option 7): Calculate and print the project completion time, considering both resource availability and proficiency levels of resources. This option provides a more detailed view of task scheduling.

        - Set Task Duration (Option 8): Set a new duration for all tasks in the project. This option is useful for modifying task durations across the entire project.

        - Set Nth Task Duration (Option 9): Set a new duration for a specific task identified by its Task ID. If the task ID is invalid, an error message is displayed.

        - Print Task Dependency List (Option 10): Enter a Task ID to print the dependency list of the specified task. This option helps visualize task dependencies.

        - Exit (Option 11): Exit the program.

    - Interaction with the menu 
        - The menu can be interacted with by inputting the desired value as per the instruction and pressing the ENTER key.

    - Exiting
        - The program may be terminated at all times by pressing the CTRL + C keys on your keyboard.


References:
    - https://www.tutorialspoint.com/management_concepts/critical_path_method.htm
    - https://www.projectmanager.com/guides/critical-path-method#:~:text=When%20done%20properly%2C%20critical%20path,project%20scheduling%20and%20resource%20allocation

Author:
	- Ashhar Amir (22i-2420, SE-B, NUCES)
	

