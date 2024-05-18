//our header file
//author-rehaan sharma
//cmput 201 lab 10 d07

//header file for lab 10
#ifndef LAB10_H
#define LAB10_H

// student struct
struct Student{
    int sid;    // student ID
};

// queue struct
struct Queue{
    struct Student *students; // array of students
    int queue_size; // current number of students in the queue
    int array_size; // capacity of the array
};

// my function prototypes

void init_Queue(struct Queue *queue, int array_size);        // initialize the queue
void enqueue_queue(struct Queue *queue, struct Student student, char discipline, int threshold);  // add a student to the queue
void dequeue_our_queue(struct Queue *queue, char position);           // remove a student from the queue
void get_Autograph(struct Queue *queue);                    // get autograph for the first student in the queue

#endif
