#pragma once

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#include <bits/stdc++.h>
#include "data_container.h"
#include "http_client.h"
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "imgui/imgui.h"
#include "imgui/imgui_plot.h"
#include "imgui/imgui_impl_allegro5.h"
#include "imgui/imgui_impl_allegro5.h"
#include "imgui/ImGuiFileDialog.h"


//this might be it bois
#include "imgui/implot.h"

#define MAX_DATA_STREAMS 32

struct Visibility_windows
{
	bool menu_bar=true;
	bool plots=false;
	bool static_plots = false;
};

struct plot_settings
{
	float lw; //line weight
	bool aa; //anti-aliasing
	//...
};


class Windows
{
	ImGuiWindowFlags main_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

	const ImU32 sample_colors[MAX_DATA_STREAMS] = { ImColor(255, 255, 0), 
													ImColor(255, 0, 255), 
													ImColor(0, 255, 255),
													ImColor(255, 255, 255) };
	
	//variables for http_window
	int frame_count = 20;
	bool* data_visibility = nullptr;
	
	//variables for static_window
	int static_frame_count = 20;
	int static_offset=0;
	int static_data_size;
	volatile double* static_x=nullptr;
	int num_tiles = 1;
	vector<plot_settings> settings;

	//variables for parsing_window
	bool load=false;
	bool load_header=false;
	vector<pair<std::string,bool>*> names;


public:
	void http_window(Data_container* data_ptr);
	void static_window(Data_container* data);
	void select_window(Visibility_windows* visibility);
	void load_file(fstream** file);
	void parsing_window(Data_container** static_data,std::fstream* file);
};
