/*
 ============================================================================
 Name        : project1.c
 Author      : Hossam Fudl
 Version     :
 Copyright   : Your copyright notice
 Description : Student Management System
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define eclipse_console {\
		setvbuf(stdout, NULL, _IONBF, 0);\
		setvbuf(stderr, NULL, _IONBF, 0);\
}

struct student
{
	int id; 		/*Student ID */
	char name[50]; 	/*Student Name */
	int age; 		/*Student Age */
	float gpa;		/*student GPA */
};
typedef struct student student;

/* structure to represent node in linked list */
struct Node
{
	student data;
	struct Node *next; 	/* structure node to point to the next node */
};
typedef struct Node Node;



Node *head = NULL; /* head to point to the first node */
int count_of_students = 0; // know number of students in list



/* fThis function collects new student details from the user and adds them to the student linked list. */
void add_student(student *data)
{
	/* allocate memory for new node */
	Node *link = (Node*)malloc(sizeof(Node));

	/*if the memory doesn't allocate*/
	if(link == NULL)
	{
		printf("can't find memory\n");
		return;
	}

	/*if there is no data*/
	if(data == NULL)
	{
		printf("data not found\n");
		return;
	}

	/* to check if the id is repeated */
	if(head != NULL)
	{
		Node *current = head;

		while(current != NULL)
		{
			if(current->data.id == data->id)
			{
				printf("This ID is already reserved\n");
				return;
			}
			current = current->next;
		}
	}

	/* insert data to the new node and next point to NULL*/
	link->data = *data;
	link->next = NULL;

	if (head == NULL)
	{
		head = link;
		count_of_students++;
		return;
	}

	/*loop go to last element in list */
	Node *current = head;
	while(current->next != NULL)
	{
		current = current->next;
	}

	/*last element point to the new last element*/
	current->next = link;
	count_of_students++;
}

/* This function displays the details of all students currently in the system. */
void displayStudents(void)
{
	/*check if the list is empty*/
	if (head == NULL)
	{
		printf("Empty list\n");
		return;
	}


	/*node to loop on the list point to head*/
	Node *current = head;

	/* loop to the end of list */
	while(current != NULL)
	{
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);
		current = current->next;
	}
}

/* This function searches for a student by their ID and displays their details if found. */
void search_student_by_id(int id)
{
	/* if the list empty print not found */
	if(head == NULL)
	{
		printf("List is Empty\n");
		return;
	}

	Node *current = head; //node to loop on the list start from head

	/*loop to the end of list */
	while(current != NULL)
	{
		if(current->data.id == id)
		{
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);
			return;
		}
		current = current->next;
	}

	/* student not found */
	printf("Student with ID %d not found\n", id);
}

/* This function updates the details of a student with the given ID. */
void update_student(int id)
{
	/*if list empty exit*/
	if(head == NULL)
	{
		printf("list is empty\n");
		return;
	}

	Node *current = head;
	while(current != NULL)
	{

		if(current->data.id == id)
		{
			/*update the student data */
			student data;
			data.id = id;
			printf("Enter Student Name: ");
			scanf("%s", data.name);
			printf("Enter Student Age: ");
			scanf("%d", &data.age);
			printf("Enter Student GPA: ");
			scanf("%f", &data.gpa);

			/* copy the data to node */
			current->data = data;
			printf("student details updated successfully.\n");
			return;
		}

		current = current->next;
	}
	/*student not found*/
	printf("Student with ID %d not found\n", id);
}

/* This function deletes a student from the linked list by their ID. */
void delete_studen(int id)
{
	/*if list is empty exit*/
	if(head == NULL)
	{
		printf("List is empty\n");
		return;
	}

	/*pointer to loop in list and the deleted node*/
	Node *current = head;
	Node *prev = NULL;

	/*if the head hold the id*/
	if(current->data.id == id)
	{
		head = head->next; // change head
		free(current); // free old head
		count_of_students--;
		printf("Student with ID %d Deleted successfully.\n", id);
		return;
	}

	prev = current;
	current = current->next;

	/* loop in the list */
	while(current != NULL)
	{
		if(current->data.id == id)
		{
			prev->next = current->next;
			free(current);
			count_of_students--;
			printf("Student with ID %d Deleted successfully.\n", id);
			return;
		}
		prev = current;
		current = current->next;
	}

	printf("Student with ID %d was not found.\n", id);
}

/* This function calculates and returns ethe average GPA of all students. */
float calculateAverageGPA(void)
{
	/*if list is empty exit*/
	if(head == NULL)
	{
		return 0;
	}

	/*pointer to loop on list*/
	Node *current = head;

	float average = 0.00;
	while(current != NULL)
	{
		average += current->data.gpa; // sum of all gpa
		current = current->next;
	}

	average = average / count_of_students;

	return average;
}

/* This function finds and displays the student with the highest GPA. */
void searchHighestGPA(void)
{
	/*if list is empty exit*/
	if(head == NULL)
	{
		printf("List is empty\n");
		return;
	}

	float highest_gpa = 0; //hold the highest gpa

	Node* current = head;

	//loop on all the list
	while(current != NULL)
	{
		if(highest_gpa < current->data.gpa)
		{
			highest_gpa = current->data.gpa;// getting the student with the biggest GPA
		}
		current = current->next;
	}

	current = head;
	/* to find all the data about the student*/
	while(current != NULL)
	{
		if(highest_gpa == current->data.gpa)
		{
			printf("Student with the highest GPA: \n");
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %.2f ]\n", current->data.id, current->data.name, current->data.age, current->data.gpa);
			return;
		}
		current = current->next;
	}

}

/*Function to free memory*/
void exit_function(void)
{
	/*the memory you used in the heap should be cleaned just before exiting the program*/
    Node *current = head;   // Start at the head of the list
    Node *next_node = NULL; // Pointer to store the next node

    // Traverse the list and delete each node
    while (current != NULL) {
        next_node = current->next; // Store the next node
        free(current);             // Free the current node
        current = next_node;       // Move to the next node
    }

    // Reset the head pointer and count of students
    head = NULL;
}



typedef void (*MenuFunction)(void);
/*  Wrapper functions to handle menu operations */
void add_student_menu(void)
{
	student data;
	printf("Enter Student ID: ");
	scanf("%d", &data.id);
	printf("Enter Student Name: ");
	scanf("%s", data.name);
	printf("Enter Student Age: ");
	scanf("%d", &data.age);
	printf("Enter Student GPA: ");
	scanf("%f", &data.gpa);

	/* add new student */
	add_student(&data);
}

void display_student_menu(void)
{
	/* Display all Students */
	displayStudents();
}

void search_student_menu(void)
{
	/*search for student*/
	int ID;
	printf("Enter Student ID to search: ");
	scanf("%d", &ID);
	search_student_by_id(ID);
}

void update_studen_menu(void)
{
	/* find student by id and update his information */
	int ID;
	printf("Enter student ID to update: ");
	scanf("%d", &ID);
	update_student(ID);
}

void delete_student_menu(void)
{
	/* Delete student by his ID */
	int ID;
	printf("Enter student ID to delete: ");
	scanf("%d", &ID);
	delete_studen(ID);
}

void calculate_average_menu(void)
{
	/* Average of All Students GPA*/
	float average = calculateAverageGPA();
	printf("Average GPA: %.2f\n", average);
}

void searchHighestGPA_menu(void)
{
	/*highest GPA*/
	searchHighestGPA();
}

void exit_program(void)
{
	exit_function();
    printf("Exiting....\n");
    exit(0);
}

/* Array of function pointers to menu functions */
MenuFunction menu_functions[] = {
	add_student_menu,		//1
	display_student_menu,	//2
	search_student_menu,	//3
	update_studen_menu,		//4
	delete_student_menu,	//5
	calculate_average_menu,	//6
	searchHighestGPA_menu,	//7
	exit_program			//8
};



int main(void)
{
	eclipse_console;

	int choice;

	/* loop to show menu until the user decides to exit */
	for(;;)
	{
		printf("----------------------------------------\n");
		printf("1. Add student\n2. Display Students\n3. Search Student by ID\n");
		printf("4. Update Student Information\n5. Delete Student\n6. Calculate Average GPA\n");
		printf("7. Search for Student with Highest GPA\n8. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		printf("----------------------------------------\n");

		if(choice >= 1)
        {
            // Call the function corresponding to the user's choice
            (*menu_functions[choice - 1])();
        }
        else
        {
            printf("Invalid choice. Please select a valid option.\n");
        }

	}

}
