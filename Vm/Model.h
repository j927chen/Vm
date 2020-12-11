#ifndef Model_h
#define Model_h

#include <memory>

class Update;

class unknownKeyPressed;
class hKeyPressed;
class jKeyPressed;
class kKeyPressed;
class lKeyPressed;
class escKeyPressed;

class Text;
class Cursor;

class Model {
public:
    virtual std::unique_ptr<const Update> update(const unknownKeyPressed &a) = 0;
    virtual std::unique_ptr<const Update> update(const hKeyPressed &a) = 0;
    virtual std::unique_ptr<const Update> update(const jKeyPressed &a) = 0;
    virtual std::unique_ptr<const Update> update(const kKeyPressed &a) = 0;
    virtual std::unique_ptr<const Update> update(const lKeyPressed &a) = 0;
    virtual std::unique_ptr<const Update> update(const escKeyPressed &a) = 0;
    virtual const Text &getText() = 0;
    virtual const Cursor &getCursor() = 0;
    virtual ~Model();
};

#endif 
