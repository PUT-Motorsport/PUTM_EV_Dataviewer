#include <bits/stdc++.h>
#include "data_container.h"
#include "http_client.h"
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui/imgui.h"
#include "imgui/imgui_plot.h"
#include "imgui/imgui_impl_allegro5.h"

using namespace std;

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
			//cout<<"Data: "<<a[0]<<" "<<a[1]<<endl;
			data.assign_a(stoi(a[0]));
			data.assign_b(stoi(a[1]));
			data.pull_up_data_flag();
			sleep(1);
		}
		catch(Exception &e)
		{
			cout<<e.displayText()<<endl;
		}
	}
}

constexpr size_t buf_size = 1024;
static float x_data[buf_size];
static float y_data1[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];


void generate_data() {
	constexpr float sampling_freq = 44100;
	constexpr float freq = 500;
	for (size_t i = 0; i < buf_size; ++i) {
		const float t = i / sampling_freq;
		x_data[i] = t;
		const float arg = 2 * M_PI * freq * t;
		y_data1[i] = sin(arg);
		y_data2[i] = y_data1[i] * -0.6 + sin(2 * arg) * 0.4;
		y_data3[i] = y_data2[i] * -0.6 + sin(3 * arg) * 0.4;
	}
}



int main()
{
	//random allegro code
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
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

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_advanced_graph_thing = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	int iter = 0;
	Data_container data(0,0);
	thread http_thread(tFunction,&data);
	http_thread.detach();
	string str="";
	vector<float> values;

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

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			ImGui::Begin("Okno nr 1");
			ImGui::Checkbox("Demo Window", &show_demo_window);
			ImGui::Checkbox("Okno z http", &show_another_window);
			ImGui::Checkbox("Okno z http i customowym fajnym plotem", &show_advanced_graph_thing);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_another_window)
		{
			ImGui::Begin("HTTP data: ", &show_another_window);
			if(data.get_data_flag()==true)
			{
				cout<<"Peek: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
				data.pull_down_data_flag();
				stringstream a;
				a << data.peek_a();
				str = a.str();
				values.push_back((float)data.peek_a());
			}
			ImGui::Text((str).c_str());
			char* a = (char*)malloc(sizeof(char)*50);
			sprintf(a,"make me smile"); 
			ImGui::PlotLines("Dane numero uno", values.data(), values.size());
			
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
		if(show_advanced_graph_thing)
		{
			//ImGui::Begin("HTTP data: ", &show_advanced_graph_thing,ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Begin("HTTP data: ", &show_advanced_graph_thing);
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
			ImGui::BeginChild("Data",ImVec2(ImGui::GetWindowContentRegionWidth(), 0), false, window_flags);
			// imgui-plot blob begin
			generate_data();
			static const float* y_data[] = { y_data1, y_data2, y_data3 };
			static ImU32 colors[3] = { ImColor(255, 255, 0), ImColor(255, 0, 255), ImColor(0, 255, 255) };
			static uint32_t selection_start = 0, selection_length = 0;
			// Draw first plot with multiple sources
			ImGui::PlotConfig conf;
			iter++;
			conf.values.xs = x_data;
			
			//yay, this exists, so than I can put live values into a GIANT vector and then just kinda do it and see what happens
			//adjusting offset, x_data and values and their size. Then add scaling and some magical per-color scales (hopefully)
			//and then see magic rise
			conf.values.offset = iter%512;
			
			conf.values.count = buf_size/2;
			conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
			conf.values.ys_count = 3;
			conf.values.colors = colors;
			conf.scale.min = -1;
			conf.scale.max = 1;
			conf.tooltip.show = true;
			conf.grid_x.show = true;
			conf.grid_x.size = 128;
			conf.grid_x.subticks = 4;
			conf.grid_y.show = true;
			conf.grid_y.size = 0.5f;
			conf.grid_y.subticks = 5;
			conf.selection.show = true;
			conf.selection.start = &selection_start;
			conf.selection.length = &selection_length;
			conf.frame_size = ImVec2(ImGui::GetWindowWidth(), 200);
			ImGui::Plot("plot1", conf);

			// Draw second plot with the selection
			// reset previous values
			conf.values.ys_list = nullptr;
			conf.selection.show = false;
			// set new ones
			conf.values.ys = y_data3;
			conf.values.offset = selection_start;
			conf.values.count = selection_length;
			conf.line_thickness = 2.f;
			ImGui::Plot("plot2", conf);

			// imgui-plot blob end
			if (ImGui::Button("Close Me"))
				show_advanced_graph_thing = false;
			ImGui::EndChild();
			ImGui::End();
		}
		ImGui::Render();
		al_clear_to_color(al_map_rgba_f(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
		ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
		al_flip_display();
	}

	ImGui_ImplAllegro5_Shutdown();
	ImGui::DestroyContext();
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	return 0;
}