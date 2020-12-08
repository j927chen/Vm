#ifndef Text_h
#define Text_h

#include <memory>

class TextIterator {
    
public:
    virtual std::unique_ptr<TextIterator> clone() const = 0;
    virtual bool operator!=(const TextIterator &other) const = 0;
    virtual std::unique_ptr<TextIterator> operator++() = 0;
    virtual char &operator*() const = 0;
    virtual ~TextIterator();
};

class ConstTextIterator {
    
public:
    virtual std::unique_ptr<ConstTextIterator> clone() const = 0;
    virtual bool operator!=(const ConstTextIterator &other) const = 0;
    virtual std::unique_ptr<ConstTextIterator> operator++() = 0;
    virtual const char &operator*() const = 0;
    virtual ~ConstTextIterator();
};

class Text {
    
public:
    
    virtual std::unique_ptr<TextIterator> begin() = 0;
    virtual std::unique_ptr<TextIterator> end() = 0;
    
    virtual std::unique_ptr<ConstTextIterator> begin() const = 0;
    virtual std::unique_ptr<ConstTextIterator> end() const = 0;
    
    virtual std::unique_ptr<ConstTextIterator> cbegin() = 0;
    virtual std::unique_ptr<ConstTextIterator> cend() = 0;
    
    virtual ~Text();
};

#endif
