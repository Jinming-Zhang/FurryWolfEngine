#### shaders
- After linked a shader to a shader program, can that shader be used again to link to other shader programs?
- when is safe to delete a shader then
- Vertex attribute means each property that we need for the shader, such as position is a vertex attribute, color is another vertex attribute, etc...
- Is vertex shader the first shader in render pipeline (for setting up vertex attribute)

#### textures
- Is texture unit global to all shader programs?
- Is it okey that when binding texture unit on C++, is using macro `GL_TEXTURE0`, and when setting the uniform sampler value in shader, use hardcoded number 0-15

#### camera
- all shaders should have same view matrix?
- what's the default view/camera position, direction in OpenGL (position at origin at pointing toward -z axis?)
- Why by convention the camera is pointing to the negative z axis.
- Overcome lookat flip when pitch outside of (-90, 90)