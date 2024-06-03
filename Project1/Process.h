// 2-3. Process
// 이 파일은 Process 클래스의 선언을 포함하고 있습니다. Process 클래스는 각 프로세스를 나타내며, 
// ID, 타입 및 남은 시간을 관리합니다.

#pragma once
#include <string>

class Process {
public:
    Process(int id, const std::string& type, int remainingTime); // 생성자: ID, 타입, 남은 시간 초기화
    void update(); // 프로세스 업데이트 함수: 남은 시간을 감소시킴
    bool isReady() const; // 프로세스가 준비되었는지 확인하는 함수

private:
    int id; // 프로세스 ID
    std::string type; // 프로세스 타입
    int remainingTime; // 남은 시간
};
