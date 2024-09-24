// sandbox_idea: cpp/basics
// sandbox_name: signals_example
// sandbox_description: how to wrap process signals in a class
// sandbox_env: cpp

#include <chrono>
#include <csignal>
#include <functional>
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

std::function<void(int)> hh;

class Application {
  struct AToken {
    friend Application;

  private:
    explicit AToken() = default;
  };

public:
  static Application *create() {
    if (instance_ == nullptr) {
      instance_ = std::make_unique<Application>(AToken());
      signal(SIGINT, Application::handler);
    }
    return instance_.get();
  }
  static Application *instance() { return instance_.get(); }
  static std::unique_ptr<Application> instance_;

  static void handler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    instance()->stop();
    exit(signum);
  }

  void run() { std::cout << "run" << std::endl; }

  Application(AToken) {}

private:
  void stop() { std::cout << "stop" << std::endl; }
};

std::unique_ptr<Application> Application::instance_ = nullptr;

int main(void) {
  Application *app = Application::create();

  while (1) {
    app->run();
    std::this_thread::sleep_for(2000ms);
  }
  return 0;
}
