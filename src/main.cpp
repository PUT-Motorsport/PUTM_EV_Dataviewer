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
	Data_container* static_data=nullptr;

	//TODO: Make a connection only in live mode
	thread* http_thread = nullptr;
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
			if(http_thread == nullptr)
			{
				http_thread = new thread(tFunction,&data);
				http_thread->detach();
			}
			ImGui::SetNextWindowPos(ImVec2(0,0));
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT-size_y));
			windows.http_window(&data);
		}
		if(visibility.static_plots)
		{
			visibility.plots = false;
			ImGui::SetNextWindowPos(ImVec2(0,0));
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT-size_y));
			windows.static_window(static_data);
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
	
	//free-null all the shit
	free(http_thread);
	http_thread = nullptr;
	
	free(static_data);
	static_data=nullptr;
	return 0;
}
