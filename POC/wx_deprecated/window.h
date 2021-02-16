#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif


#include "http_client.h"
#include "data_container.h"
#include "window.h"




// The HelloWorldApp class. This class shows a window
// containing a statusbar with the text "Hello World"

class MyPanel : public wxPanel
{
	
public:
	MyPanel(wxFrame* parent);
	
	Data_container* data;
	void paintEvent(wxPaintEvent & evt);
	void paintNow();
	//void OnTimer(wxTimerEvent& evt);
	void render(wxDC& dc);
	
	// some useful events
	/*
	 void mouseMoved(wxMouseEvent& event);
	 void mouseDown(wxMouseEvent& event);
	 void mouseWheelMoved(wxMouseEvent& event);
	 void mouseReleased(wxMouseEvent& event);
	 void rightClick(wxMouseEvent& event);
	 void mouseLeftWindow(wxMouseEvent& event);
	 void keyPressed(wxKeyEvent& event);
	 void keyReleased(wxKeyEvent& event);
	 */
	
	DECLARE_EVENT_TABLE()
};


class HelloWorldApp : public wxApp
{
public:
	virtual bool OnInit();
	wxFrame* frame;
	MyPanel* drawPane;
};

DECLARE_APP(HelloWorldApp)

#endif // __WINDOW_H__