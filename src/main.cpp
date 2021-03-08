#include <bits/stdc++.h>
#include "data_container.h"
#include "http_client.h"
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui/imgui.h"
#include "imgui/imgui_plot.h"
#include "imgui/imgui_impl_allegro5.h"
#include "windows.h"

using namespace std;


void tFunction(Data_container* dataPointer)
{
	//cout<<"a"<<endl;
	Data_container data = *dataPointer;
	//cout<<"Test: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	http_client client("127.0.0.1",8000);
	stringstream response;
	string word;
	string a[4]; //TODO: Change that to something more safe then static declaration
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
			//cout<<"Data: "<<a[0]<<" "<<a[1]<<endl;
			data.push_to_vector(0,stof(a[0]));
			data.push_to_vector(1,stof(a[1]));
			data.push_to_vector(2,stof(a[2]));
			data.push_to_vector(3,stof(a[3])); //TODO: Kinda the same
			data.raise_data_flag();
			usleep(0.25*1000000);
		}
		catch(Exception &e)
		{
			cout<<e.displayText()<<endl;
		}
	}
}

int main()
{
	//Create allegro event and display handler
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* display = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_set_window_title(display, "The app");
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui::StyleColorsDark();
	ImGui_ImplAllegro5_Init(display);

	ImVec4 background_color = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

	//setup basic http I/O
	Data_container data(4);
	thread http_thread(tFunction,&data);
	http_thread.detach();
	string str="";

	//Visibility_windows variable
	Visibility_windows visibility;

	Windows windows;

	//Declare window static variables:
	int size_y = 32;
	// Main loop
	bool running = true;
	while (running)
	{
		ALLEGRO_EVENT ev;
		while (al_get_next_event(queue, &ev))
		{
			ImGui_ImplAllegro5_ProcessEvent(&ev);
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				running = false;
			if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
			{
				ImGui_ImplAllegro5_InvalidateDeviceObjects();
				al_acknowledge_resize(display);
				ImGui_ImplAllegro5_CreateDeviceObjects();
			}
		}

		// Start the Dear ImGui frame
		ImGui_ImplAllegro5_NewFrame();
		ImGui::NewFrame();

		//Window if tree
		if(visibility.menu_bar)
		{	
			ImGui::SetNextWindowPos(ImVec2(0, WINDOW_HEIGHT-size_y));
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, size_y));
			windows.select_window(&visibility);
		}
		if(visibility.plots)
		{
			int size_y = 32;
			ImGui::SetNextWindowPos(ImVec2(0,0));
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT-size_y));
			windows.http_window(&data);
		}

		ImGui::Render();
		al_clear_to_color(al_map_rgba_f(background_color.x,background_color.y,background_color.z,background_color.w));
		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
		al_flip_display();
	}

	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	return 0;
}