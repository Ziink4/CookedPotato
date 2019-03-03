#pragma once

#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment & env);

private:
    Wt::WLineEdit * name_edit;
    Wt::WText * greeting;
};
