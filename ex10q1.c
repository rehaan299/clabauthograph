//author-rehaan sharma
//CMPUT 201 lab 10 d07 
//this program simulates a line up for autographs
//it takes in a file with commands and executes them
//the commands are N, C, F, L
//N is for non cmput 201 students
//C is for cmput 201 students
//F is for the first person in line to get an autograph
//L is for the last person in line to leave the line
#include "ex10q1.h"                    // include the header file for necessary declarations
#include <stdio.h>                     // include standard input/output functions
#include <stdlib.h>                    // include standard library functions for memory management
//first function to initialise the queue
//takes in a queue and an array size

void init_Queue(struct Queue *queue, int array_size) {
    queue->students = (struct Student*)malloc(sizeof(struct Student) * array_size);   // allocate memory for the array of students
    //based on basic malloc ssyntax from https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/
    queue->queue_size = 0;                // initialising our queue size to zero
    queue->array_size = array_size;       // setting the initial array size
}

// adds student to queue, skips line if cmput 201 student
void enqueue_queue(struct Queue *queue, struct Student student, char discipline, int threshold) {//takes in a queue, a student, a discipline and a threshold
    // double array when filled up
    if (queue->array_size <= queue->queue_size) {                // check if the array is filled up (queue size is greater than or equal to array size)
        queue->array_size = queue->array_size * 2;               // double the array size (double the capacity) 
        queue->students = (struct Student*)realloc(queue->students, sizeof(struct Student) * queue->array_size);  // reallocate memory for the expanded array
    }//this line of code is resizing the dynamic array (queue->students) to accommodate more elements. 
    //If the array is filled up, it's doubled in size to allow for more elements to be added.
    // The realloc function takes care of managing the memory and copying the existing elements to the new location.
    if (discipline == 'C') {                                     // if the student is a CMPUT 201 student
        int new_size = (queue->queue_size % 2 == 1) ? (queue->queue_size / 2) + 1 : (queue->queue_size / 2); 
        //https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c/ reference for conditional operator
         // calculate new size based on floor division
        if (new_size < threshold) {                              // check if the new size is less than the threshold
            // move students after skipped position down
            for (int i = new_size; i < queue->queue_size; ++i) {
                queue->students[i+1] = queue->students[i];      // shift students to make space for the new student
            }
            queue->queue_size++;                                 // increment the queue size
            queue->students[new_size++] = student;              // add the student to the queue
        }
    } else if (discipline == 'N') {                              // if our student is a non-CMPUT 201 student
        // if acceptable amount of people are in front in line
        if (queue->queue_size < threshold) {                    // checking if the queue size is less than the threshold
            queue->students[queue->queue_size++] = student;     // adding the student to the queue
        }
    }
}

// removes student from queue
void dequeue_our_queue(struct Queue *queue, char position) {
    if (!(queue->queue_size == 0)) {                           // check if the queue is not empty
        if (position == 'F') {                                  // if removing the first student
            for (int i=0; i < queue->queue_size - 1; ++i) {    // move students down
                queue->students[i] = queue->students[i + 1];    // shift students to fill the removed student's position
            }
            --queue->queue_size;                                // decrement the queue size
        } else if (position == 'L') {                           // if removing the last student
            --queue->queue_size;                                // decrement the queue size
        }
    }
}

// print student at the top of queue
void get_Autograph(struct Queue *queue) {//takes in a queue 
    if (queue->queue_size == 0) {//if the queue is empty
        printf("empty\n");                                     // if the queue is empty, print "empty"
    } else {
        printf("%d\n", queue->students[0].sid);               // print the student ID of the first student in the queue
    }
}
//OUR MAIN FUNCTION

int main() {
    // initialize queue with array_size 5 
    struct Queue queue;//structure for queue
    init_Queue(&queue, 5);                                      // initialize the queue with an array size of 5
    int threshold;//initialising variables
    int studentID;//initialising variables
    char action;//initialising variables

    // parse file  and execute commands 
    while (scanf(" %c %d %d", &action, &threshold, &studentID) != EOF) {//reads the file and takes in the action, threshold and student ID  
        struct Student student = {studentID};                  // create a student struct with the given student ID

        if (action == 'F') {                                   // if the action is to finish autograph for the first person
            get_Autograph(&queue);                              // print the autograph for the first person
            dequeue_our_queue(&queue, 'F');                              // remove the first person from the queue
        } else if (action == 'L') {                            // if the action is to leave the line for the last person
            dequeue_our_queue(&queue, 'L');                              // remove the last person from the queue
        } else if (action == 'N' || action == 'C') {          // if the action is for a student to join the line
            enqueue_queue(&queue, student, action, threshold);      // add the student to the queue based on their discipline and threshold
        }
    }
    free(queue.students);                                      // free the allocated memory for the array of students
    return 0;//indiciating successful execution and freeing so we pass valgrind

}


//took help from the all sources listed and some from chatgpt for undertanding the question and the code and logic