#include "VmText.h"
#include "Posn.h"

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

bool VmText::ConstVmTextIterator::operator=(const ConstTextIterator &other) const {
    const ConstVmTextIterator &constTextIteratorOther = dynamic_cast<const ConstVmTextIterator&>(other);
    return it == constTextIteratorOther.it;
}

bool VmText::ConstVmTextIterator::operator!=(const ConstTextIterator &other) const {
    const ConstVmTextIterator &constTextIteratorOther = dynamic_cast<const ConstVmTextIterator&>(other);
    return it != constTextIteratorOther.it;
}

bool VmText::ConstVmTextIterator::operator==(const ConstTextIterator &other) const {
    const ConstVmTextIterator &constTextIteratorOther = dynamic_cast<const ConstVmTextIterator&>(other);
    return it == constTextIteratorOther.it;
}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::operator++() {
    ++it;
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {it});
}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::operator--() {
    --it;
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {it});
}

const char &VmText::ConstVmTextIterator::operator*() const {
    return *it;
}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::next() const {
    auto nextIt = it + 1;
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {nextIt});
}

std::unique_ptr<ConstTextIterator> VmText::ConstVmTextIterator::previous() const {
    auto previousIt = it - 1;
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {previousIt});
}

VmText::VmText(): text{""}, numOfLines{0} {}

VmText::VmText(std::string text): text{std::move(text)} {
    size_t newLineCount = 0;
    for (auto it = cbegin(); it->operator!=(*cend().get()); it->operator++()) {
        if (it->operator*() == '\n') ++newLineCount;
    }
    numOfLines = newLineCount;
}

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

std::unique_ptr<ConstTextIterator> VmText::beginAtLine(int ln) const {
    auto it = begin();
    for (int i = 1; i < ln; it->operator++()) {
        if (it->operator*() == '\n') ++i;
    }
    return it;
}

void VmText::advanceToStartOfNextLine(ConstTextIterator &it) const {
    while (it != *end()) {
        if (*it == '\n') {
            ++it;
            return;
        }
        ++it;
    }
}

std::unique_ptr<ConstTextIterator> VmText::goBackToStartOfPreviousLine(ConstTextIterator &it) const {
    bool isOnPreviousLine = false;
    for (; it != *begin(); --it) {
        if (it.previous()->operator*() == '\n') {
            if (isOnPreviousLine) break;
            isOnPreviousLine = true;
        }
    }
    return it.clone();
}

std::unique_ptr<ConstTextIterator> VmText::cbegin() {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.begin()});
};

std::unique_ptr<ConstTextIterator> VmText::cend() {
    return std::unique_ptr<ConstVmTextIterator>(new ConstVmTextIterator {text.end()});
};

bool VmText::isEmpty() const { return text.empty(); }

int VmText::getLength() const { return text.length(); }

int VmText::getNumOfLines() const { return numOfLines; }

VmText::~VmText() {}
