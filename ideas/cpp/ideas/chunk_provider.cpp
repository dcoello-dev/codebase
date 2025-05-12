// sandbox_idea: cpp/ideas
// sandbox_name: chunk_provider
// sandbox_description:
// sandbox_env: cpp

#include <iostream>
#include <array>
#include <string.h>

class Buffer{
public:
    Buffer(uint8_t* b, size_t ms){
        reset(b, ms);
    }

    void reset(uint8_t* b, size_t ms)
    {
        _buffer = b;
        _max_size = ms;
        _size = 0;
    }

    size_t size(){
        return _size;
    }

    size_t max_size(){
        return _max_size;
    }

    template<typename T>
    bool assign(const T& b){
        return assign(b.data(), b.size());
    }

    bool assign(const uint8_t* ptr, size_t s){
        if (s <= max_size()){
            memcpy(_buffer, ptr, s);
            _size = s;
            return true;
        }
        return false;
    }

    size_t append(const uint8_t* ptr, size_t s)
    {
        size_t min = std::min(s, max_size() - size());
        memcpy(_buffer + size(), ptr, min);
        _size += min;
        return s - min;
    }

private:
    uint8_t* _buffer = nullptr;
    size_t _size = 0;
    size_t _max_size = 0;
};

template<size_t N, size_t C>
class ChunkProvider {

    Buffer* get_chunk(){
        if (counter < N / C){
            buffer.reset(pool.data() + (C * counter), C);
            counter++;
            return &buffer;
        }
        return nullptr;
    }

    bool end(){
        finish = true;
        return finish;
    }

private:
    bool finish = false;
    std::array<uint8_t, N> pool{};
    Buffer buffer{nullptr, 0};
    size_t counter = 0;
};

int main(void) {
    std::array<uint8_t, 50> p{};
    Buffer buff {p.data(), 50};
    std::array<uint8_t, 500> p2{};
    p2.fill(0xBB);

    buff.assign(p2.data(), 10);
    std::cout << buff.size() << " " << buff.append(p2.data(), 100) << " " << buff.size() <<  std::endl;
    return 0;
}
