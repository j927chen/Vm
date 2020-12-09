#ifndef VmModel_h
#define VmModel_h

#include "Model.h"

class Text;
class Reader;
class Writer;

class VmModel: public Model {
    
    std::unique_ptr<Text> text;
    std::unique_ptr<Reader> reader;
    std::unique_ptr<Writer> writer;
    
public:
    VmModel(std::unique_ptr<Text> text, std::unique_ptr<Reader> reader, std::unique_ptr<Writer> writer);
    std::unique_ptr<const Update> update(const unknownKeyPressed &a) override;
    std::unique_ptr<const Update> update(const hKeyPressed &a) override;
    std::unique_ptr<const Update> update(const escKeyPressed &a) override;
    
    const Text &getText() override;
    ~VmModel();
};

#endif
