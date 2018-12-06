// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>

// Create your node_t type here


// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.




typedef struct node {

    unsigned int myData;
    struct node* next;

}node_t;


node_t* create_list(int data, node_t* n) {

    node_t* myList = malloc(sizeof(node_t));

    myList->myData = data;

    myList->next = n;

    return myList;
}

void printList(node_t* n) {

    //if(n->myData == NULL) {  printf("That's All!"); }
    //if (n->next = NULL) {  printf("That's All!"); }

    node_t* currentNode = n;


    while (currentNode != NULL) {

        if(currentNode->myData <= 75) {

            printf("%d wins ---- This was a BAD year!\n", currentNode->myData);



        }

    else if(75 < currentNode->myData <= 90) {
            printf("%d wins ---- We did OK this year!\n", currentNode->myData);

        }

         else if (n->myData > 90) {
            printf("%d wins ---- This was a good year!\n", currentNode->myData);


        } else {

             printf("End of this year!");
         }

        currentNode = currentNode->next;



    }




}

void free_list(node_t* n) {

    while (n != NULL) {
        free(n);
        n = n->next;

    }


}




int main(){


    FILE *filePointer;

    filePointer = fopen("data.txt","r");

    // to hold data while reading

    int buffer;




    //node_t* head = (node_t*)malloc(sizeof(node_t));
    //node_t* currentNode = head;
    node_t* currentNode = (node_t*)malloc(sizeof(node_t));
    node_t* head = NULL;




while(fscanf(filePointer,"%d",&buffer) == 1) {




if(head == NULL)  {



    currentNode->myData  = buffer;
    currentNode->next = NULL;
    head = currentNode;






} else {


    node_t* newNode = create_list(buffer, NULL);
    currentNode->next = newNode;
    currentNode = currentNode->next;



}


    }

printList(head);

free_list(head);
    return 0;
}
