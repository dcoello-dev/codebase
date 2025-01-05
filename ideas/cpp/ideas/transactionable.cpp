// sandbox_idea: cpp/ideas
// sandbox_name: transactionable
// sandbox_description:
// sandbox_env: cpp

#include <iostream>
#include <mutex>

template <typename T> class ITransactionable {
  class Transaction {
  public:
    Transaction(std::unique_lock<std::mutex> &&lk, T &data)
        : lk_(std::move(lk)), data_(data) {}

    T &write() noexcept { return data_; }

    const T &read() const noexcept { return data_; }

  private:
    std::unique_lock<std::mutex> lk_;
    T &data_;
  };

public:
  Transaction transaction() noexcept {
    return Transaction(std::unique_lock<std::mutex>(mMutex), *static_cast<T *>(this));
  }

private:
  std::mutex mMutex{};
};

class Thing : public ITransactionable<Thing> {
public:
  void step1() {
    std::cout << "step 1" << std::endl;
  }
  void step2() {
    std::cout << "step 2" << std::endl;
  }
  void step3() { 
    std::cout << "step 3" << std::endl;
  }
};

int main(void) {
  Thing t{};
  {
    auto transaction = t.transaction();
    transaction.write().step1();
    transaction.write().step2();
    transaction.write().step3();
  }
  return 0;
}
