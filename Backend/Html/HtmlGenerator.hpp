#include <cstdint>
#include <string>
#include <vector>

namespace BoardsDotNet::HTML
{
    // The core of the Document Object Model.
    class HTMLNode
    {
    protected:
        class Attribute
        {
            ::std::string name;
            ::std::string value;
        public:
            Attribute(::std::string _name, ::std::string _value)
            {
                name = _name;
                value = _value;
            }

            bool Equals(Attribute& other)
            {
                return name == other.name && value == other.value;
            }

            ::std::string ToString()
            {
                return name+"=\""+value+"\"";
            }
        };
        static uint64_t lastId;
        // id to search fast in a document. Not rendered.
        uint64_t id;
        // the type of tag
        ::std::string tag;
        ::std::string textContent;
        HTMLNode* parent;
        public:
        ::std::vector<HTMLNode> Children;
        ::std::vector<Attribute> Attributes;

        HTMLNode(HTMLNode* Parent, ::std::string tagName)
        {
            // parent can be null too
            parent = Parent;
            tag = tagName;
        }

        void setContent(::std::string content)
        {
            textContent = content;
        }

        void Append(HTMLNode& node)
        {
            Children.push_back(node);
        }

        void Remove(HTMLNode& node)
        {
            for(::std::vector<HTMLNode>::iterator _it = Children.begin(); _it != Children.end(); _it++)
                if(_it->id == node.id)
                    Children.erase(_it);
        }

        bool Equals(HTMLNode& node)
        {
            for(uint64_t i = 0;;++i)
            {
                if(i < Attributes.size())
                    if(!Attributes[i].Equals(node.Attributes[i]))
                        return false;
                if(i < Children.size())
                    if(!Children[i].Equals(node.Children[i]))
                        return false;
                if(i >= Children.size() && i >= Attributes.size())
                break;
            }
            return 1;
        }

        ::std::string ToString()
        {
            ::std::string r = "<" + tag;
            for(Attribute a : Attributes)
                r += " " + a.ToString();
            r + ">" + textContent;
            for(HTMLNode child : Children)
                r += child.ToString();
            return r + "</" + tag + ">";   
        }
    };

    // The root node of any HTML document.
    class Document
    {
        HTMLNode head;
        HTMLNode body;
    };
}