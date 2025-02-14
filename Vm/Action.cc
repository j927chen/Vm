#include "Action.h"
#include "Model.h"
#include "Update.h"

Action::~Action() {}


otherKeyPressed::otherKeyPressed(int code): code{code} {}

std::unique_ptr<const Action> otherKeyPressed::clone() const {
    return std::make_unique<const otherKeyPressed>(code);
}

std::unique_ptr<const Update> otherKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const otherKeyPressed>(code)); }


numberKeyPressed::numberKeyPressed(int num): num{num} {}

std::unique_ptr<const Action> numberKeyPressed::clone() const {
    return std::make_unique<const numberKeyPressed>(num);
}

std::unique_ptr<const Update> numberKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const numberKeyPressed>(num)); }


std::unique_ptr<const Action> control_gKeyPressed::clone() const {
    return std::make_unique<const control_gKeyPressed>(); }

std::unique_ptr<const Update> control_gKeyPressed::visit(Model &m) const {
    return m.update(std::make_unique<const control_gKeyPressed>()); }


std::unique_ptr<const Action> enterKeyPressed::clone() const {
    return std::make_unique<const enterKeyPressed>(); }

std::unique_ptr<const Update> enterKeyPressed::visit(Model &m) const {
    return m.update(std::make_unique<const enterKeyPressed>()); }


std::unique_ptr<const Update> dollarSignKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const dollarSignKeyPressed>()); }

std::unique_ptr<const Action> dollarSignKeyPressed::clone() const {
    return std::make_unique<const dollarSignKeyPressed>(); }


std::unique_ptr<const Update> colonKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const colonKeyPressed>()); }

std::unique_ptr<const Action> colonKeyPressed::clone() const {
    return std::make_unique<const colonKeyPressed>(); }


std::unique_ptr<const Update> forwardSlashKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const forwardSlashKeyPressed>()); }

std::unique_ptr<const Action> forwardSlashKeyPressed::clone() const {
    return std::make_unique<const forwardSlashKeyPressed>(); }


std::unique_ptr<const Update> questionMarkKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const questionMarkKeyPressed>()); }

std::unique_ptr<const Action> questionMarkKeyPressed::clone() const {
    return std::make_unique<const questionMarkKeyPressed>(); }


std::unique_ptr<const Update> AKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const AKeyPressed>()); }

std::unique_ptr<const Action> AKeyPressed::clone() const {
    return std::make_unique<const AKeyPressed>(); }


std::unique_ptr<const Update> IKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const IKeyPressed>()); }

std::unique_ptr<const Action> IKeyPressed::clone() const {
    return std::make_unique<const IKeyPressed>(); }


std::unique_ptr<const Update> NKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const NKeyPressed>()); }

std::unique_ptr<const Action> NKeyPressed::clone() const {
    return std::make_unique<const NKeyPressed>(); }


std::unique_ptr<const Update> caretKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const caretKeyPressed>()); }

std::unique_ptr<const Action> caretKeyPressed::clone() const {
    return std::make_unique<const caretKeyPressed>(); }


std::unique_ptr<const Update> aKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const aKeyPressed>()); }

std::unique_ptr<const Action> aKeyPressed::clone() const {
    return std::make_unique<const aKeyPressed>(); }


std::unique_ptr<const Update> hKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const hKeyPressed>()); }

std::unique_ptr<const Action> hKeyPressed::clone() const {
    return std::make_unique<const hKeyPressed>(); }

    
std::unique_ptr<const Update> iKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const iKeyPressed>()); }

std::unique_ptr<const Action> iKeyPressed::clone() const {
    return std::make_unique<const iKeyPressed>(); }

    
std::unique_ptr<const Update> jKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const jKeyPressed>()); }

std::unique_ptr<const Action> jKeyPressed::clone() const {
    return std::make_unique<const jKeyPressed>(); }


std::unique_ptr<const Update> kKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const kKeyPressed>()); }

std::unique_ptr<const Action> kKeyPressed::clone() const {
    return std::make_unique<const kKeyPressed>(); }


std::unique_ptr<const Update> lKeyPressed::visit(Model &m) const { return m.update(std::make_unique<lKeyPressed>()); }

std::unique_ptr<const Action> lKeyPressed::clone() const {
    return std::make_unique<const lKeyPressed>(); }


std::unique_ptr<const Update> nKeyPressed::visit(Model &m) const { return m.update(std::make_unique<nKeyPressed>()); }

std::unique_ptr<const Action> nKeyPressed::clone() const {
    return std::make_unique<const nKeyPressed>(); }


std::unique_ptr<const Update> oKeyPressed::visit(Model &m) const { return m.update(std::make_unique<oKeyPressed>()); }

std::unique_ptr<const Action> oKeyPressed::clone() const {
    return std::make_unique<const oKeyPressed>(); }


std::unique_ptr<const Update> wKeyPressed::visit(Model &m) const { return m.update(std::make_unique<wKeyPressed>()); }

std::unique_ptr<const Action> wKeyPressed::clone() const {
    return std::make_unique<const wKeyPressed>(); }


std::unique_ptr<const Update> escKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const escKeyPressed>()); }

std::unique_ptr<const Action> escKeyPressed::clone() const {
    return std::make_unique<const escKeyPressed>(); }

std::unique_ptr<const Update> backspaceKeyPressed::visit(Model &m) const { return m.update(std::make_unique<const backspaceKeyPressed>()); }

std::unique_ptr<const Action> backspaceKeyPressed::clone() const {
    return std::make_unique<const backspaceKeyPressed>(); }
