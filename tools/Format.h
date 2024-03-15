#pragma once
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::wstring;

class Format
{
private:
    static size_t myPrintfInnerLen(const char *message, va_list params)
    {
        return vsnprintf(NULL, 0, message, params);
    }

    static std::string myPrintfInner(size_t length, const char *message, va_list params)
    {
        std::string strBuf(length, '\0');
        vsnprintf(&strBuf[0], length, message, params);

        return strBuf;
    }

public:
    static std::string format(const char *message, ...)
    {
        va_list va_args;
        va_start(va_args, message);
        size_t length = myPrintfInnerLen(message, va_args);
        va_end(va_args);
        va_start(va_args, message);
        auto strBuf = myPrintfInner(length + 1, message, va_args);
        va_end(va_args);

        strBuf.pop_back();

        return strBuf;
    }

    static std::wstring format(const wchar_t *msg, ...)
    {
        va_list arg_ptr;
        va_start(arg_ptr, msg);

        int len = vswprintf(NULL, 0, msg, arg_ptr) + 1;
        std::wstring strBuf(len, L'\0');
        vswprintf(&strBuf[0], len, msg, arg_ptr);

        va_end(arg_ptr);

        strBuf.pop_back();

        return strBuf;
    }
};