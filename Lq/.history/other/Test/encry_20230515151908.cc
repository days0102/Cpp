#include <iostream>

std::string encode(std::string text, std::string pwd)
{
    std::string res;
    int pwd_len = pwd.size();
    for (size_t i = 0; i < text.size(); i++)
    {
        res.append((text[i] * 2 + 32 + pwd[i % pwd_len]) % 128);
    }
}

std::string decode(std::string text, std::string pwd) {}

int main() {}