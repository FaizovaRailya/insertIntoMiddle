#pragma once
#include <mutex> 

struct Node{
    int value;
    Node* next;
    std::mutex* node_mutex;
};

class FineGrainedQueue {
    Node* head;
    std::mutex* queue_mutex;

public:
    FineGrainedQueue();
    ~FineGrainedQueue();
    void insertIntoMiddle(int value, int pos);
    void pushback(int value);
    void print();
};