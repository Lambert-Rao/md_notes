#include <iostream>
#include <fstream>
#include "example.pb.h"

int main() {
    using namespace std;
    std::fstream ofs("test.pb", std::ios::out | std::ios::binary|std::ios::app);

    example:: person p;
    p.set_id(123);
    p.set_name("hello");
    p.phone_type_Name(example::person::MOBILE);
    auto k = p.mutable_name();
    k->append("hello");
    auto&& p2 = std::move(p);
    p.SerializeToOstream(&ofs);
    ofs.close();
    std::fstream ifs("test.pb", std::ios::in | std::ios::binary);
    example::person d;
    if (!d.ParseFromIstream(&ifs)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }
    std::cout << d.DebugString() << std::endl;
}
