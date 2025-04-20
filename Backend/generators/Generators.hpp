#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <initializer_list>
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
        class Object;

        class Array
        {
                        
            protected:
            ::std::string name;
            ::std::vector<Object*> _Children;
            public:
            Array(::std::string _name)
            {
                name = _name;
            }

            Array(::std::string name, ::std::initializer_list<Object*> objects)
            {
                _Children = objects;
            }
            
            virtual void AddChild(Object* object);
            virtual ::std::string ToString();
        };

        class Object : public Array
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
            ::std::vector<Property> _Properties;
        public:
            
            Object(::std::string _name) : Array{_name} {};
            // Creates an anonymous object, like a JSON root
            Object() : Array{::std::string()} {};
            // Builds an object initialized with sub objects
            Object(::std::initializer_list<Property> _properties, ::std::initializer_list<Object*> _objects) : Object() 
            {
                for(Property property : _properties)
                    AddProperty(property);
                for(Object* obj : _objects)
                    AddChild(obj);
            }
            // Builds an object initialized witha name and sub objects
            Object(::std::string _name, ::std::initializer_list<Property> _properties, ::std::initializer_list<Object*> _objects) : Object{_name} 
            {
                for(Property property : _properties)
                    AddProperty(property);
                for(Object* obj : _objects)
                    AddChild(obj);
            }

            // Returns true if this object does NOT contain any property or sub object
            bool IsString();
            
            void AddProperty(Property property);
            void AddChild(Object* object) override;
            // Parses a json string into an actual object
            virtual Object FromString(::std::string json_content);
            ::std::string ToString() override;
        };
    }
    
    
}
#endif
    