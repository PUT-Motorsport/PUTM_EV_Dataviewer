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

struct Visibility_windows
{
	bool menu_bar=true;
	bool plots=false;
};

class Windows
{
	ImGuiWindowFlags main_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	int frame_count = 20;
public:
	void http_window(Data_container* data_ptr);
	void select_window(Visibility_windows* visibility);
};