<h1>Lil Engie</h1>
My attempt to make a small game engine.
<br /> <br />
Special thanks to <b>Matthew Fisher</b> for help with models
<br />
https://steamcommunity.com/profiles/76561198254676201/images/

<h2>Dependencies</h2>
<ul>
  <li>GLEW</li>
  <li>GLFW</li>
  <li>GLM</li>
  <li>Assimp</li>
  <li>stb_image</li>
</ul>

<h2>Plans</h2>
<ul>
  <li>Better input system</li>
  <li>Object hierarchies</li>
  <li>Start using .lilgam to handle all game details such as resources</li>
  <li>Make scene manager store hashmap of scene pointers with names(key)</li>
  <li>Experiment with better scene management methods(may require tons of rewriting)</li>
  <li>Make sure I have no memory issues</li>
  <li>Focus on PBR shaders</li>
  <li>Graphics folder should be interface for entity</li>
  <li>Make all lights use transform component</li>
  <li>Basic text features (alignment, word wrap, etc)</li>
  <li>Sky boxes</li>
  <li>Image effects</li>
  <li>Console logging in game window</li>
  <li>Improve scene loading error handling</li>
  
  <li>Would love to one day experiment with making an editor</li>
</ul>


Platform:
	Windows: 
		WinInput.cpp/h
			Init(); //Going to need HWND from glfw
			AddCallback(KEY key, funcptr func) //IDK details

Input:
	Keys.h
		KeyState
		Event
		Key

	Bindings.cpp/h
		//Manage .lilinp file for input bindings
		
	Input.cpp/h
		private map<string, KeyState> keys;
	
		Init();
	
		KeyEvent(Key key, Event event);
			//Match with bindings, Manage keys
	
		GetKey(string name);
		GetKeyDown(string name);
		GetKeyUp(string name);
		...



Platform:
	Windows: 
		WinInput.cpp/h
			Init(); //Going to need HWND from glfw
			WinCallback(...) //Interpret key, call keyevent in input

Input:
	Keys.h
		KeyState
		Event
		Key
		
	Input.cpp/h
		private bool[255] currentKeys;
		private bool[255] pastKeys;
	
		Init();
		KeyUpdate();
			//Transfer currentKeys to pastKeys
	
		KeyEvent(Key key, Event event);
			//Match with bindings, Manage currentKeys
	
		GetKey(string name);
		GetKeyDown(string name);
		GetKeyUp(string name);
		...


		
