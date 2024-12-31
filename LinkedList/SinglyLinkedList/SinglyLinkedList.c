#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
  } Node;

Node* createNode(int data){
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("内存分配失败\n");
        exit(1);
      }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
  }

Node* insertAtHead(Node* head , int data){
    Node* newNode = createNode( data);
    newNode->data = data;
    newNode->next = head;
    return newNode;
  }

Node* insertAtTail(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) { // 如果链表为空
        return newNode;
    }
    Node* temp = head;
    while (temp->next != NULL) { // 遍历到链表末尾
        temp = temp->next;
    }
    temp->next = newNode; // 将新节点加入链表末尾
    return head;
}

Node* deleteNode(Node* head, int key) {
    if (head == NULL) return NULL; // 如果链表为空

    if (head->data == key) { // 如果头节点就是要删除的节点
        Node* temp = head;
        head = head->next; // 更新头节点
        free(temp);        // 释放内存
        return head;
    }

    Node* temp = head;
    while (temp->next != NULL && temp->next->data != key) { // 找到要删除的节点
        temp = temp->next;
    }

    if (temp->next != NULL) { // 如果找到了节点
        Node* toDelete = temp->next;
        temp->next = temp->next->next; // 删除节点
        free(toDelete);               // 释放内存
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp); // 释放节点内存
    }
}
int main() {
    Node* head = NULL; // 初始化空链表

    // 插入节点
    head = insertAtHead(head, 10);
    head = insertAtHead(head, 20);
    head = insertAtTail(head, 30);

    // 打印链表
    printf("链表内容: ");
    printList(head);

    // 删除节点
    head = deleteNode(head, 20);
    printf("删除 20 后的链表: ");
    printList(head);

    // 释放链表内存
    freeList(head);

    return 0;
}


