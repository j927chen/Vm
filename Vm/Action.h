#ifndef Action_h
#define Action_h

#include <memory>

class Model;
class Update;

class Action {
public:
    virtual std::unique_ptr<const Update> visit(Model &m) const = 0;
    virtual std::unique_ptr<const Action> clone() const = 0;
    virtual ~Action();
};

class otherKeyPressed: public Action {
public:
    int code;
    otherKeyPressed(int code);
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class enterKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class colonKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class forwardSlashKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class questionMarkKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class hKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class jKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class kKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class lKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class escKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

class backspaceKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
    std::unique_ptr<const Action> clone() const override;
};

#endif 
