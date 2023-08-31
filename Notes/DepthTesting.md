Previously we enabled *depth buffer* to prevent triangles rendering in the front while they are suppose to be behind other triangles.
*Depth value* is the value that the depth buffer stores, which is used to determine whether a fragment should be in the front or not.
# Depth Buffer
Similar to color buffer, depth buffer stores information per fragment and has the same width and height as the color buffer.
Depth buffer is *automatically* created by the windowing system and stores the depth value as a float, usually with with a precision of 16, 24, or 32 bits.

Depth testing is done in screen space **after** the *fragment shader and stencil test* is done. When depth testing is enabled, OpenGL tests the depth value of a fragment against the content in the *depth buffer*, if the test *pass*,  then the fragment is rendered and the depth value is updated.

### gl_FragCoord
The screen coordinates related directly with the `glViewport` function. In GLSL, we can access the screen space coordinates by using the built-in function `gl_FragCoord`: the x and y component of the return value represents the screen space coordinates, the z component represents the depth value of that fragment.

To enable depth test, call
```cpp
glEnable(GL_DEPTH_TEST);
```
and clear it ever frame with:
```cpp
glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
```
If we only want to check the depth buffer without write to it, call:
```cpp
glDepthMask(GL_FALSE);
```

There are a number of depth test functions available to us, we can set it to one of them by calling:
```cpp
glDepthFunc(GL_LESS);
```

Following is a list of available depth test functions:

|Function|Description|
|---|---|
|`GL_ALWAYS`|The depth test always passes.|
|`GL_NEVER`|The depth test never passes.|
|`GL_LESS`|Passes if the fragment's depth value is less than the stored depth value.|
|`GL_EQUAL`|Passes if the fragment's depth value is equal to the stored depth value.|
|`GL_LEQUAL`|Passes if the fragment's depth value is less than or equal to the stored depth value.|
|`GL_GREATER`|Passes if the fragment's depth value is greater than the stored depth value.|
|`GL_NOTEQUAL`|Passes if the fragment's depth value is not equal to the stored depth value.|
|`GL_GEQUAL`|Passes if the fragment's depth value is greater than or equal to the stored depth value.|

## Depth Value Precision
