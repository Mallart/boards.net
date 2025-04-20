#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <string>
#include <vector>

namespace BoardsDotNet
{

    namespace HTML
    {
        // The core of the Document Object Model.
        class Node
        {
        protected:
            class Attribute
            {
                ::std::string name;
                ::std::string value;
            public:
                Attribute(::std::string _name, ::std::string _value);
                bool Equals(Attribute& other);
    
                ::std::string ToString();
            };
            static uint64_t lastId;
            // id to search fast in a document. Not rendered.
            uint64_t id;
            // the type of tag
            ::std::string tag;
            ::std::string textContent;
            Node* parent;
            public:
            ::std::vector<Node*> Children;
            ::std::vector<Attribute> Attributes;
            Node(Node* Parent, ::std::string tagName);
            void setContent(::std::string content);
            void Append(Node* node);
            void Remove(Node node);
            bool Equals(Node& node);
            ::std::string ToString();
        };
    
        // The root node of any HTML document.
        class Document
        {
            Node head;
            Node body;
        };
    }


    namespace JSON 
    {
        class Object
        {
            public:
            class Property
            {
                ::std::string name;
                ::std::string value;
                bool isNumber();
                public:
                Property(::std::string _name, ::std::string _value);
                ::std::string ToString();
            };
            
            protected:
            ::std::string name;
            ::std::vector<Property> _Properties;
            ::std::vector<Object*> _Children;
            public:
            
            Object(::std::string _name);
            
            // Parses a json string into an actual object
            virtual Object FromString(::std::string json_content);
            virtual ::std::string ToString();
        };
        
        class Array : public Object
        {
            public:
            Array(::std::string name, ::std::vector<Object*> objects) : Object{name}
            {
                _Children = objects;
            }
            
            ::std::string ToString() override;
        };
    }
    
    
}
#endif
    