#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment & env);

private:
    Wt::WLineEdit * nameEdit;
    Wt::WText * greeting;
};

HelloApplication::HelloApplication(const Wt::WEnvironment & env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton * button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]
    {
        greeting->setText("Hello there, " + nameEdit->text());
    };
    button->clicked().connect(greet);
}

int main(int argc, char ** argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment & env)
    {
      return std::make_unique<HelloApplication>(env);
    });
}