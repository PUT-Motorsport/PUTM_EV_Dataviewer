#include "windows.h"

// https://github.com/epezent/implot

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
	double* val[MAX_DATA_STREAMS];
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

void modify_style(ImPlotStyle* style,plot_settings* s)
{
	using namespace ImGui;
	Text("Grubość linii:");
	SliderFloat("##asd", &(s->lw), 0.0f, 5.0f, "%.1f");
	Text("Anty-Aliasing:");
	ImGui::Checkbox("##asdf", &(s->aa));
	style->LineWeight = s->lw;
	style->AntiAliasedLines = s->aa;
}

void Windows::static_window(Data_container* data)
{
	volatile float width=1.0f;
	ImGui::Begin("Static",NULL,this->main_flags);
	int temp = this->num_tiles;
	if(this->settings.size()==0)
	{
		plot_settings s;
		s.lw = ImPlot::GetStyle().LineWeight;
		s.aa = ImPlot::GetStyle().AntiAliasedLines;
		this->settings.push_back(s);
		cout<<"Pushing to settings"<<endl;

	}
	for(int k=0;k<temp;k++)
	{
		ImGui::SetNextWindowPos(ImVec2(10,int(ImGui::GetWindowSize().y/this->num_tiles)*k));
		stringstream name;
		name << "sterowanie"<< k;
		ImGui::BeginChild(name.str().c_str(),ImVec2(140,int(ImGui::GetWindowSize().y/this->num_tiles)),false,this->main_flags);
		ImGui::Text("Sterowanie");
		//ImPlot::ShowStyleEditor();
		modify_style(&ImPlot::GetStyle(),this->settings.data()+k);
		if(k==0)
		{
			ImGui::Button("split!",ImVec2(100,100));
			if(ImGui::IsItemActivated())
			{
				this->num_tiles+=1;
				plot_settings new_settings;
				new_settings.lw = ((plot_settings)*(this->settings.begin())).lw;
				this->settings.push_back(new_settings);
			}
		}
		stringstream temp;
		temp << this->num_tiles;
		ImGui::Text(temp.str().c_str());
		ImGui::EndChild();
	}
	//ImGui::DragFloat("Grubość",)
	ImGui::SetNextWindowPos(ImVec2(150,0));
	
	ImGui::BeginChild("child",ImVec2(ImGui::GetWindowWidth()-150,ImGui::GetWindowHeight()),false,this->main_flags);
	//TODO: fix this ugly hack
	if( this->static_x == nullptr)
	{
		this->static_x = new volatile double[10000000];
		for (int i = 0; i < 10000000; i++)
		{
			this->static_x[i]=(double)i;
		}
		cout<<"Oi mate"<<endl;
	}
	
	//ImPlot::ShowDemoWindow();
	for(int k=0;k<this->num_tiles;k++)
	{
		ImGui::PushStyleColor(ImGuiCol_FrameBg,ImVec4(0,0,0,0));
		stringstream asdf;
		asdf << k; 
		if (ImPlot::BeginPlot(asdf.str().c_str(),NULL,NULL,ImVec2(ImGui::GetWindowSize().x,int(ImGui::GetWindowSize().y/this->num_tiles)),ImPlotFlags_NoTitle,0,ImPlotAxisFlags_AutoFit)); 
		{
			for(int i=0;i<data->get_num_data();i++)
			{
				//TODO: Add "glue" between segments (there's a 1u gap in filling, no data actually is lost)"
				//TODO: Add a generator to X axis, due to inaccuracy with larger numbers
				int x_left=ImPlot::GetPlotLimits().Min().x,x_right=ImPlot::GetPlotLimits().Max().x;

				if(x_left < 0) x_left = 0;
				for(int j=(int)(x_left/1000);  j<=(int)(x_right/1000)+1; j++)
					ImPlot::PlotLine<double>(data->get_names()[i].c_str(),(double*)this->static_x+1000*j,(double*)data->get_vector_data_ptr(i)+1000*j,1000,1000*j);
					//ImPlot::PlotStairs<double>(data->get_names()[i].c_str(),(double*)this->static_x+1000*j,(double*)data->get_vector_data_ptr(i)+1000*j,1000,1000*j);
				//cout<<ImPlot::GetPlotLimits().Min().x<<endl;
				//TODO: check if the change in imconfig.h is needed after drawing in blocks
				//ImPlot::PlotLine<double>(data->get_names()[i].c_str(),(double*)this->static_x,(double*)data->get_vector_data_ptr(i),1000);

			}
			ImPlot::EndPlot();
			ImGui::PopStyleColor();
		}
	}
	
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

void Windows::load_file(fstream** file)
{
	//TODO: Swap theese to make it portable
	//ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".csv", ".");
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".csv", "/home/czarnobylu/.files/");
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName(); 
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			cout<<"Loaded file: "<<filePathName<<endl;
			(*file) = new fstream;
			(*file)->open(filePathName,ios::in);
			printf("%p\n",*file);
		}
		ImGuiFileDialog::Instance()->Close();
	}	
}

void Windows::parsing_window(Data_container** static_data,fstream* file)
{
	ImGui::Begin("Parsing Window",NULL,this->main_flags);
	string a = "";
	if(!this->load_header)
	{
		getline(*file,a);
		stringstream temp(a);
		for(string i; getline(temp, i, ',');)
		{
			this->names.push_back(new pair<string,bool>(i,true));
			cout<<i<<endl;
		}
		this->load_header = true;
	}
	
	ImGui::Text("Load:");
	//select the fields that you will input
	for(auto i : this->names)
	{
		ImGui::Checkbox(i->first.c_str(),&(i->second));
	}
	if(!this->load)
		this->load = ImGui::Button("OK",ImVec2(30,20));
	if(this->load)
	{
		int fields = 0;
		for(auto i : this->names)
			if(i->second) fields++;
		
		(*static_data) = new Data_container(fields);
		Data_container* data = *static_data;
		for(auto i : this->names)
			if(i->second) data->push_name(i->first);
		int it=0;
		int field = 0;
		long long iter=0;
		while(getline(*file,a))
		{
			if(++iter%100000==0) cout<<iter<<endl;
			it=0;
			field = 0;
			stringstream line(a);
			for(double i; line>>i;)
			{
				if(names[field]->second)
				{
					data->push_to_vector(it,i);
					it++;
				}
				field++;
				if (line.peek() == ',')
					line.ignore();
			}
		}
		file->close();
	}
	ImGui::End();
}

