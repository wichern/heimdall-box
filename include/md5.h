#pragma once

#include <cstdint>
#include <string>

class MD5
{
public:
    MD5();
    ~MD5();

    void update(const uint8_t* in, uint32_t size);
    void update(const std::string& str);
    void update(const std::u16string& str);
    std::string digest();

    static std::string Calc(const std::string& str) {
        MD5 md5;
        md5.update(str);
        return md5.digest();
    }

    static std::string Calc(const std::u16string& str) {
        MD5 md5;
        md5.update(str);
        return md5.digest();
    }

private:
    void transform(uint32_t state[4], const uint8_t block[64]);
    void decode(uint32_t* output, const uint8_t* input, uint32_t len);
    void encode(uint8_t* output, const uint32_t* input, uint32_t len);

    uint32_t state[4] = {};
    uint32_t count[2] = {};
    uint8_t buffer[64] = {};
};
