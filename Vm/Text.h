#ifndef Text_h
#define Text_h

#include <memory>
class Posn;

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
    virtual bool operator=(const ConstTextIterator &other) const = 0;
    virtual bool operator!=(const ConstTextIterator &other) const = 0;
    virtual bool operator==(const ConstTextIterator &other) const = 0;
    virtual std::unique_ptr<ConstTextIterator> operator++() = 0;
    virtual std::unique_ptr<ConstTextIterator> operator--() = 0;
    virtual const char &operator*() const = 0;
    virtual std::unique_ptr<ConstTextIterator> next() const = 0;
    virtual std::unique_ptr<ConstTextIterator> previous() const = 0;
    virtual ~ConstTextIterator();
};

class Text {
    
public:
    
    virtual bool isEmpty() const = 0;
    
    virtual bool wasModified() const = 0;
    
    virtual int getLength() const = 0;
    
    virtual int getNumOfLines() const = 0;
    
    virtual int getNumOfChars() const = 0;
    
    virtual std::unique_ptr<TextIterator> begin() = 0;
    virtual std::unique_ptr<TextIterator> end() = 0;
    
    virtual std::unique_ptr<ConstTextIterator> begin() const = 0;
    virtual std::unique_ptr<ConstTextIterator> end() const = 0;
    
    virtual std::unique_ptr<ConstTextIterator> beginAtLine(int ln) const = 0;
    virtual void advanceToStartOfNextLine(ConstTextIterator &it) const = 0;
    virtual std::unique_ptr<ConstTextIterator> goBackToStartOfPreviousLine(ConstTextIterator &it) const = 0;
    
    virtual std::unique_ptr<ConstTextIterator> cbegin() = 0;
    virtual std::unique_ptr<ConstTextIterator> cend() = 0;
    
    virtual std::unique_ptr<ConstTextIterator> insert(char c , const ConstTextIterator &it) = 0;
    
    virtual std::unique_ptr<ConstTextIterator> remove(const ConstTextIterator &it) = 0;
    
    virtual ~Text();
};

#endif
