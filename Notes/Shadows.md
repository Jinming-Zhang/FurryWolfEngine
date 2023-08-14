# Shadows
For each light, generate a depth texture from the point of view of that light
In the final render pass (from the camera's perspective), check against the distance of the pixel against the distance from each depth texture

## Generate Shadow Map
#### Shadow map shader
Vertex shader will need the translation matrices (affine transform, projection) of the current light component to find the relative position of each vertex relative to the light source.

Fragment shader stays the same

Depth value will be automatically populated throughout the render pipeline

#### Generate depth texture
Use the shadow map shader to render the scene for each light source with provided resolution
1. Set shader to use
2. specify resolution through `glViewport`
3. Set the buffer that the texture should write to
