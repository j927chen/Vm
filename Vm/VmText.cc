#include "VmText.h"

VmText::VmTextIterator::VmTextIterator(std::string::iterator it): it{it} {}

std::unique_ptr<TextIterator> VmText::VmTextIterator::clone() const {
    return std::unique_ptr<VmTextIterator>(new VmTextIterator {it});
}

bool VmText::VmTextIterator::operator!=(const TextIterator &other) const {
    const VmTextIterator &textIteratorOther = dynamic_cast<const VmTextIterator&>(other);
    return it != textIteratorOther.it;
}

std::unique_ptr<TextIterator> VmText::VmTextIterator::operator++() {
    ++it;
    return std::unique_ptr<VmTextIterator>(new VmTextIterator {it});
}

char &VmText::VmTextIterator::operator*() const {
    return *it;
}

VmText::ConstVmTextIterator::ConstVmTextIterator(std::string::const_iterator it): it{it} {}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::clone() const {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {it});
}

bool VmText::ConstVmTextIterator::operator!=(const ConstTextIterator &other) const {
    const ConstVmTextIterator &constTextIteratorOther = dynamic_cast<const ConstVmTextIterator&>(other);
    return it != constTextIteratorOther.it;
}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::operator++() {
    ++it;
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {it});
}

const char &VmText::ConstVmTextIterator::operator*() const {
    return *it;
}

VmText::VmText(std::string text): text{std::move(text)} {}

std::unique_ptr<TextIterator> VmText::begin() {
    return std::unique_ptr<VmTextIterator>(new VmTextIterator {text.begin()});
}
std::unique_ptr<TextIterator> VmText::end() {
    return std::unique_ptr<VmTextIterator>(new VmTextIterator {text.end()});
}

std::unique_ptr<ConstTextIterator> VmText::begin() const {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.begin()});
}
std::unique_ptr<ConstTextIterator> VmText::end() const {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.end()});
}

std::unique_ptr<ConstTextIterator> VmText::cbegin() {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.begin()});
};

std::unique_ptr<ConstTextIterator> VmText::cend() {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.end()});
};

VmText::~VmText() {}
