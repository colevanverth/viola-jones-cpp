#include "wlearner.h"

template <typename F, typename R>

class Pool {

public:

    Pool() {
        for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
            std::thread t(this->m_thread);
            this->m_threads.push_back(t);
        }
    }

    ~Pool() {
        this->m_stop = true;
        this->m_cv.notify_all();        
        for (auto& t : this->m_threads) { 
            t.join();
        }
    }

    void queue(F function) {
        std::lock_guard<std::mutex> fLock(this->m_fMutex); 
        this->m_functions.push_back(function);
        this->m_cv.notify_one();
    }

    std::vector<R>& getReturnVals() {
        std::lock_guard<std::mutex> rLock(this->m_rMutex);
        return this->m_returnVals;
    }

private:

    void m_thread() {
        while (true) {
            std::unique_lock fLock(this->m_fMutex);
            this->m_cv.wait(fLock, [this] () { return this->m_functions.size() > 0 || this->m_stop; });
            if (this->m_stop) { return; }
            F function = this->m_functions.back();
            this->m_functions.pop_back();
            fLock.unlock();
            R returnVal = function();
            std::lock_guard<std::mutex> rLock(this->m_rMutex);
            this->m_returnVals.push_back(returnVal); 
        }
    }

    bool m_stop = false;

    std::vector<F> m_functions;

    std::vector<R> m_returnVals;

    std::vector<std::thread> m_threads;

    std::mutex m_fMutex;

    std::mutex m_rMutex;

    std::condition_variable m_cv;

};
