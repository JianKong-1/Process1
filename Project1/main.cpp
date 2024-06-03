// 2-1. ~ 2-3. Main program
// 이 파일은 전체 프로그램의 진입점입니다. Dynamic Queue, Monitor, Shell의 객체를 생성하고, 
// 각 스레드를 실행합니다. Shell 스레드가 끝난 후 Monitor 스레드를 종료합니다.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "DynamicQueue.h"
#include "Monitor.h"
#include "Shell.h"

using namespace std;

// 전역 변수 선언
mutex mtx; // 상호 배제 뮤텍스
condition_variable cv; // 조건 변수
bool stopFlag = false; // 프로그램 종료 플래그

int main() {
    // DynamicQueue, Monitor, Shell 객체 생성
    DynamicQueue dynamicQueue;
    Monitor monitor(dynamicQueue, mtx, cv, stopFlag);
    Shell shell(dynamicQueue, mtx, cv, stopFlag);

    // Monitor와 Shell 스레드 실행
    thread monitorThread(&Monitor::run, &monitor);
    thread shellThread(&Shell::run, &shell);

    // Shell 스레드가 종료될 때까지 대기
    shellThread.join();
    {
        lock_guard<mutex> lock(mtx);
        stopFlag = true; // 종료 플래그 설정
    }
    cv.notify_all(); // 조건 변수 알림
    monitorThread.join(); // Monitor 스레드 종료 대기

    return 0;
}
