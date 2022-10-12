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

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = uint2022_t();
    uint32_t previous_overload = 0;
    for (int i = uint2022_t::CONTAINER_SIZE - 1; i >= 0 ; i--){
        if ((int64_t)lhs.digits[i] - previous_overload < (int64_t)rhs.digits[i]) {
            uint64_t minuend = (uint64_t)lhs.digits[i];
            uint64_t u64_1 = 1;
            uint64_t current_overload = u64_1 << 32;
            minuend = minuend | current_overload;
            uint64_t diff = minuend - (uint64_t)rhs.digits[i] - previous_overload;
            result.digits[i] =  diff;
            previous_overload = 1;
        } else {
            result.digits[i] = lhs.digits[i] - rhs.digits[i] - previous_overload;
            previous_overload = 0;
        }
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = uint2022_t();
    for (int i = uint2022_t::CONTAINER_SIZE - 1; i >= 0; i--) {
        int shift_size = uint2022_t::CONTAINER_SIZE - 1 - i;
        uint2022_t big_number = lhs;
        uint32_t digit = rhs.digits[i];
        uint2022_t unshifted_composition_part = big_number * digit;
        uint2022_t shifted_composition_part = shift(unshifted_composition_part, shift_size);
        result = result + shifted_composition_part;
    }
    std::cout << lhs << " * " << rhs << " = " << result << std::endl;
    return result;
}

uint2022_t sum_composition_parts(const std::vector<uint64_t>& composition_parts) {
    uint2022_t result = uint2022_t();
    for (int i = 0; i < composition_parts.size(); i++) {
        uint2022_t unshifted_big_number = from_uint64_t(composition_parts[i]);
        uint2022_t shifted_composition_part = shift(unshifted_big_number, i);
        result = result + shifted_composition_part;
    }
    return result;
}