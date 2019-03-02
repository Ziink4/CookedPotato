#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment & _env);

private:
    Wt::WLineEdit * m_nameEdit;
    Wt::WText * m_greeting;
};

HelloApplication::HelloApplication(const Wt::WEnvironment & _env)
    : Wt::WApplication(_env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    m_nameEdit = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton * button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    m_greeting = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]
    {
        m_greeting->setText("Hello there, " + m_nameEdit->text());
    };
    button->clicked().connect(greet);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment & env)
    {
      return std::make_unique<HelloApplication>(env);
    });
}