#ifndef HTML_GEN_HPP
#define HTML_GEN_HPP

#include "../generators/Generators.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace BoardsDotNet::HTML
{
    // The core of the Document Object Model.
    Node::Attribute::Attribute(::std::string _name, ::std::string _value)
    {
        name = _name;
        value = _value;
    }

    bool Node::Attribute::Equals(Attribute& other)
    {
        return name == other.name && value == other.value;
    }

    ::std::string Node::Attribute::ToString()
    {
        return name+"=\""+value+"\"";
    }

    Node::Node(Node* Parent, ::std::string tagName)
    {
        // parent can be null too
        parent = Parent;
        tag = tagName;
    }

    void Node::setContent(::std::string content)
    {
        textContent = content;
    }

    void Node::Append(Node* node)
    {
        Children.push_back(node);
    }

    void Node::Remove(Node node)
    {
        for(::std::vector<Node*>::iterator _it = Children.begin(); _it != Children.end(); _it++)
            if((*_it)->id == node.id)
                Children.erase(_it);
    }

    bool Node::Equals(Node& node)
    {
        for(uint64_t i = 0;;++i)
        {
            if(i < Attributes.size())
                if(!Attributes[i].Equals(node.Attributes[i]))
                    return false;
            if(i < Children.size())
                if(!Children[i]->Equals(*node.Children[i]))
                    return false;
            if(i >= Children.size() && i >= Attributes.size())
            break;
        }
        return 1;
    }

    ::std::string Node::ToString()
    {
        ::std::string r = "<" + tag;
        for(Attribute a : Attributes)
            r += " " + a.ToString();
        r + ">" + textContent;
        for(Node* child : Children)
            r += child->ToString();
        return r + "</" + tag + ">";   
    }
}
#endif