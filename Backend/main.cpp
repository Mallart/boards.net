#include "./generators/Generators.hpp"
#include <string>
#include <iostream>

void test(void)
{
    auto jobj = BoardsDotNet::JSON::Object("uwu");
    ::std::cout << jobj.ToString();
}


int main(int argc, char** argv)
{
    // ::std::string[] Argv = argv;
    test();
    return 0;
}