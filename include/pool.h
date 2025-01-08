#pragma once

#include "common.h"

template <typename R>

class Pool {

public:

    Pool() = default;

    void queue(std::function<R()> function) {
        this->m_functions.push_back(function);
    }

    std::vector<R>& getReturnVals() {
        for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
            this->m_threads.emplace_back([this] { this->m_thread(); });
        }
        for (auto& t : this->m_threads) { 
            t.join();
        }
        return this->m_returnVals;
    }

private:

    void m_thread() {
        m_fMutex.lock();
        while (m_functions.size() > 0) {
            auto function = this->m_functions.back();
            this->m_functions.pop_back();
            m_fMutex.unlock();
            R returnVal = function();
            std::lock_guard<std::mutex> rLock(this->m_rMutex);
            this->m_returnVals.push_back(returnVal); 
            m_fMutex.lock();
        }
        m_fMutex.unlock();
    }

    std::vector<std::function<R()>> m_functions;

    std::vector<R> m_returnVals;

    std::vector<std::thread> m_threads;

    std::mutex m_rMutex;

    std::mutex m_fMutex;

};
