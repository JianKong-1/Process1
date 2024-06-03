// 2-3. CLI
// 이 파일은 Shell 스레드의 구현을 포함하고 있습니다. Shell은 commands.txt 파일에서 명령을 읽고 실행합니다.

#include "Shell.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>

Shell::Shell(DynamicQueue& dq, std::mutex& m, std::condition_variable& cv, bool& stopFlag)
    : dynamicQueue(dq), mtx(m), cv(cv), stopFlag(stopFlag) {}

void Shell::run() {
    std::ifstream commandsFile("commands.txt");
    if (!commandsFile.is_open()) {
        std::cerr << "Failed to open commands.txt" << std::endl;
        return;
    }

    std::string line;
    int processId = 1;
    while (getline(commandsFile, line) && !stopFlag) {
        std::istringstream iss(line);
        std::string command;
        while (getline(iss, command, ';')) {
            executeCommand(command, processId++);
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
}

void Shell::executeCommand(const std::string& command, int processId) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Executing command: " << command << std::endl;

    // 명령어 파싱
    std::istringstream iss(command);
    std::string cmd;
    std::vector<std::string> args;
    while (iss >> cmd) {
        args.push_back(cmd);
    }

    Node* node = new Node();
    node->processes.push_back(command);
    dynamicQueue.push(node);

    // 명령어 처리
    if (args[0] == "echo") {
        std::cout << args[1] << std::endl;
    }
    else if (args[0] == "gcd") {
        if (args.size() >= 3) {
            int x = std::stoi(args[1]);
            int y = std::stoi(args[2]);
            while (y != 0) {
                int temp = y;
                y = x % y;
                x = temp;
            }
            std::cout << "gcd result: " << x << std::endl;
        }
    }
    else if (args[0] == "sum") {
        if (args.size() >= 2) {
            int x = std::stoi(args[1]);
            long long sum = 0;
            for (int i = 1; i <= x; ++i) {
                sum += i;
            }
            std::cout << "sum result: " << sum << std::endl;
        }
    }
    else if (args[0] == "dummy") {
        std::cout << "Created dummy process" << std::endl;
    }

    cv.notify_all();
}
