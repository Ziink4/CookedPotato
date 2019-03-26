#include <ui/hello_application.h>

#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

HelloApplication::HelloApplication(const Wt::WEnvironment & env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));

    name_edit = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    Wt::WPushButton * button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));

    root()->addWidget(std::make_unique<Wt::WBreak>());

    greeting = root()->addWidget(std::make_unique<Wt::WText>());
    auto greet = [this]
    {
        greeting->setText("Hello there, " + name_edit->text());
    };
    button->clicked().connect(greet);
}
