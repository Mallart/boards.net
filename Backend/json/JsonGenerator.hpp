#include <vector>
#include <string>

namespace BoardsDotNet::JSON 
{
    class Object
    {
        public:
        class Property
        {
            ::std::string name;
            ::std::string value;

            bool isNumber()
            {
                for(char c : value)
                    for(uint8_t i = '0'; i <= '9'; ++i)
                    {
                        if(c == i)
                            continue;
                        if(c != '9' && i == '9')
                            return 0;
                    }
                return 1;
            }

        public:
            Property(::std::string _name, ::std::string _value)
            {
                name = _name;
                value = _value;
            }

            ::std::string ToString()
            {
                if(isNumber())
                    return name + ":" + value;
                else
                    return name + ":\"" + value + "\"";
            }
        };
        Object(); 
        virtual ::std::string ToString()
        {

        };
    protected:
        ::std::vector<Property> _Properties;
        ::std::vector<Object*> _Children;
    };

    class Array : public Object
    {
    public:
        Array(::std::vector<Object*> objects);
        ::std::string ToString() override
        {
            ::std::string r = "[";

            return r + "]";
        }
    };
}