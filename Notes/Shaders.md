# Shaders
## Definition
Shaders are small programs that run on GPU for each step of the graphics pipeline.

These programs usually contains highly specialized steps and can be easily executed in parallel.

A ShaderProgram is a complete render pipeline that contains shaders for different stages of the rendering pipeline.

After we compiled the shader (i.e. vertex and fragment shader), we'll need to attach them to a shader program, and finally let the shader program links all the shaders it has. Then we can bind the shader program to future render calls.

Whiling linking the shaders, the out parameters of the previous shader will be linked to the in parameters of the next shader based on the **name and type of the variable**.

## Shader Variables
### Vertex Attribute
Each vertex contains a collection of data that's needed for the shaders to use, it can be more than just the position of the vertex. For example, a vertex can contain the 3D coordinate, color, uv-mapping, normal, etc..., each of these property is called a *vertex attribute*.

Since usually **vertex shader** is the first shader in render pipeline, we'll need to specify the vertex attributes that will be used in vertex shader, and pass it on through variables to the other shaders through out the pipeline.

> Recall that when we copy vertex data to the gpu through VAO, the data just an array of numbers, so we need to tell OpenGL how to interpret those numbers, or how to map them into each vertex attribute to the shader. 

For example, the vertices we copied onto the gpu may looks like this:
```cpp
float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};    
```
Note that for each row (each vertex), other than the 3D coordinate, it also contains the color of that vertex.

Our vertex data now looks like the following:
![[moreVertexAttributes.png]]

To tell the OpenGL that the first 3 numbers means to be the position of the vertex, and the next 3 numbers means to be the color of the vertex, we'll need to call `glVertexAttribPointer` to set them as two vertex attributes of each vertex.

###### glVertexAttribPointer
```cpp
glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
```
`glVertexAttribPointer` takes 6 parameters:
- index: the location value (set on vertex shader) for the vertex attribute
- size: number of components/elements per vertex attribute, must be 1-4
- type: the data type of the array
- normalized: if the data should be clamped to $[-1,1]$ for signed value and $[0,1]$ for unsigned value.
- stride:the offset in **byte** between consecutive vertex attributes.
- ptr: the offset of the first component of the first vertex attribute in the array.


> There is a maximum number of vertex attributes we are allowed to declare limited by the hardware. We can query the limit through OpenGL function call. (OpenGL guarantees a minimum of 16 4-component vertex attribute available)

```cpp
int maxAttrs;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttrs);
```

##### Set vertex attribute values for shader
For each vertex attribute we need, we specify it as a variable in the following format:
```cpp
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;
```
where *location* needs to match what we set in the opengl c++ code using the `glVertexAttribPointer` function, the first parameter will be the location we need in shader code.

> It is also possible to omit the `layout (location = 0)` specifier and query for the attribute locations in your OpenGL code via `glGetAttribLocation`

To set the *pos* vertex attribute for the vertex shader:
```cpp
// the stride parameter is 6 since there are 6 elements until the next position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
glEnableVertexAttribArray(0);
```

To set the *color* vertex attribute for the vertex shader:
```cpp
// the offset is 3 *sizeof(float) since there are 3 elements before the first color vertex attribute in the array
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(3*sizeof(vertices[0])));
glEnableVertexAttribArray(1);
```

### Uniform Variables in shader
*Uniforms* are another way to pass data **from application on cpu to the shaders on gpu**. *Uniforms* are global, which means unique **per shader program object**, and can be accessed from any shader at any stage in the shader program. 

> We only need to declare uniform variables in the shader that uses them.

##### Set uniform variable
After generating and retrieving a shader id from open gl:
```cpp
shaderId = glCreateProgram()
```

We can set the value for uniform parameters that's defined in the shader in 2 steps:
1. Get the location id of the variable in shader:
```cpp
var1Id=glGetUniformLocation(shaderId, "variableName");
```

2. Set the value of the variable by using the Id and calling the function with corresponding type:
```cpp
vec3Id = glGetUniformLocation(shaderId,"someVec3VarName");
glUniform3f(vec3Id, 1.0f, .5f, .0f);
```

> Note that for finding the uniform location we don't need to use the shader first, since the id of the shader program object is provided in the query. However when setting the values of uniform variables we need to **use the shader** first.

`glUniform` uses specific postfix for various type of the uniform types we want to set, some of the postfix are:
- f: float
- i: int
- ui: unsigned int
- 3f: 3 floats
- fv: float vector/array

For matrix type, we use the glm library function:
```cpp
glm::mat4 someMatrix{1.0f};
glUniformMatrix4fv(var1Id, 1, GL_FALSE, glm::value_ptr(someMatrix))
```

