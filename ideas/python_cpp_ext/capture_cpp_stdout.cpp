// sandbox_idea: python_cpp_ext
// sandbox_name: capture_cpp_stdout
// sandbox_description: how to capture cpp stdout
// sandbox_env: cpp

#include <cstdio>
#include <iostream>

template <typename C> class StdoutSniffer : public std::streambuf {
public:
  StdoutSniffer(C c) : callback_(c) {}
  ~StdoutSniffer() { disable(); }
  void enable() { std::cout.rdbuf(this); }
  void disable() { std::cout.rdbuf(coutbuf); }

protected:
  int overflow(int ch) override {
    buffer += ch;
    if (ch == '\n') {
      callback_(buffer);
      buffer.clear();
    }
    return ch;
  }

private:
  std::streambuf *coutbuf = std::cout.rdbuf();
  std::string buffer;
  C callback_;
};

int main(void) {
  auto callback = [](const std::string &line) -> void {
    printf("callback: %s", line.c_str());
  };
  StdoutSniffer<decltype(callback)> sniffer(callback);

  sniffer.enable();
  std::cout << "hello world!" << std::endl;
  sniffer.disable();

  std::cout << "hello world!" << std::endl;
  return 0;
}
