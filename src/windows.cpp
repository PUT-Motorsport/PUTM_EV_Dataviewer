#include "windows.h"

// https://github.com/epezent/implot

#define SLOWING_FACTOR 40

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

void Windows::static_window(Data_container* data)
{
	ImGui::Begin("Static",NULL,this->main_flags);

	ImGui::BeginChild("child",ImGui::GetWindowSize(),false,this->main_flags);
	//TODO: fix this ugly hack
	for (int i = 0; i < 1000; i++)
	{
		this->static_x[i]=(float)i;
	}
	
	ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0,0,0,0));
	//ImPlot::ShowDemoWindow();
	if (ImPlot::BeginPlot("My Plot",NULL,NULL,ImGui::GetWindowSize())); 
	{
		//ImPlotAxisFlags_AutoFit
		for(int i=0;i<data->get_num_data();i++)
		{
			stringstream ss;
			ss << i;
			ImPlot::PlotLine(ss.str().c_str(),(float*)this->static_x,data->get_vector_data_ptr(i),data->get_vector_size(i));
		}
		ImPlot::EndPlot();
	}
	ImGui::PopStyleColor();
	ImGui::EndChild();

	ImGui::End();
}

void Windows::select_window(Visibility_windows* visibility)
{
	ImGui::Begin("Main menu",NULL,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
	ImGui::SetNextWindowPos(ImVec2(0,ImGui::GetWindowPos().y));
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::BeginChildFrame(100100,ImVec2(200,ImGui::GetWindowHeight()),this->main_flags);
	ImGui::Checkbox("Okno z http", &(visibility->plots));
	ImGui::EndChildFrame();
	ImGui::SetNextWindowPos(ImVec2(220,ImGui::GetWindowPos().y));
	ImGui::SetNextWindowBgAlpha(0);
	ImGui::BeginChildFrame(100101,ImVec2(200,ImGui::GetWindowHeight()),this->main_flags);
	ImGui::Checkbox("Analiza statyczna", &(visibility->static_plots));
	ImGui::EndChildFrame();
	ImGui::End();
}

Data_container* Windows::load_data(Data_container* static_data)
{
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".csv", ".");
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
		std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
		std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
		static_data = new Data_container(4);	
		fstream file;
		file.open(filePathName,ios::in);
		string a = "";
		while(getline(file,a))
		{
			if(a[0]=='D') //TODO: Replace with a better header-line identifier
				continue;
			stringstream temp(a);
			float nums[4];
			int it=0;
			for(float i; temp >> i;)
			{
				nums[it] = i;
				it+=1; 
				if (temp.peek() == ',')
					temp.ignore();
			}
			for(int i=0;i<4;i++)
			{
				static_data->push_to_vector(i,nums[i]);
				//cout<<nums[i]<<endl;
			}
		}
		file.close();
		cerr<<"loaded "<<filePathName<<endl;
		}
	ImGuiFileDialog::Instance()->Close();
	}
	
	return static_data;
}