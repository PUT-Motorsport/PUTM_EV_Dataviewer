#include "window.h"

#define TIMER_ID 1


//Most of the code here is (for now) HEAVILY INSPIRED on
//https://wiki.wxwidgets.org/Drawing_on_a_panel_with_a_DC

BEGIN_EVENT_TABLE(MyPanel, wxPanel)
// some useful events
/*
EVT_MOTION(MyPanel::mouseMoved)
EVT_LEFT_DOWN(MyPanel::mouseDown)
EVT_LEFT_UP(MyPanel::mouseReleased)
EVT_RIGHT_DOWN(MyPanel::rightClick)
EVT_LEAVE_WINDOW(MyPanel::mouseLeftWindow)
EVT_KEY_DOWN(MyPanel::keyPressed)
EVT_KEY_UP(MyPanel::keyReleased)
EVT_MOUSEWHEEL(MyPanel::mouseWheelMoved)
*/
// catch paint events
EVT_PAINT(MyPanel::paintEvent)
END_EVENT_TABLE()


// some useful events
/*
void MyPanel::mouseMoved(wxMouseEvent& event) {}
void MyPanel::mouseDown(wxMouseEvent& event) {}
void MyPanel::mouseWheelMoved(wxMouseEvent& event) {}
void MyPanel::mouseReleased(wxMouseEvent& event) {}
void MyPanel::rightClick(wxMouseEvent& event) {}
void MyPanel::mouseLeftWindow(wxMouseEvent& event) {}
void MyPanel::keyPressed(wxKeyEvent& event) {}
void MyPanel::keyReleased(wxKeyEvent& event) {}
*/

MyPanel::MyPanel(wxFrame* parent) : wxPanel(parent)
{
}

/*
* Called by the system of by wxWidgets when the panel needs
* to be redrawn. You can also trigger this call by
* calling Refresh()/Update().
*/

void MyPanel::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

/*
* Alternatively, you can use a clientDC to paint on the panel
* at any time. Using this generally does not free you from
* catching paint events, since it is possible that e.g. the window
* manager throws away your drawing when the window comes to the
* background, and expects you will redraw it when the window comes
* back (by sending a paint event).
*
* In most cases, this will not be needed at all; simply handling
* paint events and calling Refresh() when a refresh is needed
* will do the job.
*/
void MyPanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
	cout<<"Hey, I'm Bob and I like to print stuff"<<endl;
}

//void MyPanel::OnTimer(wxTimerEvent& evt)
//{
//	if((this->data)->get_data_flag()==true)
//	{
//		cout<<"Peek: "<<(this->data)->peek_a()<<" "<<(this->data)->peek_b()<<endl;
//		(this->data)->pull_down_data_flag();
//		stringstream a;
//		a << (this->data)->peek_a();
//		string str = a.str();
//		//frame->SetStatusText(str);
//		cout<<str<<endl;
//	}
//	cout<<"Hey, I'm Bob and I like to print stuff"<<endl;
//}


/*
* Here we do the actual rendering. I put it in a separate
* method so that it can work no matter what type of DC
* (e.g. wxPaintDC or wxClientDC) is used.
*/
void MyPanel::render(wxDC&  dc)
{
	// draw some text
	dc.DrawText(wxT("Testing"), 40, 60); 
	
	// draw a circle
	dc.SetBrush(*wxGREEN_BRUSH); // green filling
	dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
	dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

	// draw a rectangle
	dc.SetBrush(*wxBLUE_BRUSH); // blue filling
	dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
	dc.DrawRectangle( 300, 100, 400, 200 );
	
	// draw a line
	dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
	dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle
	
	// Look at the wxDC docs to learn how to draw other stuff
}

void tFunction(Data_container* dataPointer)
{
	//cout<<"a"<<endl;
	Data_container data = *dataPointer;
	//cout<<"Test: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	http_client client("127.0.0.1",8000);
	stringstream response;
	string word;
	string a[2];
	while(true)
	{
		try
		{
			response.str(std::string());
			response.clear();
			//cout<<"stream content: "<<response.str()<<endl;
			int iterator = 0;	
			client.send_request(&response,0);
			while(getline(response, word, ',')) 
				a[iterator++] = word;
			cout<<"Data: "<<a[0]<<" "<<a[1]<<endl;
			data.assign_a(stoi(a[0]));
			data.assign_b(stoi(a[1]));
			data.pull_up_data_flag();
			sleep(1);
		}
		catch(Exception &e)
		{
			cout<<e.displayText()<<endl;
		}
		//cout<<"Peek: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	}
}

IMPLEMENT_APP(HelloWorldApp)

// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool HelloWorldApp::OnInit()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	this->frame = new wxFrame((wxFrame*) NULL, -1, _T("POC DATA_VIEWER"));
	this->drawPane = new MyPanel((wxFrame*)this->frame);
	frame->CreateStatusBar();
	frame->SetStatusText(_T("działaj kurwiu"));
	SetTopWindow(frame);
	sizer->Add(drawPane, 1, wxEXPAND);
	frame->SetSizer(sizer);
	frame->SetAutoLayout(true);
	frame->Show(true);
	Data_container data(0,0);
	((MyPanel*)(this->frame))->data = &data;
	thread http_thread(tFunction,&data);
	http_thread.detach();
	return true;
}