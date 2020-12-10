#ifndef Action_h
#define Action_h

#include <memory>

class Model;
class Update;

class Action {
public:
    virtual std::unique_ptr<const Update> visit(Model &m) const = 0;
};

class unknownKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
};

class hKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
};

class lKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
};

class escKeyPressed: public Action {
public:
    std::unique_ptr<const Update> visit(Model &m) const override;
};

#endif 
