//
// Created by nicola on 12/3/24.
//

#include "utils.h"


struct Timer
{
    time_point<steady_clock> start_ = steady_clock::now();
    time_point<steady_clock> stop_ = steady_clock::now();
    string task_name_;

public:
    explicit Timer(string task_name) : task_name_(task_name) {}

    void start()
    {
        start_ = steady_clock::now();
    }
    void start(string task_name)
    {
        task_name_ = task_name;
        start_ = steady_clock::now();
    }
    void stop()
    {
        stop_ = steady_clock::now();
        duration<double> elapsed_ms = stop_ - start_;
        cout << "Elapsed time for " << task_name_ << ": " << (elapsed_ms.count()) << " sec" << endl;
    }

    void stop_flops(float flops)
    {
        stop_ = steady_clock::now();
        duration<double> elapsed_ms = stop_ - start_;
        cout << "Elapsed time for " << task_name_ << ": " << (elapsed_ms.count()) << " sec" << "    " << flops / elapsed_ms.count() << " GFLOPS" << endl;
    }
};
