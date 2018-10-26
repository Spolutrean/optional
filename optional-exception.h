//
// Created by ydsviridov on 20.10.18.
//
#ifndef OPTIONAL_EXCEPTION_H
#define OPTIONAL_EXCEPTION_H
#include <stdexcept>

struct bad_optional_access : std::runtime_error {
    bad_optional_access(const std::string& message) : runtime_error(message){}
};
#endif
