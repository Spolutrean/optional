//
// Created by ydsviridov on 20.10.18.
//
#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include "optional-exception.h"

template <typename T>
struct optional {
    optional(): valid(false) {}

    optional(T const& otherVal):valid(true) {
        new(&storage) T(otherVal);
    }

    optional(optional const& otherOptional):valid(otherOptional.valid) {
        if(otherOptional.valid) {
            new(&storage) T(*otherOptional);
        }
    }

    optional& operator=(optional const& other) {
        optional<T> forSwap(other);
        swap(*this, forSwap);
        return *this;
    }

    void clear(){
        if(valid) {
            reinterpret_cast<T*>(&storage)->~T();
        }
        valid = false;
    }

    explicit operator bool() const {
        return valid;
    }

    T& operator*() {
        if(valid) {
            return *(reinterpret_cast<T*>(&storage));
        }
        else {
            throw bad_optional_access("Resourse is undefined");
        }
    }

    T const& operator*() const {
        if(valid) {
            return *(reinterpret_cast<T const *>(&storage));
        }
        else {
            throw bad_optional_access("Resourse is undefined");
        }
    }

    T const* operator->() const {
        return reinterpret_cast<T const*>(&storage);
    }

    T* operator->() {
        return reinterpret_cast<T *>(&storage);
    }

    ~optional(){
        clear();
    }

    template<typename F>
    friend void swap(optional<F> &a, optional<F> &b);

private:
    bool valid;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage;
    T& getOriginalType() {
        return *reinterpret_cast<T*>(&storage);
    }
};

template<typename F>
void swap(optional<F> &a, optional<F> &b) {
    if(a && b) {
        std::swap(*reinterpret_cast<F*>(&a.storage), *reinterpret_cast<F*>(&b.storage));
    } else if(a) {
        new(&b.storage) F(*reinterpret_cast<F*>(&a.storage));
        reinterpret_cast<F*> (&a.storage)->~F();
    } else if(b) {
        new(&a.storage) F(*reinterpret_cast<F*>(&b.storage));
        reinterpret_cast<F*> (&b.storage)->~F();
    }
    std::swap(a.valid, b.valid);
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
