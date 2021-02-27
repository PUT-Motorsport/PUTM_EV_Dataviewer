#include "windows.h"

using namespace std;

void Windows::http_window(Data_container* data)
{
	static ImU32 colors[3] = { ImColor(255, 255, 0), ImColor(255, 0, 255), ImColor(0, 255, 255) };
	static uint32_t selection_start = 0, selection_length = 0;
	ImGui::Begin("Plots",NULL,main_flags);

	ImGui::PlotConfig conf;
	float* val[] = {data->get_vector_data_ptr(0),data->get_vector_data_ptr(1)};
	int offset;
	int count;

	if(data->get_vector_size(0) > (unsigned int)(this->frame_count))
	{
		count = this->frame_count;
		offset = data->get_vector_size(0)-this->frame_count;
	}
	else if(data->get_vector_size(0) <=0 || data->get_vector_size(1) <= 0)
	{
		
		ImGui::BulletText("Network error");
		ImGui::End();
		return;
	}
	else
	{
		offset = 0;
		count = data->get_vector_size(0);
	}

	conf.values.offset = offset;
	conf.values.count = count;
	conf.values.ys_list = (const float **)&val;
	conf.values.ys_count = 2;
	conf.values.colors = colors;
	conf.scale.min = -1;
	conf.scale.max = 1;
	conf.tooltip.show = true;
	conf.grid_x.show = false;
	conf.grid_x.size = 1;
	conf.grid_x.subticks = 1;
	conf.grid_y.show = true;
	conf.line_thickness = 2.f;
	conf.grid_y.size = 1;
	conf.grid_y.subticks = 2;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(ImGui::GetWindowWidth(), 440);
	ImGui::Plot("plot1", conf);

	ImGui::SliderInt("Scale size", &this->frame_count, 5, 100);

	ImGui::End();
}

void Windows::select_window(Visibility_windows* visibility)
{
	ImGui::Begin("Main menu",NULL,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
	ImGui::Checkbox("Okno z http", &(visibility->plots));
	ImGui::End();
}