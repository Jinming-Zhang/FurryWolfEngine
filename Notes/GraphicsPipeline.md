Process of transforming 3D coordinates to 2D pixels.

Everything is 3D in OpenGL, a large part of OpenGL's work is about transforming all 3D coordinates to 2D pixels.

Two main parts of graphics pipeline:
1. Transform 3D coordinates into 2D coordinates.
2. Transform the 2D coordinates into actual colored pixels.

Some of the shaders in certain pipeline stage are configurable by developers:
![[RenderPipelineOverview.png]]

> There are no default vertex/fragment shaders on the GPU, so in modern OpenGL we are required to define at least a vertex and fragment shader of our own.

### Explaination
The input of the pipeline is a list of Vertex Data, where a Vertex is a collection of data per 3D coordinate.
Vertex Data is represented using `vertex attribbutes` which can contain any data we'd like.

OpenGL uses *primitives* to determine the render type to use to render the given list of vertex data (render as points, lines or triangles), i.e. `GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP`.

#### Primitive Assembly
The primitive assembly stage takes all the vertices that form one or more primitives and assembles all the points in the primitive shape given.

#### Vertex Shader
The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates, and allow us to do some basic processing on the vertex attributes.


#### Geometry Shader
Geometry shader takes in a collection of vertices that form a primitive, and has the ability to generate other shapes by emitting new vertices to form new or other primitives.

#### Rasterization
Rasterization stage maps the resulting primitives to the corresponding pixels on the final screen for the fragment shader to use.
`Clipping` is performed before fragment shaders to run. Clipping discards all fragments that are outside of the view.

### Fragment Shader

> A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

The main purpose of the fragment shader is to calculate the final color of a pixel and is usually the stage where all the advanced OpenGL effects occur.
Usually in the fragment shader, it will contain the data about 3D scene that can be used to calculate the final pixel color (lights, shadow, etc.).

### Alpha test and blending
This stage checks the corresponding depth and stencil value of the fragment, and uses those to check if the resulting fragment is in front or behind other objects and should be discarded accordingly.