#include "Action.h"
#include "Model.h"
#include "Update.h"

Action::~Action() {}


otherKeyPressed::otherKeyPressed(int code): code{code} {}

std::unique_ptr<const Action> otherKeyPressed::clone() const {
    return std::make_unique<const otherKeyPressed>(code);
}

std::unique_ptr<const Update> otherKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const otherKeyPressed>(code)); }


std::unique_ptr<const Action> enterKeyPressed::clone() const {
    return std::make_unique<const enterKeyPressed>(); }

std::unique_ptr<const Update> enterKeyPressed::visit(Model &m) const {
    return m.update(std::make_unique<const enterKeyPressed>()); }


std::unique_ptr<const Update> colonKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const colonKeyPressed>()); }

std::unique_ptr<const Action> colonKeyPressed::clone() const {
    return std::make_unique<const colonKeyPressed>(); }


std::unique_ptr<const Update> hKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const hKeyPressed>()); }

std::unique_ptr<const Action> hKeyPressed::clone() const {
    return std::make_unique<const hKeyPressed>(); }
    
    
std::unique_ptr<const Update> jKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const jKeyPressed>()); }

std::unique_ptr<const Action> jKeyPressed::clone() const {
    return std::make_unique<const jKeyPressed>(); }


std::unique_ptr<const Update> kKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const kKeyPressed>()); }

std::unique_ptr<const Action> kKeyPressed::clone() const {
    return std::make_unique<const kKeyPressed>(); }


std::unique_ptr<const Update> lKeyPressed::visit(Model &m) const { return m.update(std::make_unique<lKeyPressed>()); }

std::unique_ptr<const Action> lKeyPressed::clone() const {
    return std::make_unique<const lKeyPressed>(); }


std::unique_ptr<const Update> escKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const escKeyPressed>()); }

std::unique_ptr<const Action> escKeyPressed::clone() const {
    return std::make_unique<const escKeyPressed>(); }

std::unique_ptr<const Update> backspaceKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const backspaceKeyPressed>()); }

std::unique_ptr<const Action> backspaceKeyPressed::clone() const {
    return std::make_unique<const backspaceKeyPressed>(); }
