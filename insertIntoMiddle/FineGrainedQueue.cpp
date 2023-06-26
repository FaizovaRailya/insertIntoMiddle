#include <iostream>
#include <string>
#include "FineGrainedQueue.h"
#include <mutex>

FineGrainedQueue::FineGrainedQueue() {
    head = nullptr;
    queue_mutex = new std::mutex();
}

FineGrainedQueue::~FineGrainedQueue() {
    delete queue_mutex;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos) {
    // ������ ����� ����
    Node* new_node = new Node();
    new_node->value = value;
    new_node->node_mutex = new std::mutex;

    // ��������� ������� �������
    queue_mutex->lock();

    // ��������� �� ��������� �� pos ����� ������
    int length = 0;
    Node* current = head;
    while (current != nullptr && length < pos) {
        current = current->next;
        length++;
    }
    if (pos > length) { pos = length; }

    // �������� �� ������ � �������, � ������� ����� �������� ����� ����
    current = head;
    Node* previous = nullptr;
    for (int i = 0; i < pos; i++) {
        previous = current;
        current = current->next;
    }

    // ��������� ����� ����
    if (previous == nullptr) {
        // ������� � ������
        new_node->next = head;
        head = new_node;
    }
    else {
        // ��������� � �������� ��� � �����
        previous->next = new_node;
        new_node->next = current;
    }

    // ������������ ������� �������
    queue_mutex->unlock();
}
    
void FineGrainedQueue::pushback(int value) {
    std::lock_guard<std::mutex> m(*queue_mutex);
    if (head == nullptr) {
        head = new Node;
        head->next = nullptr;
        head->value = value;
        head->node_mutex = new std::mutex;
        return;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        Node* newNode = new Node;
        newNode->next = nullptr;
        newNode->value = value;
        newNode->node_mutex = new std::mutex;
        current->next = newNode;
        return;
    }
}

void FineGrainedQueue::print() {   
    std::lock_guard<std::mutex> m(*queue_mutex);
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}