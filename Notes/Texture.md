# Texture
To map a texture to a triangle, we need to specify for each vertex about which part of the texture it corresponds to, so each vertex will have a *texture coordinate* associated with.

*Texture coordinate* range from $[0,1]$ with origin at the bottom-left. *Sampling* is the process of retrieving the color using the texture coordinate.

![[textureCoordinate.png]]


## Texture wrapping
There are 4 options in OpenGL for how to sample the texture for **each coordinate** when the coordinate is outside the range of $[0,1]$.
- `GL_REPEAT`: repeats the image
- `GL_MIRRORED_REPEAT`: mirror the texture with each repeat
- `GL_CLAMP_TO_EDGE`: clamp the coordinates, results in a stretched edge pattern.
- `GL_CLAMP_TO_BORDER`: coordinates outside the range are now given a user-specified border color.

These options can be set via the `glTexParameteri` function, (similar for setting the border color):
```cpp
// set the border color
float clr[]={1.f, 1.f, 1.f, 1.f};
glTexParameterfv(gl_texture_2d, gl_texture_border_color, clr);
// set the x axis wrapping option
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
```

## Texture Filtering
Texture filtering is the strategy applied to decide which texture pixel (aka *texel*) color to use when sampling with a texture coordinate.

This is necessary because the textore coordinates are given in float, so in the case when we mapping low resolution texture to a large object, it's possible that several sections of the object will map to the same texel color.

The crosshair in the below example represents the actual given texture coordinate.
##### GL_NEAREST
Pick the texel color of the texel that has its center closest to the actual texture coordinate. This usually results in hard edges.
![[nearestTextureFiltering.png]]
##### GL_LINEAR
Perform a bi-linear interpolation for the color of texels around the actual texture coordinate. This usually results in blurred edges.
![[linearTextureFiltering.png]]

We can specify different texture filtering options for when the texture is scaled upward(*magnifying*) or downward(*minifying*), so we can for example, use nearest filtering when textures are scaled downward, and linear filtering when textures are scaled upward.

Texture filtering option can be set via the `glTexParameter*` as well:
```cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

## Mipmaps
Mipmaps a re a collection of texture images where each subsequent texture is twice as small as the previous one.
![[MipmapsSample.png]]

In the situation when we need to sample a high resolution texture for a distant object, the object may only produce a few fragments.
To sample the texture color, the texture might be down-scaled a lot, which means two adjacent fragments may sampling texels that are far away from each other.

>This is because since each vertex is associated with a texture coordinate, when a distant large object only produce few fragment, then the adjacent screen pixels will very likely hitting vertices that span large part of the object and hence resulting in sample very different texture coordinates, which result in potential very different color on adjacent screen pixels.

*Mipmaps* will use different texture based on the object's distance, for further object it will sample the smaller texture (if configured) for the mipmap.

We can use `glGenerateMipmap` function to let the OpenGL generate mipmaps for us.

Similar to texture filtering, we can configure how OpenGL should sample the mipmap to use among the following options:
- GL_NEAREST_MIPMAP_NEAREST: take the nearest mipmap and sample it using closest neighbour
- GL_LINEAR_MIPMAP_NEAREST: take the nearest mipmap and sample it using bi-linear interpolation
- GL_NEAREST_MIPMAP_LINEAR: linear interpolate between two mipmaps and sample the interpolated level using nearest neighbour
- GL_LINEAR_MIPMAP_LINEAR: linear interpolate between two mipmaps and sample the interpolated level using bi-linear interpolation

We can use `glTexParameteri` to configure the mipmap filtering mode:
```cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR)
// note we do NOT use mipmaps filtering for magnification, since mipmaps' purpose is to deal with downscaled textures.
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
```

## Generating a texture
First we need to load the image into a char array, to do this we can use the `stb_image` library:
```cpp
int width;
int height;
int nrChannels;
unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
// copy data over gpu
// ...
// free the image
stbi_image_free(data);

```

Creating a texture object is similar as creating other objects in OpenGL:
```cpp
glGenTextures(1, &textureId);
glBindTexture(GL_TEXTURE_2D, textureId);
```

###### glTexImage2D
To generating the texture with the image data we just loaded, we can use the `glTexImage2D` function:
```cpp
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
// remember to generate a mipmap as well, OpenGL will need at least a level 0 mipmap for the texture object
glGenerateMipmap(GL_TEXTURE_2D);
```
The function takes 9 parameters:
`glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* data)`
- target: there are different types of textures, `GL_TEXTURE_1D`, `GL_TEXTURE_2D`, `GL_TEXTURE_3D`, `GL_TEXTURE_CUBE_MAP`, etc.. Here we are using 2D texture so texture bounded to other type won't be affected.
- level: the mipmap level that we want to create a texture for if we want to set each mipmap level manually.
- internalFormat: format that we want to store the texture
- width: width of the texture
- height: height of the texture
- border: always be 0 for legacy stuff
- format: format of the source image
- type: the data type for the source image, in our case we loaded the source image in char byte array, which is equivalent to unsigned byte.
- data: actual data of the image.

> If needed,remember to set necessary texture filtering mode and mipmaps mode after generated and bound the texture object.

## Applying textures
Since we need to have each vertex associated with a texture coordinate, we need to add more data to the vertex data we defined before, and hence an addition vertex attribute as well.
The updated vertex data will look like the following:
```cpp
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
```
![[vertexDataWithTextureCoordinates.png]]

Then we can add a vertex attribute for the texture coordinate and send it to the vertex shader, then let the vertex shader pass the data to fragment shader (this is to avoid of manually defining all the vertex color in vertex data array):
```cpp
// vertex texture coordinate attribute
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
glEnableVertexAttribArray(2);
```

# Use Texture in Shader
Since fragment should have access to the texture object, GLSL has a built-in data type for texture object, called `sampler`. Each sampler variable has a corresponding location value that we can set in c++ code,  some graphics driver will have a default location for the sampler, if not, then we need to set the location manually. ([[#Texture Unit|more about texture unit]])

To sample the texture with the texture coordinate, we can use the `texture` function provided by GLSL.
The output if `texture` function is the filtered color of the texture sampled at the **interpolated** texture coordinate.

Texture is attached to a structure called `Texture Unit`, each Texture Unit has a unique ID. 
The sampler will access a Texture Unit by providing its ID, then gets the value from the texture that the Texture Unit has.
Different sampler2D can access the same texture.

## Texture Unit
We can assign a location value to each uniform *texture sampler* in the fragment shader, so we can have multiple textures at once in a fragment shader. Multiple textures can be used for different things, such as albedo, normal map, noise, etc.

The location of a texture is also known as a *texture unit*.

The default *texture unit* for a texture is 0, which is also the default active texture. Some graphics driver will have the default texture unit activated for us.
When we binding the texture on the C++ side, we are binding the texture to the currently active texture unit (default texture unit), and since the default texture unit on the shader is also 0, we effectively setting the only sampler to our texture.

When our shader needs to use multiple textures, either for blending, normal map or other purposes, we will need to activate the desired texture unit before binding the texture, and set the texture unit on the shader using `glUniform1i` function (remember that texture unit is the location value of the texture sampler).

OpenGL should have minimum 16 texture units available for us, we can activate using `GL_TEXTURE0` - `GL_TEXTURE15`:
```cpp
// active a texture unit and bind a texture to it
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

// active another texture unit and bind a texture to it
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

// set the texture unit (the location of the sampler) on shader to the desired texture unit

glUniform1i(sampleId, textureId);
```


> Note that when we active texture unit and binding the texture, we don't need to provide shader program id. This means the texture unit are global and can be access by every shader program.
> We still need to active the shader before we setting the uniform variable (texture unit for the texture samplers).


