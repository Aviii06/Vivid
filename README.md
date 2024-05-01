# Vivid
<img width="1080" alt="Screenshot 2023-02-03 at 4 12 49 PM" src="https://user-images.githubusercontent.com/45993519/218171952-624d8dda-5c49-4fe4-942f-301deaa502f4.png">
Vivid is an OpenGL-based rendering framework providing an intuitive 2D and 3D rendering API.

# Features
**Shader-Based Rendering**: The renderer utilizes the power of shaders to achieve real-time rendering with support for vertex, fragment, and geometry shaders. This allows for flexible and efficient customization of the rendering pipeline.

**Basic Shapes**: Easily render basic geometric shapes like cubes, spheres, cylinders, and planes. These primitives can be manipulated and combined to create complex scenes.

**Texture Mapping**: Apply textures to objects for more realistic and visually appealing results. Experiment with different materials and lighting setups.

**Camera Controls**: The renderer includes a camera system that allows you to navigate and explore the 3D environment using mouse and keyboard controls.

**Lighting**: Implement point-light lighting models.

**Model Loading**: Import 3D obj models from external files to populate your scenes with intricate designs.

**User Interface**: The renderer comes with a simple user interface that provides controls for adjusting rendering settings, camera parameters, and more.

# Integration
To integrate this library into your project all you have to do is in your CMakeLists.txt add this folder as a subdirectory: `add_subdirectory(Vivid)`.
Once this is done you can link this library by simply writing:   
```cmake
target_link_libraries(project_name
        Vivid)
```

After this, you could simply write `#include "Vivid.h"`, and use the Vivid API.

# Getting Started
To get started follow these steps:

## Clone repo
```bash
git clone git@github.com:Aviii06/Vivid.git
cd Vivid
git submodule update --init --recursive
```

## Dependencies: 
Before running the renderer, ensure you have the necessary dependencies installed. This includes an OpenGL driver, a C++ compiler, and the necessary libraries (GLEW, GLFW, etc.).

Here is a checklist of dependencies for different operating systems:
### Linux
#### OpenGL
- OpenGL
#### CPP Tools
- CMake
- xorg-dev 
- libglu1-mesa-dev 
- freeglut3-dev 
- mesa-common-dev 
- libgl1-mesa-dev 
- libglew-dev 
- mesa-utils 
- freeglut3-dev
#### File Dialog Boxes
- GTK (default)
- Make sure libgtk-3-dev is installed on your system. `build-essential` and  `libgtk-3-dev`

### MacOS
#### OpenGL
- OpenGL
#### File Dialog Boxes
- On MacOS, add AppKit and UniformTypeIdentifiers to the list of frameworks.

### Windows
#### OpenGL
- OpenGL
#### File Dialog Boxes
- On Windows (both MSVC and MinGW), ensure you are building against ole32.lib, uuid.lib, and shell32.lib.

## Build the Project: 
Use the provided build system (CMake, Makefile, etc.) to build the renderer. Make sure to configure the build with the appropriate settings for your system.
```bash
mkdir build && cd build
cmake .. -G Ninja
ninja -j8
```

## Running the project: 
The project comes with many example executables, like marchingSquare and ecs_test. You can directly run these binaries.

## Explore and Experiment: 
Once the renderer is running, feel free to explore the various features it offers. Modify shaders, adjust camera settings, load different models, and experiment with lighting configurations.


# API
## Philosophy
The API is inspired primarily by [processing foundation](https://github.com/processing).

You have a Rendering Interface which comes with 3 main functions: `Setup()`, `Draw()`, and `ImGuiRender()`. You can create a new class which extends to RenderingInterface and override these functions.
This provides a multitude of different rendering APIs all with different levels of control to ease.

## Types of API

### ECS API
This API provides a complete entity-component-based architecture. You can initialise an entity and give it many components and they all get rendered automatically.
![Screenshot 2023-08-29 at 8 57 21 PM](https://github.com/Aviii06/Vivid/assets/45993519/d674cba6-3b2b-421c-9a58-31ac616295e6)


### Rendering 2D/3D APIs
These APIs create a more processing-like feel to rendering. You call a `Vivid::Renderer2D::Init();` or `Vivid::Renderer3D::Init();` and can call many functions like `Vivid::Renderer2D::DrawLine(point1, point2, thickness, color);` and more. 
This makes it easy to create a small simulation which is not overly complicated.

![Screenshot 2023-08-29 at 9 02 14 PM](https://github.com/Aviii06/Vivid/assets/45993519/726871f7-9659-4c40-9173-f0861f736d38)

### Mesh API
This is useful for small renders. You can simply create a Mesh object from an Obj file and then render it out by calling the `Draw(camera)` method.  
![Screenshot 2023-08-29 at 9 21 26 PM](https://github.com/Aviii06/Vivid/assets/45993519/138684c3-d278-4c90-ab44-55c664923f09)


## Rendering Interface
This is an interface which is provided by Vivid to ease the rendering process.
```cpp
class ExampleInterface : public Rendering
```

### Setup()
The `Setup()` function runs once and is useful for initializing your variables.
The first line of the setup is reserved for your openGL configs. You can write your own configs or use one of the premade configs.
For 3D it is recommended to use: `OPENGL_CONFS`
And for 2D: `OPENGL_2D_CONFS`

### Draw()
This function is called every frame. And is not inside the ImGUI context.

### ImGuiRender()
This function is similar to `Draw()` but is inside ImGUI context so this could be used to create custom UI elements.

To see examples using these APIs you can look in the examples folder in the root directory of the repo.

## 2D

First in your `Setup()` function use the macro `OPENGL_2D_CONFS`.
To get started with 2D API you need to call `Vivid::Renderer2D::Init();` in your `Setup()` function. This initializes the 2D renderer.

In your `Draw()` loop call `Vivid::Renderer2D::BeginScene();` and once all the DrawCalls have been made call `Vivid::Renderer2D::EndScene();`
In between these two functions, you can use the Renderer2D API to render anything. This all gets BatchRendered for optimal performance.

Examples can be found in `examples/examples2D`.

Write the `Vivid::CreateApplication()` function:

```cpp
Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Rendering2D");

	OrthoCamera* orthoCamera = new OrthoCamera(0, 1920, 0, 1080);
	app->SetCamera(orthoCamera);
	app->SetRenderingInterface(new ExampleInterface);
	return app;
}
```
It is advised to have `OrthoCamera` for 2D scenes.
This is a client-side function which is used in the library to create an Application.

After the in your main function simply call: `return Vivid::main(0, nullptr);` This calls Vivid's main function.

## 3D

First in your `Setup()` function use the macro `OPENGL_CONFS`.
The 3D rendering API is still WIP.

Currently for 3D rendering it is advised to use the ECS based approach.

Examples can be found in `examples/examples3D`.

Write the `Vivid::CreateApplication()` function:

```cpp
Application* Vivid::CreateApplication()
{
	Application* app = Application::GetInstance(1920, 1080, "Rendering2D");

	app->SetRenderingInterface(new ExampleInterface);
	return app;
}
```

By Default it uses `EditorCamera` which provides WASD movements and mouse control.

After the in your main function simply call: `return Vivid::main(0, nullptr);` This calls Vivid's main function.



#Contribute
If you find issues or want to contribute enhancements, fork the repository, make your changes, and submit a pull request. We welcome contributions from the community.

# Documentation
For more detailed information on how to use the renderer, including API documentation and usage examples, refer to the [Documentation](https://aviii06.github.io/Vivid/) of this repository.

# License
This project is licensed under the MIT License, which means you are free to use, modify, and distribute the code as long as you include the original license text.
