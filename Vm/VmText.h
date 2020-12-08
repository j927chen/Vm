#ifndef VmText_h
#define VmText_h

#include <string>
#include "Text.h"

class VmText: public Text {
    
    std::string text;
    
public:
    
    VmText(std::string text);
    
    class VmTextIterator: public TextIterator {
        
        std::string::iterator it;
        
        VmTextIterator(std::string::iterator it);
        
    public:
        std::unique_ptr<TextIterator> clone() const override;
        bool operator!=(const TextIterator &other) const override;
        std::unique_ptr<TextIterator> operator++() override;
        char &operator*() const override;
        
        friend VmText;
    };
    
    class ConstVmTextIterator: public ConstTextIterator {
        
        std::string::const_iterator it;
        
        ConstVmTextIterator(std::string::const_iterator it);
        
    public:
        std::unique_ptr<ConstTextIterator> clone() const override;
        bool operator!=(const ConstTextIterator &other) const override;
        std::unique_ptr<ConstTextIterator> operator++() override;
        char const &operator*() const override;
        
        friend VmText;
    };
    
    std::unique_ptr<TextIterator> begin() override;
    std::unique_ptr<TextIterator> end() override;
    
    std::unique_ptr<ConstTextIterator> begin() const override;
    std::unique_ptr<ConstTextIterator> end() const override;
    
    std::unique_ptr<ConstTextIterator> cbegin() override;
    std::unique_ptr<ConstTextIterator> cend() override;
    
    ~VmText();
    
};

#endif
