// 2-1. Dynamic Queueing
// 이 파일은 Dynamic Queue의 선언을 포함하고 있습니다. Dynamic Queue는 Node들의 연결 리스트로 구성되며, 
// 각 Node는 프로세스 리스트를 가집니다.

#pragma once
#include <list>
#include <string>
#include <mutex>

// Node 구조체 정의: 각 Node는 프로세스 리스트와 다음 Node를 가리키는 포인터를 가짐
struct Node {
    std::list<std::string> processes;
    Node* next;
    Node() : next(nullptr) {}
};

// DynamicQueue 클래스 정의
class DynamicQueue {
public:
    DynamicQueue(); // 생성자
    ~DynamicQueue(); // 소멸자
    void push(Node* node); // Node를 큐에 삽입
    Node* pop(); // 큐에서 Node를 제거
    void printStatus(); // 큐의 상태 출력

private:
    Node* top; // 큐의 최상단 Node
    std::mutex mtx; // 상호 배제 뮤텍스
};
