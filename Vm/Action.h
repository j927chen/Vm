#ifndef Action_h
#define Action_h

class Model;

class Action {
public:
    virtual void visit(Model &m) = 0;
};

class unknownKeyPressed: public Action {
public:
    void visit(Model &m) override;
};

class hKeyPressed: public Action {
public:
    void visit(Model &m) override;
};

class escKeyPressed: public Action {
public:
    void visit(Model &m) override;
};

#endif 
