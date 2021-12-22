#include <wx/wx.h>
#include <wx/wxprec.h>

#include "Dialogs/MainWindow.h"
#include "Exception.h"

#include <iostream>
#include <string>
#include <filesystem>

class MyApp : public wxApp
{
public:
    bool OnInit() final;
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    try
    {
        std::filesystem::current_path(std::filesystem::path{static_cast<std::string>(argv[0])}.parent_path());

        auto frame = new Dialogs::MainWindow(nullptr);
#if defined(__MINGW32__) || defined(WIN32)
        frame->SetIcon(wxICON(aaaa));
#endif
        frame->Show(true);
        return true;
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}
