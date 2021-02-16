# GNU/Linux Build:
1. Clone the repository:
	```bash
	$ git clone https://github.com/PUT-Motorsport/PUTM_EV_Dataviewer
	$ cd PUTM_EV_Dataviewer
	```
2. Install additional dependencies into POC/imgui-POC subfolder

	2.1: Install POCO
	```bash
	$ echo "install poco according to instructions"
	$ echo "I had mine compiled so dunno for now"
	```
	2.2 Install IMGUI and additional sources
	```bash
	$ cd POC/imgui-POC
	$ git clone https://github.com/ocornut/imgui
	$ git clone https://github.com/soulthreads/imgui-plot
	```
3. Copy backend files from imgui/backends subfolder
	```bash
	$ cd imgui
	$ cp backends/imgui_impl_allegro5.* ./
	```
4. Copy imgui-plot source files to imgui subfolder
	```bash
	$ cp ../imgui-plot/include/* ./
	$ cp ../imgui-plot/src/* ./
	```
5. Make and run the binary
	```bash
	$ cd ../
	$ make run
	```
	
