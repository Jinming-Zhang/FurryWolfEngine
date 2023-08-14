# OpenGL Intro
OpenGL process result into -1, 1 coordinates, then it maps to the actual pixel on the screen based on the configuration of `glViewport`, or the screen size we have set for the window.

`glfwSwapBuffers` swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration (the back buffer), and show it as output to the screen. (switched to the front buffer).

When clear the color at each frame, we can select which bit of the buffer we want to clear, possible values are 
	-`GL_COLOR_BUFFER_BIT`, the front buffer
	-`GL_DEPTH_BUFFER_BIT`, the depth buffer
	-`GL_STENCIL_BUFFER_BIT`, the stencil buffer

## Vertex Input
OpenGL only processes 3D coordinates when they are in a specific range between $[-1.0,1.0]$ on all 3 axes (*normalized device coordinates*). Points fall out of the NDC will not be visible.

> We also need to transform the input data to vertex shader to normalized device coordinates as well, otherwise the points outside of NDC will be discarded.

### Normalized Device Coordinates (NDC)
Once the vertex coordinates have been processed in the vertex shader, they should be in *normalized device coordinates*. It's origin is at the center of the graph with positive y-axis points in the up-direction.

![[normalizedDeviceCoordinate.png]]
Then the NDC coordinates will be transformed to *screen-space coordinates* via the *viewport transform* using the data provided with `glViewport` function.

The resulting screen-space coordinates are then transformed as inputs of the **fragment shader**.

## Vertex Data
The definition of **vertex** is a **collection** of data per 3D coordinate, it can contain information **more than** the 3D coordinate, such as normal, ambient color, etc.

**Vertex data** is a **collection** of vertices, usually is represented using **vertex attributes**, which can contain any data we'd like (defined by ourselves).

## Send Vertex Data to GPU
To send the vertex data to GPU for the first process of the graphics pipeline, first we need to creating memory on GPU, configure how OpenGL should interpret the memory, and specify how to send the data to the graphics card.

We manage the memory of the Vertex Data via the *Vertex Buffer Objects (VBO)*, which can store a large number of vertices in GPU's memory.

> The advantage of using VBO is that we can send large batches of data all at once to the graphics card, and keep it there if there's enough memory left.

To generate an VBO object and get its ID, we use the `glGenBuffers` function:
```cpp
unsigned int VBO;
glGenBuffers(1, &VBO);
```
OpenGL has many types of buffer objects, the buffer type for a vertex buffer object is `GL_ARRAY_BUFFER`. Since we are generating buffer for vertex buffer object, we'll bind the buffer to that type:
```cpp
glBindBuffer(GL_ARRAY_BUFFER, VBO);
```
After we bind the buffer, all the following buffer calls we make on the `GL_ARRAY_BUFFER` target will be used to configure the current bound buffer (VBO in this case).
Then we can use `glBufferData` to copy the vertex data we defined into the buffer's memory:
```cpp
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```
`glBufferData` is a function specifically for copying user-defined data into the currently bound buffer.
- First arg is the type of the buffer we want to copy data into
- Second arg is the size of the data, in bytes, we want to pass to the buffer.
- Third arg is the actual data we want to send.
- Fourth arg tells how we want the GPU to manage the data, it can take 3 forms:
	- `GL_STREAM_DRAW`: data is set only once and used just a few times.
	- `GL_STATIC_DRAW`: data is set once and used many times.
	- `GL_DYNAMIC_DRAW`: data is changed a lot and used many times.
 
For example, for `GL_DYNAMIC_DRAW` data, GPU will place the data in memory that allows for faster writes.

## Shaders
### Vertex Shader
```cpp
#version 330 core
layout (location=0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```
First we specify the version of the shader.
Then we declare all the input vertex attributes in the vertex shader with the `in` keyword.

> A vertex shader can have several **vertex attributes**, each vertex attribute is specified with `location=` followed by the location we defined ourselves. To pass the data to corresponding vertex attribute in the vertex shader, we'll need to specify how the OpenGL should interpret our vertex data in C++ side through [[#Linking Vertex Attributes]].

We specifically set the location of the input variable via the `layout (location=0)`.
`gl_Position` is a predefined variable that holds the output of the vertex shader.

## Fragment Shader
Fragment shader is responsible for calculating the color output of the pixels.
```cpp
#version 330 core
out vec4 fracColor;

void main()
{
	fragColor = vec4(1.0f, .5f, .2f, 1.0f);
}
```

Fragment shader requires one output variable of type vec4, which defines the final color output we calculated ourselves.

## Compile a Shader
In order for OpenGL to use the shader, it has to dynamically compile it at run-time from its source code.

We first need to create a shader object of the corresponding type using `glCreateShader()`, then referenced by an ID.
```cpp
unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
```
Then we attach the shader source code to the shader object using `glShaderSource` and compile the shader using `glCompileShader`:
```cpp
glShaderSource(vertexShader, 1, &vertexShaderCource, NULL);
glCompileShader(vertexShader);
```
`glShaderSource` takes 4 arguments:
1. the shader object id
2. the number of strings we are passing as source code
3. the actual source code of the vertex shader

To check for errors we can use `glGetShaderiv` for compile-time errors:
```cpp
int success;
char log[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
	glGetShaderInfoLog(vertexShader, 512, NULL, log);
	std::cout<<log<<std::endl;
}
```

## Shader Program
A Shader Program object is the final linked version of multiple shaders combined.
Shaders will need to be linked to a shader program object, then the shader program object will be activated, then its used to render the objects.
The activated shader program's shaders will be used when we issue render calls.

> When linking shaders into a program, it will link the outputs of each shader to the inputs of the next shader. Linking errors will be generated if the outputs and inputs do not match.

To create a Shader Program and attach custom shaders, we first need to create a shader program:
```cpp
unsigned int shaderProgram = glCreateProgram();
```
Then we can attach compiled shaders to the created program by using the shader object reference id:
```cpp
glAttachShader(shaderProgram, shaderId);
```

After we attached all the shaders we want to the shader program, we can tell the shader program to link all the shaders, if successful, the shader program will be ready to use.
```cpp
glLinkProgram(shaderProgram);

// to check if the linking successful
int success;
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

// we can delete shaders after we linked them to a shader program
glDeleteShader(shaderId);

// to use the shader program for following rendering calls
glUseProgram(shaderProgram);
```

## Linking Vertex Attributes
Right now, we have done the following:
1. Define vertices data and copied them to GPU through VBO 
2. Created and compiled vertex and fragment shaders
3. Created a shader program and linked our shaders

However, OpenGL still don't know how to interpret the vertex data, and how to connect the vertex data to the vertex shader's attribute.

Based on how we defined our vertex data (list of vertex, which is a collection of data per coordinate), we can specify how OpenGL should interpret it and pass it to vertex shader:
![[vertexDataInitial.png]]

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);;
glEnableVertexAttribArray(0);
```

glVertexAttribPointer:
- The first parameter is the vertex attribute we want to configure. This should match the number (0 in our case) in `(location=0)` in our vertex shader.
- The second parameter specify the size (number of elements) of the vertex attribute. Since the attribute is `vec3`, we pass it 3.
- The third parameter specifies the type of the data. Since `vec` in GLSL consists of floating point values, we pass `GL_FLOAT`.
- The fourth parameter specifies whether the data should be normalized. If we inputting integer data types (int, char, byte) and we set to `GL_TRUE`, the data will be normalized to 0 and 1 when converted to float.
- The fifth parameter is the *stride*, which means the space between consecutive vertex attributes. This is useful when we have more than 1 vertex attribute for our shaders. Right now our vertex data is *tightly packed*, which means we only have one position attribute and there is no space (extra data) between each position attribute. We can set it to 0 or explicitly to the total bytes needed (`3*sizeof(float)`).
- The last parameter specifies the offset of where the position data begins in the buffer. Since it's of type `void*`, we need the cast.

> When calling `glVertexAttriPointer`, each vertex attribute, i.e. `aPos`, takes its data from memory managed by the VBO that is currently bounded to `GL_ARRAY_BUFFER`. So make sure we bind the proper VBO before linking the vertex attributes.

Since vertex attributes are disabled by default, we need to call `glEnableVertexAttribArray` with the specified attribute location after we tell OpenGL how to interpret the vertex data.

## Vertex Array Object
Right now, to draw an object, we need to do the following:
1. Create and bind VBO
2. Copy vertices data to GPU through the VBO
3. Link vertex attribute and enable vertex attribute

An *vertex array object* enable us to store the the configurations of the above steps, so that every time we need to draw those set of vertices, we only need to bind the VAO and then call the rendering function. All the states we just set will be stored inside the VAO.

A *vertex array object* stores following information:
1. Calls to `glEnableVertexAttribArray` or `glDisableVertexAttribArray`
2. Calls to `glVertexAttribPointer` that configures vertex attributes
3. *Vertex buffer object* that associated with the above calls.
![[VAOGraph.png]]

After use a VAO:
1. Generate a VAO using `glGenVertexArrays(1, &vao)`
2. Bind it to current object using `glBindVertexArray(vao)`

Then all the future calls for VBO and linking vertex attribute will be stored in the VAO we just created.

To render object using VAO, we use the function `glDrawArrays(GL_TRIANGLES, 0, 3)`.
- The first arg is the primitive type we are drawing.
- The second arg is the starting index of the vertex array.
- The last arg is the number of vertices we want to draw.

## Element Buffer Object
Instead drawing by vertex data, we can copy a unique vertex data that we'll use for drawing, and then use a list of indices to indicate the order of vertices we would like to draw, this method is called *indexed drawing*, and it's achieved through *element buffer object*.

Similar to VBO, we first need to generate a EBO object and retrieve the reference id. Then we copy the indices to GPU.

To render EBO object, we'll use `glDrawElement` function. It will render the indices provided by the currently bound EBO.
```cpp
// generate ebo and copy indices data
unsigned int ebo = glGenBuffers(1, &ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// bind the ebo and call the render function
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0)
```

`glDrawElements`:
- The first arg is the mode we want to draw
- The second arg is the number of elements we want to draw (6 indices in our case).
- The third arg is the type of indices (*UNSIGNED INT* in our case).
- The last arg is the offset in the EBO.


> Similar to VBO, we can also use VAO to store the data/configuration for EBO, and bind VAO for rendering calls.
>
> However, since VAO stores the `glBindBuffer` call when the buffer target is *GL_ELEMENT_ARRAY_BUFFER* (EBO), which means VAO will also store unbind calls (when the second parameter of `glBindBuffer` is 0, it unbinds the buffer), so, we should **NOT** unbind the EBO buffer while an VAO is active. (i.e. we should unbind VAO first, then EBO).

 ![[VAOAndEBO.png]]
 ```cpp
// define vertices and indices array
// 1. generate vao, vbo, ebo, and copy data to gpu
unsigned int vao, vbo, ebo;
glGenVertexArrays(1, &vao);
glGenBuffers(1, &vbo);
glGenBuffers(1, &ebo);
// 2. bind vao and configure vbo and ebo
glBindVertexArray(vao);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 2. - configure ebo
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 2. - configure vertex attributes based on vbo
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0); 

// 3 - set shader program to use and call render function
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
```

## Wireframe mode
We can let OpenGL to draw in wireframe mode by calling the `glPolygonMode` function:
```cpp
// draw outline only
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
// fill the triangles
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
```