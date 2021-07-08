
# What is GL Window ?

**GL Window** a.k.a **GLWND** is a modern GL library that helps you quickly create GL GUI application

## Requirements

* Windows 32/64 bit
* MS Visual C++ 2019 or later

## Features
* Modern Open GL
* Interactive
  * Keyboard Events
  * Mouse Events
  * Drag & Drop Events
 * Vertex Buffer Object (VBO)
 * Pixel Buffer Object (PBO)
 * Texture Manipulation
 * Integrated Dear ImGUI
 * Shader (GLSL)
 * FT/GLUT Text Renderer
 * Primitive Renderer
 * Mesh Loader/Renderer
 * Multi Views
 * Debugging Error
 * Etc

## License

Released under the [MIT](LICENSE.md) license

## Installation

>$ git clone https://github.com/vic4key/GL-Window.git
>
>$ cd [GL-Window](https://github.com/vic4key/GL-Window)
>
>$ git submodule update --init --recursive
>
>$ git submodule foreach --recursive git checkout master
>
>$ git submodule foreach --recursive git pull
>
>$ setx `GL_3RDPARTY_DIR` [%CD%\\glwnd\\3rdparty\\](https://github.com/vic4key/gl-3rdparty)
>
> *load [GL-Window.sln](https://github.com/vic4key/GL-Window/blob/master/GL-Window.sln) into VS then build them all*

* Usage
	* Take a look at the [examples](example)

## Examples

>[example/example.simple.h](example/example.simple.h)
>
>![](screenshots/example.simple.png?)

>[example/example.imgui.h](example/example.imgui.h)
>
>![](screenshots/example.imgui.png?)

>[example/example.vds.h](example/example.vds.h)
>
>![](screenshots/example.vds-2a.png?)
>![](screenshots/example.vds-4a.png?)

>[example/example.mesh.h](example/example.mesh.h)
>
>![](screenshots/example.mesh-1.png?)
>![](screenshots/example.mesh-2.png?)

>[example/example.multiview.h](example/example.multiview.h)
>
>![](screenshots/example.multiview-2x2.png?)
>![](screenshots/example.multiview-2x1.png?)
>![](screenshots/example.multiview-1x2.png?)

>[example/example.shader.h](example/example.shader.h)
>
>![](screenshots/example.shader.png?)

>[example/example.image.h](example/example.image.h)
>
>![](screenshots/example.image.png?)

>[example/example.text.h](example/example.text.h)
>
>![](screenshots/example.text.png?)

>[example/example.textglut.h](example/example.textglut.h)
>
>![](screenshots/example.textglut.png?)

>[example/example.primitive.h](example/example.primitive.h)
>
>![](screenshots/example.primitive.png?)

>[example/example.events.h](example/example.events.h)
>
>![](screenshots/example.events.png?)

>Etc

## Contact
Feel free to contact via [Twitter](https://twitter.com/vic4key) / [Gmail](mailto:vic4key@gmail.com) / [Blog](https://blog.vic.onl/) / [Website](https://vic.onl/)