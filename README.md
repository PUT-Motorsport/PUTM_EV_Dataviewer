# GNU/Linux Build:
1. Clone the repository:
	```bash
	git clone https://github.com/PUT-Motorsport/PUTM_EV_Dataviewer
	cd PUTM_EV_Dataviewer
	```
2. Install additional dependencies into src/ subfolder

	2.1: Install POCO
	Compile/install complete POCO libraries according to https://pocoproject.org/download.html#building
	
	2.2: Install allegro5:
	
	- Debian/ubuntu:
	```bash 
	sudo apt install allegro
	```
	- Arch/Manjaro:
	```bash 
	sudo pacman -S allegro
	```
	2.3 Install IMGUI and additional sources
	```bash
	cd src/
	git clone https://github.com/ocornut/imgui
	git clone https://github.com/soulthreads/imgui-plot
	```
3. Copy backend files from imgui/backends subfolder
	```bash
	cd imgui
	cp backends/imgui_impl_allegro5.* ./
	```
4. Copy imgui-plot source files to imgui subfolder
	```bash
	cp ../imgui-plot/include/* ./
	cp ../imgui-plot/src/* ./
	```
5. Make and run the binary
	```bash
	cd ../
	make run
	```
	
