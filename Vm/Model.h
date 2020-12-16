#ifndef Model_h
#define Model_h

#include <memory>

class Update;
class Editor;
class Cursor;

class otherKeyPressed;
class numberKeyPressed;
class control_gKeyPressed;
class enterKeyPressed;
class dollarSignKeyPressed;
class colonKeyPressed;
class forwardSlashKeyPressed;
class questionMarkKeyPressed;
class AKeyPressed;
class IKeyPressed;
class NKeyPressed;
class caretKeyPressed;
class aKeyPressed;
class hKeyPressed;
class iKeyPressed;
class jKeyPressed;
class kKeyPressed;
class lKeyPressed;
class nKeyPressed;
class oKeyPressed;
class wKeyPressed;
class escKeyPressed;
class backspaceKeyPressed;

class Model {
public:
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const otherKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const numberKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const control_gKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const enterKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const dollarSignKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const colonKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const forwardSlashKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const questionMarkKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const AKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const IKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const NKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const caretKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const aKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const hKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const iKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const jKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const kKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const lKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const nKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const oKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const wKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const escKeyPressed> a) = 0;
    virtual std::unique_ptr<const Update> update(std::unique_ptr<const backspaceKeyPressed> a) = 0;
    virtual const std::string &getFileName() const = 0;
    virtual const Editor &getEditor() const = 0;
    virtual const Cursor &getCursor() const = 0;
    virtual ~Model();
};

#endif 
