#include <iostream>
using namespace std;

int sizeList();
// Declare linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
};
Node* head;
Node* tail;

// Utility function to add an element at the head (push)
void push(int data) {
  Node* temp = new Node();
  if (!temp) {
      cout << "\ncannot be allocated";
      exit(1);
  }
  temp->data = data;
  temp->next = head;
  temp->prev = NULL;
  if(head == NULL){
    tail = temp;
  }else{
    head->prev = temp;
  }
  head = temp;
}

// Utility function to check if the stack (list) is empty
int isEmpty() {
    return head == NULL;
}

// Utility function to return the head element
int peek() {
    if (!isEmpty())
        return head->data;
    else
        exit(1);
}
int show(){
  if(!isEmpty()){
    return tail->data;
  }
  else
    exit(1);
}

// Utility function to pop the head element
int pop() {
    if (head == NULL) {
        cout << "\nStack Underflow" << endl;
        exit(1);
    } 
    Node* temp;
    int x;
    temp = head;
    head = head->next;
    x = temp->data;
    if (head != NULL) {
      head->prev = NULL;
    } else {
      tail = NULL;
    }
    delete temp;
    return x;
}

// Function to print the list (stack)
void printList() {
    Node* temp;
    if (head == NULL) {
        cout << "\nStack Underflow";
        exit(1);
    } else {
        temp = head;
        cout << "NULL<=>";
        while (temp != NULL) {
            cout << temp->data << "<=>";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

void printList(struct Node* pointer) {
    if (pointer == NULL) {
        cout << "\nStack Underflow" << endl;
        return;
    }

    if (pointer == head) {
        cout << "NULL<=>";
        while (pointer != NULL) {
            cout << pointer->data << "<=>";
            pointer = pointer->next;
        }
        cout << "NULL" << endl;
    } else if (pointer == tail) {
        cout << "NULL<=>";
        while (pointer != NULL) {
            cout << pointer->data << "<=>";
            pointer = pointer->prev;
        }
        cout << "NULL" << endl;
    } else {
        cout << "\nPointer is neither head nor tail" << endl;
    }
}

// Function to get the element at a specific position
int get(int position) {
  int size = sizeList()-1;
  if(position < 0 || position > size){
    cout << "\nPosition out of range!" << endl;
    return -1;
  }
  Node* temp;    
  if(position <= size/2){
      temp = head;
      for(int i = 0; i < position; i++){
        temp = temp->next;
      }
    }
    else{
      temp = tail;
      for(int i = size; i > position; i--){
        temp = temp->prev;
      }
    }
    return temp->data;
}

// Function to remove an element from a specific position
void removeElement(int position) {
    if (head == NULL) {
        cout << "\nStack Underflow";
        return;
    }
    int size = sizeList()-1;
    if(position < 0 || position > size){
      cout << "\nPosition out of range! oops" << endl;
      exit(1);
    }
    Node* temp;
    if (position == 0) {
        temp = head;
        head = head->next;
        if(head == NULL)
          tail = NULL;
        head->prev = NULL;
        delete temp;
        return;
    }
    else if(position == size){
      temp = tail;
      tail = temp->prev;
      tail->next = NULL;
      delete temp;
      return;
    }
    if(position <= size/2){
      temp = head;
      for (int i = 0; temp != NULL && i < position ; i++) {
          temp = temp->next;
      }
    } else{
      temp = tail;
      for (int i = size; temp != NULL && i >= position ; i--){
        temp = temp->prev;
      }
    }
    temp->next->prev = temp->prev;
    temp->prev->next= temp->next;
    delete temp;
}

// Function to insert an element at the end
void insertLast(int newElement) {
    Node* temp = new Node();
    temp->data = newElement;
    temp->prev = tail;
    temp->next = NULL;

    if (tail == NULL) {
        head = temp;
    }else{
        tail->next = temp;
    }
    tail = temp;
}

// Function to return the size of the list
int sizeList() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void reverseList(){
  Node* temp = head;
  Node* temp2 = tail;
  int size = sizeList();
  for(int i = 0; i < size/2; i++){
    int temp3 = temp->data;
    temp->data = temp2->data;
    temp2->data = temp3;
    temp = temp->next;
    temp2 = temp2->prev;
  }
}

int main() {
  // Push the elements to stack (list)
  push(11);
  push(22);
  push(33);
  push(44);

  // Display stack elements
  printList();
  cout << "Element at position 0: " << get(0) << endl;
  cout << "Element at position 1: " << get(1) << endl;
  cout << "Element at position 2: " << get(2) << endl;
  cout << "Element at position 3: " << get(3) << endl;

  // Print top element
  cout << "Top element is " << peek() << endl;

  // Delete top elements of stack
  pop();
  pop();

  // Display stack elements
  printList();

  // Print top element
  cout << "Top element is " << peek() << endl;

  // Get element at position 1
  cout << "Element at position 0: " << get(0) << endl;
  cout << "Element at position 1: " << get(1) << endl;

  // Remove element at position 0
  removeElement(0);
  printList();

  // Insert element at the end
  insertLast(55);
  insertLast(77);
  printList();

  // Print the size of the list
  cout << "Size of the list: " << sizeList() << endl;

  cout << "Reversing list: " << endl;
  reverseList();
  printList();

  cout << "Printing from tail: " << endl;
  printList(tail);
  cout << "Printing from head: " << endl;
  printList(head);

  return 0;
}
