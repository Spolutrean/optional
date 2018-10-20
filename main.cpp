#include <iostream>
#include "optional.h"

struct kek {
    std::string s = "222";
    kek(std::string kk) {
        s = kk;
    }
};

int main() {
    optional<int> a(222);
    optional<int> b = 2222;
    std::cout<<"a < b = " << (a < b) << "\n";
    std::cout<<"a <= b = " << (a <= b) << "\n";
    std::cout<<"a > b = " << (a > b) << "\n";
    std::cout<<"a >= b = " << (a >= b) << "\n";
    std::cout<<"a == b = " << (a == b) << "\n";
    std::cout<<"a != b = " << (a != b) << "\n";

    optional<kek> aa(kek("ss"));
    optional<kek> bb(kek("ss"));

    std::cout << (aa < bb);

    return 0;
}