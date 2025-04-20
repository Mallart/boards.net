#include "./generators/Generators.hpp"
#include <string>
#include <iostream>

void JSONTest(void)
{
    using namespace BoardsDotNet::JSON;
    auto jobj = BoardsDotNet::JSON::Object();
    jobj.AddProperty({"Root", "None"});
    jobj.AddChild(
        new Object(
            "Rawr", {{"prop1", "val1"}},{
                new Object("awa", {{"prop1", "val1"}}, {}),
                new Object("owo", {{"prop1", "val2"}}, {}),
                new Array("ArrayExample", {
                    new Object({{"exampleprop", "examplevalue"}}, {new Object("testobj", {{"prop2", "val1"}}, {})})
                }),
            }
        )
    );
    ::std::cout << jobj.ToString() << ::std::endl;
}


int main(int argc, char** argv)
{
    // ::std::string[] Argv = argv;
    JSONTest();
    return 0;
}