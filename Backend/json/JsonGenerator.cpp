#ifndef JSON_GEN_HPP
#define JSON_GEN_HPP

#include "../generators/Generators.hpp"
#include <cstdio>
#include <stdexcept>

namespace BoardsDotNet::JSON 
{
    void Array::AddChild(Array* object)
    {
        if(object->name.empty())
            _Children.push_back(object);
        else
            throw ::std::invalid_argument("In-array object shouldn't have a name.");
    }

    ::std::string Array::ToString()
    {
        ::std::string r = "\"" + name + "\":[";
        for(Array* o : _Children)
            r += o->ToString() + ",";
        if(!_Children.empty())
            r.erase(r.length() - 1, 1); // deletes last comma
    
        return r + "]";
    }

    bool Object::Property::isNumber()
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

    Object::Property::Property(::std::string _name, ::std::string _value)
    {
        name = _name;
        value = _value;
    }

    ::std::string Object::Property::ToString()
    {
        if(isNumber())
            return "\"" + name + "\"" + ":" + value;
        else
            return "\"" + name + "\"" + ":\"" + value + "\"";
    }

    void Object::AddProperty(Object::Property property)
    {
        _Properties.push_back(property);
    }

    void Object::AddChild(Array* object)
    {
        if(dynamic_cast<Object*>(object) && ((Object*)object)->IsString())
        {
            throw ::std::invalid_argument("Cannot add a string to an object. Use a property instead.");
            return;
        }
        _Children.push_back(object);
    }

    bool Object::IsString()
    {
        return !(_Children.size() + _Properties.size());
    }

    Object Object::FromString(::std::string json_content)
    {
        int _brace_rotator = 0;
        size_t _to = 0;
        for(size_t i = 0; i < json_content.length(); ++i)
        {
            switch(json_content[i])
            {
                case '{': _brace_rotator++; break;
                case '}': _brace_rotator--; break;
            }
            // when the rotator is null, opening and closing braces are even -> object is delimited
            if(!_brace_rotator)
                break;
        }
        
        return (Object)0;
    }

    ::std::string Object::ToString()
    {
        ::std::string r;
        if(_Children.empty() && _Properties.empty())
            return "\"" + name + "\"";
        else
            if(name.empty())
                r = "{";
            else
                r = "\"" + name + "\"" + ":{";
            // returns a simple string if no child or property is provided

        for(Property p : _Properties)
            r += p.ToString() + ",";
        if(!_Properties.empty() && _Children.empty())
            r.erase(r.length() - 1, 1); // deletes last comma

        for(Array* o : _Children)
            r += o->ToString() + ",";
        if(!_Children.empty())
            r.erase(r.length() - 1, 1); // deletes last comma

        return r + "}";
    };
};

#endif
