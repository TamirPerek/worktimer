#include <wx/wx.h>
#include <wx/wxprec.h>

#include "Dialogs/MainWindow.h"

#include <iostream>
#include <string>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    auto frame = new Dialogs::MainWindow(nullptr);
#if defined(__MINGW32__) || defined(WIN32)
    frame->SetIcon(wxICON(aaaa));
#endif
    frame->Show(true);
    return true;
}
