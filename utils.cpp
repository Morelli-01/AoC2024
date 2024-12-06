//
// Created by nicola on 12/3/24.
//

#include "utils.h"

Timer::Timer(string task_name) : task_name_(task_name) {}

void Timer::start() {
    start_ = steady_clock::now();
}

void Timer::start(string task_name) {
    task_name_ = task_name;
    start_ = steady_clock::now();
}

void Timer::stop() {
    stop_ = steady_clock::now();
    duration<double> elapsed_ms = stop_ - start_;
    cout << "Elapsed time for " << task_name_ << ": " << (elapsed_ms.count()) << " sec" << endl;
}

void Timer::stop_flops(float flops) {
    stop_ = steady_clock::now();
    duration<double> elapsed_ms = stop_ - start_;
    cout << "Elapsed time for " << task_name_ << ": " << (elapsed_ms.count()) << " sec" << "    "
         << flops / elapsed_ms.count() << " GFLOPS" << endl;
}


