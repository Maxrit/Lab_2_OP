#include "number.h"


uint2022_t from_uint(uint32_t i) {
    uint2022_t result = uint2022_t();
    result.digits[uint2022_t::CONTAINER_SIZE - 1] = i;
    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result = uint2022_t();
    std::string str(buff);
    std::string a;
    uint2022_t shift_base = from_uint(10000000);
    uint2022_t current_shift = from_uint(1);
    while (str.length() > 0) {
        if (str.length() < 8) {
            a = str.substr(0, str.length());
            str = str.substr(0,0);
            //std::cout << "a = " << a << std::endl;
            //std::cout << "str = " << str << std::endl;
        } else {
            a = str.substr(str.length() - 8, 8);
            str = str.substr(0, str.length()-8);
            //std::cout << "a = " << a << std::endl;
            //std::cout << "str = " << str << std::endl;
        }
        const char *c = a.c_str();
        uint32_t unshifted = atoi(c);
        uint2022_t shifted = current_shift * unshifted;
        current_shift = current_shift * shift_base;
        result = result + shifted;
    }
    return  result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = uint2022_t();
    int overload = 0;
    for (int i = uint2022_t::CONTAINER_SIZE - 1; i >= 0 ; i--){
        uint64_t sum = (uint64_t)lhs.digits[i];
        sum += (uint64_t)rhs.digits[i] + overload;
        result.digits[i] = sum % (1LL << 32);
        overload = sum >> 32;
    }
    std::cout << lhs << " + " << rhs << " = " << result << std::endl;
    return result;
}

uint2022_t shift(const uint2022_t& big_number, const int& shift_length) {
    uint2022_t result = uint2022_t();
    for (int i = 0; i < uint2022_t::CONTAINER_SIZE; i++) {
        result.digits[i] = ((i + shift_length) < uint2022_t::CONTAINER_SIZE) ? big_number.digits[i+shift_length] : 0;
    }
    return result;
}