// 2-1. Dynamic Queueing
// 이 파일은 Dynamic Queue의 구현을 포함하고 있습니다. Node의 삽입(push), 제거(pop), 
// 상태 출력(printStatus) 기능을 구현합니다.

#include "DynamicQueue.h"
#include <iostream>
#include <mutex>

// DynamicQueue 생성자: 초기화
DynamicQueue::DynamicQueue() : top(nullptr) {}

// DynamicQueue 소멸자: 모든 Node를 해제
DynamicQueue::~DynamicQueue() {
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

// Node를 큐에 삽입
void DynamicQueue::push(Node* node) {
    std::unique_lock<std::mutex> lock(mtx);
    node->next = top;
    top = node;
}

// 큐에서 Node를 제거
Node* DynamicQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    if (top == nullptr) return nullptr;
    Node* temp = top;
    top = top->next;
    return temp;
}

// 큐의 상태 출력
void DynamicQueue::printStatus() {
    std::unique_lock<std::mutex> lock(mtx);
    Node* current = top;
    std::cout << "Dynamic Queue: ";
    while (current) {
        std::cout << "[ ";
        for (const auto& process : current->processes) {
            std::cout << process << " ";
        }
        std::cout << "] ";
        current = current->next;
    }
    std::cout << std::endl;
}
