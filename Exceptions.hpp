#pragma once
#include <stdexcept>

class IndexOutOfRange : public std::out_of_range 
{
    public:
        IndexOutOfRange(const std::string& msg) : std::out_of_range(msg) {}
};

class EmptyContainerError : public std::runtime_error 
{
    public:
        EmptyContainerError(const std::string& msg) : std::runtime_error(msg) {}
};