#ifndef VmText_h
#define VmText_h

#include <string>
#include "Text.h"

class VmText: public Text {
    
    std::string text;
    bool modified;
    size_t numOfLines;
    size_t numOfChars;
    
public:
    
    VmText();
    VmText(std::string text);
    VmText(const VmText &other);
    
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
        bool operator=(const ConstTextIterator &other) const override;
        bool operator!=(const ConstTextIterator &other) const override;
        bool operator==(const ConstTextIterator &other) const override;
        std::unique_ptr<ConstTextIterator> operator++() override;
        std::unique_ptr<ConstTextIterator> operator--() override;
        char const &operator*() const override;
        std::unique_ptr<ConstTextIterator> next() const override;
        std::unique_ptr<ConstTextIterator> previous() const override;
        
        friend VmText;
    };
    
    bool isEmpty() const override;
    
    bool wasModified() const override;
    
    int getLength() const override;
    
    int getNumOfLines() const override;
    
    int getNumOfChars() const override;
    
    std::unique_ptr<TextIterator> begin() override;
    std::unique_ptr<TextIterator> end() override;
    
    std::unique_ptr<ConstTextIterator> begin() const override;
    std::unique_ptr<ConstTextIterator> end() const override;
    
    std::unique_ptr<ConstTextIterator> beginAtLine(int ln) const override;
    void advanceToStartOfNextLine(ConstTextIterator &it) const override;
    std::unique_ptr<ConstTextIterator> goBackToStartOfPreviousLine(ConstTextIterator &it) const override;
    
    std::unique_ptr<ConstTextIterator> cbegin() override;
    std::unique_ptr<ConstTextIterator> cend() override;
    
    std::unique_ptr<ConstTextIterator> insert(char c , const ConstTextIterator &it) override;
    
    std::unique_ptr<ConstTextIterator> remove(const ConstTextIterator &it) override;
    
    std::unique_ptr<Text> clone() const override;
    
    ~VmText();
    
};

#endif
