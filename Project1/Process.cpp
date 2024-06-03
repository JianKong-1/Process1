// 2-3. Process
// 이 파일은 Process 클래스의 구현을 포함하고 있습니다. 생성자, 업데이트 함수 및 준비 상태 확인 함수를 구현합니다.

#include "Process.h"

Process::Process(int id, const std::string& type, int remainingTime)
    : id(id), type(type), remainingTime(remainingTime) {}

void Process::update() {
    if (remainingTime > 0) --remainingTime; // 남은 시간을 감소시킴
}

bool Process::isReady() const {
    return remainingTime <= 0; // 남은 시간이 0 이하이면 준비 상태로 간주
}
