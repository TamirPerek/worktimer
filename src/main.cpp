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
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    try
    {
        auto frame = new Dialogs::MainWindow(nullptr);
#if defined(__MINGW32__) || defined(WIN32)
        frame->SetIcon(wxICON(aaaa));
#endif

        for(int i = 0; i < argc; i++)
        {
            std::cout << "Argument: " << i << " | " << argv[i] << '\n';
        }
        std::cout << "Current Path: " << std::filesystem::current_path().string() << '\n';
        std::cout << "Path: " << std::filesystem::path{static_cast<std::string>(argv[0])}.string() << '\n';

        std::filesystem::current_path(std::filesystem::path{static_cast<std::string>(argv[0])}.parent_path());

        frame->Show(true);
        return true;
    }
    catch (...)
    {
        Exception::handle();
        return false;
    }
}
