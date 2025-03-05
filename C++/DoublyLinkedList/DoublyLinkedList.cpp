#include <iostream>

struct Node {
    int val;
    Node* prev;
    Node* next;

    Node(int val) : val(val) , prev(nullptr) , next(nullptr) {};

};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr) , tail(nullptr) {};
    
    void insertAtHead(int val){
        Node* newNode = new Node(val);

        if (!head){
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtTail(int val){
        Node* newNode = new Node(val);
        if (!tail){
            tail = head = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteAtHead(){
        if (!head) return;
        Node* temp = head;
        if (head == tail){
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr; 
        }
        delete temp;
    }
}
