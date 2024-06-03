// 2-2. Alarm Clock
// 이 파일은 Monitor 스레드의 구현을 포함하고 있습니다. Monitor는 주기적으로 Dynamic Queue의 상태를 출력합니다.

#include "Monitor.h"
#include <iostream>
#include <chrono>

// Monitor 생성자: 초기화
Monitor::Monitor(DynamicQueue& dq, std::mutex& m, std::condition_variable& cv, bool& stopFlag)
    : dynamicQueue(dq), mtx(m), cv(cv), stopFlag(stopFlag) {}

// Monitor 스레드 실행 함수
void Monitor::run() {
    while (!stopFlag) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초마다 대기
        dynamicQueue.printStatus(); // 큐의 상태 출력
    }
}
