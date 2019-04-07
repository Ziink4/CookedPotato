#pragma once

#include <Wt/WApplication.h>

namespace ui
{

class hello_application : public Wt::WApplication
{
public:
    hello_application(const Wt::WEnvironment & env);

private:
    Wt::WLineEdit * name_edit;
    Wt::WText * greeting;
};

} // namespace ui
