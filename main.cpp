#include <iostream>
#include <string>
#include <algorithm> //std::reverse.

class Text {
public:
    virtual void render(const std::string& data) {
        std::cout << data;
    }
    virtual ~Text() = default;
};

class DecoratedText : public Text {
protected:
    Text* text_;
public:
    explicit DecoratedText(Text* text) : text_(text) {}

    //Деструктор для предотвращения утечек памяти.
    ~DecoratedText() override {
        delete text_;
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}

    void render(const std::string& data) override {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(Text* text) : DecoratedText(text) {}

    void render(const std::string& href, const std::string& data) {
        std::cout << "<a href=" << href << ">";
        text_->render(data);
        std::cout << "</a>";
    }

    void render(const std::string& data) override {
        text_->render(data);
    }
};

int main() {
    //Paragraph.
    std::cout << "Paragraph" << std::endl;
    Text* p_block = new Paragraph(new Text());
    p_block->render("Hello world");
    std::cout << std::endl;
    delete p_block;

    //Reversed.
    std::cout << "\nReversed" << std::endl;
    Text* r_block = new Reversed(new Text());
    r_block->render("Hello world");
    std::cout << std::endl;
    delete r_block;

    //Link.
    std::cout << "\nLink" << std::endl;
    Link* l_block = new Link(new Text());
    l_block->render("netology.ru", "Hello world");
    std::cout << std::endl;
    delete l_block;

    //Комбинация декораторов Paragraph и Reversed.
    std::cout << "\nParagraph and Reversed" << std::endl;
    Text* combo_block = new Paragraph(new Reversed(new Text()));
    combo_block->render("Hello world");
    std::cout << std::endl;
    delete combo_block;

    return 0;
}