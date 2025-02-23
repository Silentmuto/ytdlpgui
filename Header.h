
#pragma once
#include <wx/wx.h>
#include <wx/filepicker.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
#include <wx/textfile.h>
#include <wx/timer.h>
#include "IDs.h"
#include "SecondaryFrames.h"
class program : public wxApp
{
public:
	virtual bool OnInit();


	

};
void RunCommand(std::string command);

class MainFrame : public wxFrame
{
	wxTextCtrl* LinkBox;
	wxButton* DownloadButton;
	wxTextCtrl* OutputBox;
	wxChoice* FormatSelection;
	wxCheckListBox* AdditionalArgs;
	wxDirPickerCtrl* DlFolder;
	wxChoice* ResSelect;
	OptionFrame* OptionWindow;
	std::fstream argfile;
	wxTextFile logfile;
	wxTimer refresh;
	int AdditionalOptions = 0;
	PlaylistFrame* PlaylistOptions;
	DECLARE_EVENT_TABLE()
public:
	
	MainFrame();
	void OnAbout(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnSize(wxSizeEvent& event);
	void OnButton(wxCommandEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnOption(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnUpdate(wxCommandEvent& event);

	std::stringstream CommandBuilder();
};
class HTUFrame : public wxFrame
{

};

