﻿#include "Header.h"
#include <fstream>
#include <wx/notebook.h>
#include <wx/propdlg.h>
#include <wx/bookctrl.h>
#include <wx/string.h>
#include <wx/textfile.h>
OptionFrame::OptionFrame(wxWindow* parent, int ID, wxString name) : wxFrame(parent, ID, name,{0,0},{300,150})
{
    wxArrayString choices;
    wxArrayString choices2;
    choices.Add("Id");
    choices.Add("Title");
    choices.Add("Fulltitle");
    choices.Add("Alternative Title");
    choices.Add("Uploader");
    choices2.Add("Upload Date");
    choices2.Add("Release Date");
    choices2.Add("Release Year");
    choices2.Add("Channel Name");
    choices2.Add("Duration"); // not in seconds
    
    Center();
  //  check = new wxButton(this, 169, "Check", { 0,150 });
    FileArg = new wxCheckListBox(this, FileArgID, { 0,20 }, { 150,90 }, choices);
    FileArg2 = new wxCheckListBox(this, FileArg2ID, { 150,20 }, { 150,90 }, choices2);
    
    wxStaticText* Exp = new wxStaticText(this, 992, "The order in which u select matters", { 0,0 });
   
}

void OptionFrame::OnButton(wxCommandEvent& event)
{
    wxArrayInt checki;
    FileArg->GetCheckedItems(checki);

}

void OptionFrame::OnChoice(wxCommandEvent& event)
{
    switch (event.GetInt())
    {
    case 0:
        args = args+ "%(id)s ";
        break;
    case 1:
        args = args + "%(title)s ";
        break;
    case 2:
        args = args + "%(fulltitle)s ";
        break;
    case 3:
        args = args + "%(alt_title)s ";
        break;
    case 4:
        args = args + "%(uploader)s ";
        break;
    }

}

void OptionFrame::OnChoice2(wxCommandEvent& event)
{
    switch (event.GetInt())
    {
    case 0:
        args = args + "%(upload_date)s ";
        break;
    case 1:
        args = args + "%(release_date)s ";
        break;
    case 2:
        args = args + "%(release_year)s ";
        break;
    case 3:
        args = args + "%(channel)s ";
        break;
    case 4:
        args = args + "%(duration_string)s ";
        break;
    }
}


std::string OptionFrame::GetChoices()
{
    return args;
}

OptionFrame::~OptionFrame()
{
    std::fstream argfile;
    argfile.open("args", std::fstream::out);
        argfile << args;
}

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("Youtube-dlp GUI"), { 1,700 }, { 700,700 })
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
    LinkBox = new wxTextCtrl(this, LinkBoxID, " ", { 0,0 }, { 400,315 },wxTE_PROCESS_ENTER | wxTE_MULTILINE | wxHSCROLL);
    OutputBox = new wxTextCtrl(this, OutputBoxID, " ", { 0,352  }, { 700,260 }, wxTE_READONLY | wxTE_MULTILINE | wxHSCROLL);
    std::fstream argfile;
    argfile.open("args",std::fstream::out);
    argfile << " %(title)s.%(ext)s";
    argfile.close();
    {
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
        AdditionalArgs = new wxCheckListBox(this, AdditionalArgsID, { 400,35 }, { 280,100 }, args);
    }
    refresh.SetOwner(this, TimerID);
    
    

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

void MainFrame::OnTimer(wxTimerEvent& event)
{
   
}  

void MainFrame::OnSize(wxSizeEvent &event)
{


}
void MainFrame::OnButton(wxCommandEvent &event)
{
  
    std::stringstream cmd;
    SetStatusText("Downloading");
    cmd = CommandBuilder();
    logfile.Open("out.o");
 
    if (!system(cmd.str().c_str()))
    {

        wxMessageBox("Program Ran Succesfully", "Good stuff");

    }
    else
    {
        wxMessageBox("failed to convert ", "Arrggh");
    }
    int cnt = logfile.GetLineCount();

    for (int i = 0; i < logfile.GetLineCount(); i++)
    {
        OutputBox->AppendText(logfile.GetLine(i));
        OutputBox->AppendText("\n");
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
    AdditionalOptions = 1;
    OptionWindow->Show();


}
std::stringstream MainFrame::CommandBuilder()
{
    std::stringstream cmd;
    cmd << "yt-dlp > out.o" << " " << "-P" << " " << '"'<< DlFolder->GetPath()<<'"' << " ";
    for (int i = 0; i < LinkBox->GetNumberOfLines(); i++)
        cmd <<'"'<<LinkBox->GetLineText(i) <<'"' << " ";
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
    if (FormatSelection->GetSelection() < 4)
        cmd << "--embed-subs " << "-S "<< '"' << "res" << res << '"'<<" ";
    cmd << "--embed-thumbnail " << "--embed-metadata" << " "<<" ";
    argfile.open("args", std::fstream::in);
    char args[100];
    argfile.getline(args, 100);
    wxString fin(args);
    cmd << "-o " <<'"'<<fin<<'"'<<" ";
    if (AdditionalArgs->IsChecked(0)) cmd <<" "<<"-k" << " ";
    if (AdditionalArgs->IsChecked(1)) cmd <<" "<<"--write-subs" << " ";
    if (AdditionalArgs->IsChecked(2)) cmd <<" "<<"--write-thumbnail" << " ";
    if (AdditionalArgs->IsChecked(3)) cmd <<" "<<  "--split-chapters" << " ";
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
EVT_CHECKLISTBOX(FileArgID,OptionFrame::OnChoice)
EVT_CHECKLISTBOX(FileArg2ID, OptionFrame::OnChoice2)
END_EVENT_TABLE()
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_TIMER(TimerID, MainFrame::OnTimer)
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