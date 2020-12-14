#ifndef VmModel_h
#define VmModel_h

#include <string>

#include "Model.h"
#include "Searchable.h"

class Editor;
class Reader;
class Writer;
class Cursor;
class Posn;

enum VM_MODE {
    COMMAND, COMMAND_ENTER, INSERT, REPLACE,
};

class VmModel: public Model {
    
    std::string fileName;
    VM_MODE mode;
    std::unique_ptr<Editor> editor;
    std::unique_ptr<Cursor> cursor;
    std::unique_ptr<Reader> reader;
    std::unique_ptr<Writer> writer;
    std::string typedCommand;
    int multiplier;
    
    std::unique_ptr<const Update> pushBackCharInTypedCommand(char c);
    std::unique_ptr<const Update> updateForTypedCommand();
    std::unique_ptr<const Update> updateForSearchPatternCommand(const Searchable::SearchResult &result);
    
    
    class colonCommand {
    public:
        virtual  std::unique_ptr<const Update> visit(VmModel &m) const = 0;
        virtual ~colonCommand();
    };
    
    std::unique_ptr<const colonCommand> parseColonCommand() const;
    std::unique_ptr<const Update> parseForwardSlashCommand();
    std::unique_ptr<const Update> parseQuestionMarkCommand();
    
    class colon_q: public colonCommand {
    public:
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_q();
    };
    
    class colon_q_exclaimation_mark: public colonCommand {
    public:
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_q_exclaimation_mark();
    };
    
    class colon_w: public colonCommand {
    public:
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_w();
    };
    
    class colon_wq: public colonCommand {
    public:
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_wq();
    };
    
    class colon_r: public colonCommand {
    public:
        const std::string fileName;
        colon_r(const std::string fileName);
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_r();
    };
    
    class colon_dollar_sign: public colonCommand {
    public:
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_dollar_sign();
    };
    
    class colon_number: public colonCommand {
    public:
        int ln;
        colon_number(int ln);
        std::unique_ptr<const Update> visit(VmModel &m) const override;
        ~colon_number();
    };
    
    class parse_error{};
    
    std::unique_ptr<const Update> update(colon_q c);
    std::unique_ptr<const Update> update(colon_q_exclaimation_mark c);
    std::unique_ptr<const Update> update(colon_w c);
    std::unique_ptr<const Update> update(colon_wq c);
    std::unique_ptr<const Update> update(colon_r c);
    std::unique_ptr<const Update> update(colon_dollar_sign c);
    std::unique_ptr<const Update> update(colon_number c);
    
    std::unique_ptr<const colon_r> parseColonRCommand() const;
    
    std::unique_ptr<const Update> defaultUpdate();
    std::unique_ptr<const Update> defaultInsertUpdate(const Posn previousCursorPosn);
    std::unique_ptr<const Update> noUpdate();

public:
    VmModel();
    VmModel(std::string filename);
    
    std::unique_ptr<const Update> update(std::unique_ptr<const otherKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const numberKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const enterKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const colonKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const forwardSlashKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const questionMarkKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const hKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const iKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const jKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const kKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const lKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const escKeyPressed> a) override;
    std::unique_ptr<const Update> update(std::unique_ptr<const backspaceKeyPressed> a) override;
    const std::string &getFileName() const override;
    const Editor &getEditor() const override;
    const Cursor &getCursor() const override;
    
    ~VmModel();
    
};

#endif
