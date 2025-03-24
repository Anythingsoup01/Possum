#pragma once

#include <string>
#include <iostream>
#include <exception>

namespace Possum
{
    class NullExeption : public std::exception
    {
    public:
        NullExeption(const std::string message) : m_Message(message) {}

        const char* what() const noexcept override
        {
            return m_Message.c_str();
        }

    private:
        std::string m_Message;
    };

    class OutOfRangeException : public std::exception
    {
    public:
        OutOfRangeException(const std::string message) : m_Message(message) {}

        const char* what() const noexcept override
        {
            return m_Message.c_str();
        }

    private:
        std::string m_Message;
    };
}
