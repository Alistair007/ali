#include <iostream>
#include <bitset>

class bool_pack {
private:
    std::bitset<8> data;

public:
    class BitProxy {
    private:
        std::bitset<8>& data;
        size_t index;

    public:
        BitProxy(std::bitset<8>& data, size_t index) : data(data), index(index) {}

        operator bool() const {
            return data.test(index);
        }

        BitProxy& operator=(bool value) {
            data.set(index, value);
            return *this;
        }
    };

    BitProxy operator[](size_t index) {
        return BitProxy(data, index);
    }

    const bool operator[](size_t index) const {
        return data.test(index);
    }

    friend std::ostream& operator<<(std::ostream& os, const bool_pack& obj) {
        os << obj.data;
        return os;
    }
};
