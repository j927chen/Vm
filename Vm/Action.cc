#include "Action.h"
#include "Model.h"
#include "Update.h"

void unknownKeyPressed::visit(Model &m) { m.update(*this); }

void hKeyPressed::visit(Model &m) { m.update(*this); }

void escKeyPressed::visit(Model &m) { m.update(*this); }
