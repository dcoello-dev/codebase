// sandbox_idea: cpp/ideas
// sandbox_name: mask_monitor
// sandbox_description:
// sandbox_env: cpp

#include <cstdint>
#include <cstring>
#include <iostream>
#include <bitset>
#include <memory>

enum class Events: uint32_t {
    ERROR_1,
    ERROR_2,
    ERROR_3,
    ERROR_4
};

struct MonitorPayload {
    uint32_t header;
    uint32_t payload;
};


struct Monitor {
    Monitor() {
        reset();
    }

    void set(const uint32_t & event){
        payload.payload |= 0x01 << event;
    }

    MonitorPayload get(){
        return payload;
    } 

    void reset () {
        memset(&payload, 0x00, sizeof(payload));
    }

    void print() {
        std::bitset<32>b(payload.payload);
        std::cout << b << std::endl;
    }

private:

    MonitorPayload payload{};
};

struct CentralMonitor {
    static Monitor& get_instance() {
        static std::unique_ptr<Monitor> instance = std::make_unique<Monitor>();
        return *instance;
    }
};

template<typename T>
void set(const T& event){
    CentralMonitor::get_instance().set(static_cast<uint32_t>(event));
}

MonitorPayload get(){
    auto ret = CentralMonitor::get_instance().get();
    CentralMonitor::get_instance().print();
    CentralMonitor::get_instance().reset();
    return ret;
}

int main(void) {
    set(Events::ERROR_1);
    get();
    set(Events::ERROR_2);
    set(Events::ERROR_3);
    get();
    return 0;
}
