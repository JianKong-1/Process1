// 2-2. Alarm Clock
// 이 파일은 Monitor 스레드의 선언을 포함하고 있습니다. Monitor는 주기적으로 Dynamic Queue의 상태를 출력합니다.

#pragma once
#include "DynamicQueue.h"
#include <mutex>
#include <condition_variable>

// Monitor 클래스 정의
class Monitor {
public:
    Monitor(DynamicQueue& dq, std::mutex& m, std::condition_variable& cv, bool& stopFlag); // 생성자
    void run(); // 스레드 실행 함수

private:
    DynamicQueue& dynamicQueue; // 참조 변수
    std::mutex& mtx; // 상호 배제 뮤텍스 참조
    std::condition_variable& cv; // 조건 변수 참조
    bool& stopFlag; // 종료 플래그 참조
};
