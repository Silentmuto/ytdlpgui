#include "Header.h"
#include <fstream>
#include <wx/notebook.h>
#include <wx/propdlg.h>
#include <wx/panel.h>
#include <wx/bookctrl.h>
#include <wx/mediactrl.h>
#include <wx/string.h>
OptionFrame::OptionFrame(wxWindow* parent, int ID, wxString name) : wxFrame(parent, ID, name,{0,0},{600,200})
{
    wxArrayString choices;
    wxArrayString choices2;
    choices.Add("Id");
    choices.Add("Title");
    choices.Add("Fulltitle");
    choices.Add("Alternative Title");
    choices.Add("Uploader");
    choices.Add("Upload Timestamp");
    choices.Add("Upload Date");
    choices2.Add("Release TimeStamp");
    choices2.Add("Release Date");
    choices2.Add("Release Year");
    choices2.Add("Channel Name");
    choices2.Add("Duration"); // not in seconds
    choices2.Add("Age Limit");
    choices2.Add("Tags");
    
    Center();
    check = new wxButton(this, 169, "Check", { 0,140 });
    FileArg = new wxCheckListBox(this, FileArgID, { 0,0 }, { 300,130 }, choices);
    FileArg2 = new wxCheckListBox(this, FileArg2ID, { 299,0 }, { 300,130 }, choices2);
   
    
   
}

void OptionFrame::OnButton(wxCommandEvent& event)
{
    wxArrayInt checki;
    FileArg->GetCheckedItems(checki);

}

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("Youtube-dlp GUI"), { 700,700 }, { 700,450 })
{   //Frame Init
    wxArrayString choices;
    wxArrayString args;
    wxArrayString res;
    //choices/args creation
    {  choices.Add("Video");
    choices.Add("mp4");
    choices.Add("mkv");
    choices.Add("webm");
    choices.Add("Audio");
    choices.Add("mp3");
    choices.Add("flac");
    choices.Add("wav"); 
    args.Add("Keep Video(If u selected an audio format ");
    args.Add("Write subtitle file if possible");
    args.Add("Put thumbnail into separate file");
    args.Add("Split Video based on Chapters(Separate File");
    args.Add("Add sponsorblock categories");
    res.Add("Max");
    res.Add("1440");
    res.Add("1080");
    res.Add("720");
    res.Add("480");
    res.Add("144");
    
    }
    // FrameDef
    { Center();
    
    wxMenu* MainMenu = new wxMenu;
    wxMenu* HelpMenu = new wxMenu;
    wxMenu* OptionMenu = new wxMenu;
    OptionWindow = new OptionFrame(this, 330192, wxT("OptionWindow"));
    OptionMenu->Append(FileOptionID, wxT("File Formatting"), wxT("Select filename formating options"));
    MainMenu->Append(wxID_EXIT, wxT("Exit"), wxT(":("));
    HelpMenu->Append(wxID_ABOUT, wxT("About"), wxT("womp womp "));
    wxMenuBar* MenuBar = new wxMenuBar;
    MenuBar->Append(MainMenu, "Main Menu");
    MenuBar->Append(HelpMenu, "Help");
    MenuBar->Append(OptionMenu, "Options");
    CreateStatusBar(1);
    SetStatusText("Waiting for input");
    SetMenuBar(MenuBar); }
    //UI stuff
    LinkBox = new wxTextCtrl(this, LinkBoxID, " ", { 0,0 }, { 400,315 },wxTE_PROCESS_ENTER | wxTE_MULTILINE);
  //  OutputBox = new wxTextCtrl(this, OutputBoxID, " ", { 0,300 }, { 400,315 }, wxTE_READONLY);
    {
        SetBackgroundColour(*wxGREEN);
        wxStaticText* Dl = new wxStaticText(this, 149, "Click Browse to select the download directory", { 0,315 });
        DlFolder = new wxDirPickerCtrl(this, 149, " ", "Browse", { 0,330 }, { 280,20 });


        DownloadButton = new wxButton(this, DownloadButtonID, "Download", { 500,160 });

        wxStaticText* FS = new wxStaticText(this, 149, "Select Format ", { 400,10 });
        FormatSelection = new wxChoice(this, FormatSelectionID, { 475,10 }, { 50,25 }, choices, 0L, wxDefaultValidator, "Format");
        FormatSelection->SetSelection(1);
        if (FormatSelection->GetSelection() == 0)
        {
            FormatSelection->SetSelection(1);
        }
        wxStaticText* RS = new wxStaticText(this, 149, "Select Resolution", { 400,135 });
        ResSelect = new wxChoice(this, ResSelectID, { 492,135 }, { 50,25 }, res);
        ResSelect->SetSelection(0);
        AdditionalArgs = new wxCheckListBox(this, AdditionalArgsID, { 400,35 }, { 300,100 }, args);
    }
    

}
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(wxT("Youtube-dlp gui made by skips"), wxT("wth"), wxOK, this);

}
void MainFrame::OnExit(wxCommandEvent &event)
{
    Close();
}
bool program::OnInit()
{
    MainFrame* MainWindow = new MainFrame();
    MainWindow->Show();
    return true;
}
void MainFrame::OnSize(wxSizeEvent &event)
{


}
void MainFrame::OnButton(wxCommandEvent &event)
{
    std::stringstream cmd;
    SetStatusText("Downloading");
    cmd = CommandBuilder();
    if (!system(cmd.str().c_str()))
    {

        wxMessageBox("Program Ran Succesfully", "Good stuff");
    }
    else
    {
        wxMessageBox("failed to convert ", "Arrggh");
    }
    SetStatusText("ZZZ");
}
void MainFrame::OnChoice(wxCommandEvent& event)
{
    if (FormatSelection->GetSelection() == 0)
    {
        FormatSelection->SetSelection(1);
    }
    if (FormatSelection->GetSelection() == 4)
    {
        FormatSelection->SetSelection(5);
    }
}
void MainFrame::OnOption(wxCommandEvent& event)
{
    
    
    OptionWindow = new OptionFrame(this, 330192, wxT("OptionWindow"));
    OptionWindow->Show();


}
std::stringstream MainFrame::CommandBuilder()
{
    std::stringstream cmd;
    cmd << "yt-dlp" << " " << "-P" << " " << '"'<< DlFolder->GetPath()<<'"' << " ";
    for (int i = 0; i < LinkBox->GetNumberOfLines(); i++)
        cmd << LinkBox->GetLineText(i) << " ";
    switch (FormatSelection->GetSelection())
    {
    case 2:
        cmd << "--remux-video" << " " << "mkv"<<" ";
        break;

    case 3:
        cmd << "--remux-video" << " " << "webm" << " ";
        break;
    case 5:
        cmd << "-x" << " " << "--audio-format"<<" "<< "mp3"<<" ";
        break;
    case 6:
        cmd << "-x" << " " << "--audio-format" << " " << "flac" << " ";
        break;
    case 7:
        cmd << "-x" << " " << "--audio-format" << " " << "wav" << " ";
        break;
    }
    int res;
    switch (ResSelect->GetSelection())
    {
    case 0:
        res = 2160;
        break;
    case 1:
        res = 1440;
        break;
    case 2:
        res = 1080;
        break;
    case 3:
        res = 720;
        break;
    case 4:
        res = 480;
        break;
    case 5:
        res = 144;
        break;
    }
   
    cmd << "--embed-thumbnail" << " " << "--embed-subs" << " " << "-S " << '"'<<"res" <<res<< '"'<< " "<< "--embed-metadata"<<" "<<"-o " << '"' << "%(title)s" << '"';
    if (AdditionalArgs->IsChecked(0)) cmd << "-k" << " ";
    if (AdditionalArgs->IsChecked(1)) cmd << "--write-subs" << " ";
    if (AdditionalArgs->IsChecked(2)) cmd << "--write-thumbnail" << " ";
    if (AdditionalArgs->IsChecked(3)) cmd << "--split-chapters" << " ";
    if (AdditionalArgs->IsChecked(4)) cmd << "--sponsorblock-mark all" << " ";
    std::fstream log;
    std::string filename;
    log.open("log.txt", std::fstream::out | std::fstream::app);
    log << cmd.str();
    log << std::endl;
    log.close();
    return cmd;
}

BEGIN_EVENT_TABLE(OptionFrame, wxFrame)
EVT_BUTTON(169, OptionFrame::OnButton)
END_EVENT_TABLE()
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(FileOptionID,MainFrame::OnOption)
EVT_SIZE(MainFrame::OnSize)
EVT_BUTTON(DownloadButtonID, MainFrame::OnButton)
EVT_CHOICE(FormatSelectionID,MainFrame::OnChoice)
END_EVENT_TABLE()

/*
std::stringstream stream;
stream << "\"C:\\Tests\\SO Question\\bin\\Release\\HelloWorld.exe\""
       << " " // don't forget a space between the path and the arguments
       << "myargument";
system(stream.str().c_str());
*/