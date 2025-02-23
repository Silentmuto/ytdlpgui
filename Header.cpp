#include "Header.h"
#include <fstream>
#include <wx/notebook.h>
#include <wx/propdlg.h>
#include <wx/bookctrl.h>
#include <wx/string.h>
#include <wx/textfile.h>
#include <thread>


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("Youtube-dlp GUI"), { 1,700 }, { 700,700 })
{   //Frame Init
    wxArrayString choices;
    wxArrayString args;
    wxArrayString res;
    //choices/args creation
    {  choices.Add("Video");
   // choices.Add("avi");
   // choices.Add("flv");
   // choices.Add("gif");
    choices.Add("mkv");
   // choices.Add("mov");
    choices.Add("mp4");
    choices.Add("Audio");
    choices.Add("aac");
    choices.Add("alac");
    choices.Add("flac");
    choices.Add("m4a");
    choices.Add("mp3");
    choices.Add("opus");
    choices.Add("vorbis");
    choices.Add("wav");
    args.Add("Keep Video(If u selected an audio format) ");
    args.Add("Write subtitle file if possible");
    args.Add("Put thumbnail into separate file");
    args.Add("Split Video based on Chapters(Separate File)");
    args.Add("Add sponsorblock categories");
    args.Add("Download Livestream from the start");
    args.Add("Write video description into a separate file");
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
    PlaylistOptions = new PlaylistFrame(this, 330193, wxT("Playlist Options"));
    PlaylistOptions->Show();
    OptionMenu->Append(FileOptionID, wxT("File Formatting"), wxT("Select filename formating options"));
    OptionMenu->Append(PlaylistOptionID, wxT("Playlist Options"), wxT("Options for costumizing playlist downloads"));
    MainMenu->Append(wxID_EXIT, wxT("Exit"), wxT(":("));
    MainMenu->Append(UpdateID, wxT("Update"), "Update Youtube DLP to the newest version");
    HelpMenu->Append(wxID_ABOUT, wxT("How to use"), wxT("Instruction on how to use the program "));
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
    argfile.open("FileFormat.args",std::fstream::out);
    argfile << " %(title)s.%(ext)s";
    argfile.close();
    {
        wxStaticText* Dl = new wxStaticText(this, 149, "Click Browse to select the download directory", { 0,315 });
        DlFolder = new wxDirPickerCtrl(this, 149, " ", "Browse", { 0,330 }, { 280,20 });


        DownloadButton = new wxButton(this, DownloadButtonID, "Download", { 500,180 });

        wxStaticText* FS = new wxStaticText(this, 149, "Select Format ", { 400,10 });
        FormatSelection = new wxChoice(this, FormatSelectionID, { 475,10 }, { 50,25 }, choices, 0L, wxDefaultValidator, "Format");
        FormatSelection->SetSelection(1);
        if (FormatSelection->GetSelection() == 0)
        {
            FormatSelection->SetSelection(6);
        }
        wxStaticText* RS = new wxStaticText(this, 149, "Select Resolution", { 400,155 });
        ResSelect = new wxChoice(this, ResSelectID, { 492,155 }, { 50,25 }, res);
        ResSelect->SetSelection(0);
        AdditionalArgs = new wxCheckListBox(this, AdditionalArgsID, { 400,35 }, { 280,120 }, args);
    }
    refresh.SetOwner(this, TimerID);
    
    

}   
void MainFrame::OnUpdate(wxCommandEvent& event)
{
    std::string command;
    command = "yt-dlp --update";
    system(command.c_str());
}
void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(wxT("Paste the desired link/links into the upper box \n Select the desired download directory using the Browse button \n Select a format using the format selector and select any additional options from the box below the format selection or from the options menu \n Once your done, press the download button and simply wait until u get the finished pop-up. Dont panic if the program freezes, as it'll remain freezed for the duration. \n Supports the same links as yt-dlp does, Further costumization for playlists and other features will be released in the future\n Lower Box will contain the logs once the program finished running\n Livestream downloads from the current timestamp by default"), wxT("wth"), wxOK, this);

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

void RunCommand(std::string command)
{
    if (!system(command.c_str()))
    {
        wxMessageBox("Program Ran Succesfully", "Succes");
    }
    else
    {
        wxMessageBox("The program encountered an error download one or more songs,please check for any missing songs", "Error");
    }
   
}

void MainFrame::OnSize(wxSizeEvent &event)
{


}
void MainFrame::OnButton(wxCommandEvent &event)
{

    std::stringstream cmd;
    SetStatusText("Downloading");
    cmd = CommandBuilder();

    std::thread ytdlp(RunCommand, cmd.str());
    ytdlp.detach();
    SetStatusText("Downloading");

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
        FormatSelection->SetSelection(6);
    }
    if (FormatSelection->GetSelection() == 7)
    {
        FormatSelection->SetSelection(12);
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
    bool IsPlaylist=0;
    std::string LineText;
    cmd << "yt-dlp > out.o" << " " << "-P" << " " << '"'<< DlFolder->GetPath()<<'"' << " ";
    for (int i = 0; i < LinkBox->GetNumberOfLines(); i++)
    {
        LineText = LinkBox->GetLineText(i);
        cmd << '"' << LineText << '"' << " ";
        if ( !IsPlaylist  && (LineText.find("list") != std::string::npos))
        {
            IsPlaylist = 1;
        }
    }

    switch (FormatSelection->GetSelection())
    {
  /*  case 1:
        cmd << "--remux-video" << " " << "avi" << " ";
        break;
    case 2:
        cmd << "--remux-video" << " " << "flv" << " ";
        break;
    case 3:
        cmd << "--remux-video" << " " << "gif" << " "; */
        break;
    case 4:
        cmd << "--remux-video" << " " << "mkv" << " ";
        break;
  //  case 5:
     //   cmd << "--remux-video" << " " << "mov" << " ";
     //   break;
    case 6:
        cmd << "--remux-video" << " " << "mp4" << " ";
        break;
    case 8:
        cmd << "-x" << " " << "--audio-format" << " " << "aac" << " ";
        break;
    case 9:
        cmd << "-x" << " " << "--audio-format" << " " << "alac" << " ";
        break;
    case 10:
        cmd << "-x" << " " << "--audio-format" << " " << "flac" << " ";
        break;
    case 11:
        cmd << "-x" << " " << "--audio-format" << " " << "m4a" << " ";
        break;
    case 12:
        cmd << "-x" << " " << "--audio-format" << " " << "mp3" << " ";
        break;
    case 13:
        cmd << "-x" << " " << "--audio-format" << " " << "opus" << " ";
        break;
    case 14:
        cmd << "-x" << " " << "--audio-format" << " " << "vorbis" << " ";
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
    if (FormatSelection->GetSelection() < 7)
        cmd << "--embed-subs " << "-S "<< '"' << "res" << res << '"'<<" ";
    cmd << "--embed-metadata" << " "<<" ";
    argfile.open("FileFormat.args", std::fstream::in);
    char args[100];
    argfile.getline(args, 100);
    wxString fin(args);
    if (IsPlaylist)
    {
        std::fstream PArgFile;
        std::string PArgs;
        char aux[100];
        PArgFile.open("Playlist.args", std::fstream::in);
        PArgFile.getline(aux, 100);
        PArgs = aux;
        cmd << PArgs << " ";
    }
    cmd << "-o " <<'"'<<fin<<'"'<<" ";
    if (AdditionalArgs->IsChecked(0)) cmd <<" "<<"-k" << " ";
    if (AdditionalArgs->IsChecked(1)) cmd <<" "<<"--write-subs" << " ";
    if (AdditionalArgs->IsChecked(2)) cmd <<" "<<"--write-thumbnail" << " ";
    if (AdditionalArgs->IsChecked(3)) cmd <<" "<<  "--split-chapters" << " ";
    if (AdditionalArgs->IsChecked(4)) cmd << "--sponsorblock-mark all" << " ";
    if (AdditionalArgs->IsChecked(5)) cmd << "--live-from-start ";
    if (AdditionalArgs->IsChecked(6)) cmd << "--write-description ";
    std::fstream log;
    std::string filename;
    log.open("log.txt", std::fstream::out | std::fstream::app);
    log << cmd.str();
    log << std::endl;
    log.close();
    return cmd;
}


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_TIMER(TimerID, MainFrame::OnTimer)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(UpdateID, MainFrame::OnUpdate)
EVT_MENU(FileOptionID,MainFrame::OnOption)
EVT_SIZE(MainFrame::OnSize)
EVT_BUTTON(DownloadButtonID, MainFrame::OnButton)
EVT_CHOICE(FormatSelectionID,MainFrame::OnChoice)
END_EVENT_TABLE()











