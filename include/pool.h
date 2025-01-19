#pragma once

#include "common.h"

template <typename R>

class Pool {

public:
  Pool() {
    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
      this->m_threads.emplace_back([this] { this->m_thread(); });
    }
  }

  ~Pool() {
    this->m_running = false;
    this->m_fCondition.notify_all();

    for (auto &t : this->m_threads) {
      t.join();
    }
  }

  void queue(std::function<R()> function) {
    std::unique_lock fLock(this->m_fMutex);
    std::lock_guard<std::mutex> pLock(this->m_pMutex);
    this->m_pCounter++;
    this->m_functions.push_back(function);
    fLock.unlock();
    this->m_fCondition.notify_one();
  }

  std::vector<R> &getReturnVals() {
    std::unique_lock pLock(this->m_pMutex);
    this->m_pCondition.wait(pLock, [this] { return this->m_pCounter == 0; });
    pLock.unlock();
    return this->m_returnVals;
  }

private:
  void m_thread() {
    while (true) {
      std::unique_lock fLock(this->m_fMutex);
      this->m_fCondition.wait(fLock, [this] {
        return !this->m_functions.empty() || !this->m_running;
      });
      if (!this->m_running) {
        return;
      }
      auto function = this->m_functions.back();
      this->m_functions.pop_back();
      fLock.unlock();
      R returnVal = function();

      std::lock_guard<std::mutex> rLock(this->m_rMutex);
      this->m_returnVals.push_back(returnVal);
      std::unique_lock pLock(this->m_pMutex);
      this->m_pCounter--;
      pLock.unlock();
      std::cout << "Processed wavelets: " << this->m_returnVals.size() << "\r";
      std::cout.flush();
      this->m_pCondition.notify_one();
    }
  }

  std::vector<std::function<R()>> m_functions;

  std::vector<R> m_returnVals;

  std::vector<std::thread> m_threads;

  std::condition_variable m_fCondition;

  std::condition_variable m_pCondition;

  int m_pCounter = 0;

  std::atomic<bool> m_running = true;

  std::mutex m_pMutex;

  std::mutex m_fMutex;

  std::mutex m_rMutex;
};
