#include "Action.h"
#include "Model.h"
#include "Update.h"

std::unique_ptr<const Update> unknownKeyPressed::visit(Model &m) const { return m.update(*this); }

std::unique_ptr<const Update> hKeyPressed::visit(Model &m) const { return m.update(*this); }

std::unique_ptr<const Update> lKeyPressed::visit(Model &m) const { return m.update(*this); }


std::unique_ptr<const Update> escKeyPressed::visit(Model &m) const { return m.update(*this); }
