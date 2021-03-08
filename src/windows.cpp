#include "windows.h"

using namespace std;

void Windows::http_window(Data_container* data)
{
	if(this->data_visibility==nullptr)
	{
		this->data_visibility = new bool [MAX_DATA_STREAMS];
		for(int i=0;i<data->get_num_data();i++)
			this->data_visibility[i]=true;
	}
	ImGui::Begin("Windows",NULL,this->main_flags);
	
	static uint32_t selection_start = 0, selection_length = 0;
	ImGui::SetNextWindowPos(ImVec2(100,0));
	ImGui::BeginChild("child",ImVec2(1500,ImGui::GetWindowHeight()),false,this->main_flags);

	ImGui::PlotConfig conf;
	//float* val;[] = {data->get_vector_data_ptr(0),data->get_vector_data_ptr(1)};
	float* val[MAX_DATA_STREAMS];
	ImU32 colors[MAX_DATA_STREAMS];
	int it=0;
	for(int i=0;i<data->get_num_data();i++)
	{
		if(this->data_visibility[i])
		{
			val[it] = data->get_vector_data_ptr(i);
			colors[it] = sample_colors[i];
			it++;
		}
	}
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
		ImGui::EndChild();
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
	conf.values.ys_count = it;
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
	ImGui::EndChild();
	ImGui::SetNextWindowPos(ImVec2(10,0));
	ImGui::BeginChild("Legend",ImVec2(90,ImGui::GetWindowHeight()),false,this->main_flags);
	ImGui::Text("Show:");
	for(int i=0; i<data->get_num_data();i++)
	{
		stringstream ss;
		ss << "Data " << i;
		string asdf = ss.str();
		ImGui::Checkbox(asdf.c_str(),this->data_visibility+i);
	}
	ImGui::EndChild();
	ImGui::End();
}

void Windows::select_window(Visibility_windows* visibility)
{
	ImGui::Begin("Main menu",NULL,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
	ImGui::Checkbox("Okno z http", &(visibility->plots));
	ImGui::End();
}