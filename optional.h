//
// Created by ydsviridov on 20.10.18.
//
#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include "optional-exception.h"

template <typename T>
struct optional {
    optional(): valid(false), storage(nullptr) {}

    optional(T const& otherVal):valid(true), storage(new T(otherVal)) {}

    optional(optional const& otherOptional):valid(otherOptional.valid) {
        if(otherOptional.valid) {
            storage = new T(*otherOptional.storage);
        } else {
            storage = nullptr;
        }
    }

    optional& operator=(optional const& other) {
        if(storage == other.storage) {
            return *this;
        }
        clear();
        if(other.valid) {
            valid = other.valid;
            storage = new T(*other.storage);
        }
        return (*this);
    }

    void clear(){
        if(valid) {
            delete storage;
        }
        valid = false;
    }

    explicit operator bool() const {
        return valid;
    }

    T& operator*() {
        if(valid) {
            return *storage;
        }
        else {
            throw bad_optional_access("Resourse is undefined");
        }
    }

    T const& operator*() const {
        if(valid) {
            return *storage;
        }
        else {
            throw bad_optional_access("Resourse is undefined");
        }
    }

    T const* operator->() const {
        return storage;
    }

    T* operator->() {
        return storage;
    }

    ~optional(){
        if(valid) {
            delete storage;
        }
    }

    template<typename F>
    friend void swap(optional<F> &a, optional<F> &b);

private:
    bool valid;
    T* storage;
};

template<typename F>
void swap(optional<F> &a, optional<F> &b) {
    std::swap(a.valid, b.valid);
    std::swap(a.storage, b.storage);
}

template<typename T>
decltype(std::declval<T>() < std::declval<T>(), bool())
operator<(optional<T> const &a, optional<T> const &b) {
    if (!b) {
        return false;
    }
    if (!a) {
        return true;
    }
    return *a < *b;
}

template<typename T>
bool operator>=(optional<T> const &a, optional<T> const &b) {
    return !(operator<(a, b));
}

template<typename T>
bool operator==(optional<T> const &a, optional<T> const &b) {
    if (a) {
        if (b) {
            return *a == *b;
        }
        else {
            return false;
        }
    }
    else {
        return !b;
    }
}

template<typename T>
bool operator>(optional<T> const &a, optional<T> const &b) {
    return operator<(b, a);
}

template<typename T>
bool operator<=(optional<T> const &a, optional<T> const &b) {
    return !operator>(a, b);
}

template<typename T>
bool operator!=(optional<T> const &a, optional<T> const &b) {
    return !operator==(a, b);
}

#endif //OPTIONAL_OPTIONAL_H
