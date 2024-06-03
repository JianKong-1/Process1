// 2-3. CLI
// 이 파일은 Shell 스레드의 선언을 포함하고 있습니다. Shell은 commands.txt 파일에서 명령을 읽고 실행합니다.

#pragma once
#include "DynamicQueue.h"
#include <mutex>
#include <condition_variable>

// Shell 클래스 정의
class Shell {
public:
    Shell(DynamicQueue& dq, std::mutex& m, std::condition_variable& cv, bool& stopFlag); // 생성자
    void run(); // 스레드 실행 함수

private:
    void executeCommand(const std::string& command, int processId); // 명령 실행 함수
    DynamicQueue& dynamicQueue; // 참조 변수
    std::mutex& mtx; // 상호 배제 뮤텍스 참조
    std::condition_variable& cv; // 조건 변수 참조
    bool& stopFlag; // 종료 플래그 참조
};
