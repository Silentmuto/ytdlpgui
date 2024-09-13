#pragma once
#include <wx/wx.h>
#include <wx/filepicker.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
class program : public wxApp
{
public:
	virtual bool OnInit();

};
class OptionFrame : public wxFrame
{
	wxCheckListBox* FileArg;
	wxCheckListBox* FileArg2;
	  wxButton* check;
	  std::string args;
	DECLARE_EVENT_TABLE();
public:
	OptionFrame(wxWindow* parent = NULL, int ID=330192, wxString name="Options");
	void OnButton(wxCommandEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnChoice2(wxCommandEvent& event);
	std::string GetChoices();
};
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
	int AdditionalOptions = 0;
	DECLARE_EVENT_TABLE()
public:
	
	MainFrame();
	void OnAbout(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	void OnSize(wxSizeEvent& event);
	void OnButton(wxCommandEvent& event);
	void OnChoice(wxCommandEvent& event);
	void OnOption(wxCommandEvent& event);
	std::stringstream CommandBuilder();
};

enum ID {
	TestButton = 0,
	LinkBoxID,
	DownloadButtonID,
	OutputBoxID,
	FormatSelectionID,
	AdditionalArgsID,
	ResSelectID,
	FileOptionID,
	OptionWindowID,
	FileArgID,
	FileArg2ID
};	