#pragma once
#include <stdexcept>

class IndexOutOfRange : public std::out_of_range {
public:
    explicit IndexOutOfRange(const std::string& msg) : std::out_of_range(msg) {}
};

class EmptyContainerError : public std::runtime_error {
public:
    explicit EmptyContainerError(const std::string& msg) : std::runtime_error(msg) {}
};