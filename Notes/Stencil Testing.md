# Stencil Testing
Stencil test can be performed after the fragment shader has processed, and it can be used to discard fragments.

Stencil test uses another buffer called the *stencil buffer* that we are allowed to update during rendering.

#### Stencil Buffer
Stencil buffer usually contains *8-bit* value per pixel, which means a value of range $[0,256]$ we can use of our liking.

Here is a general flow of using stencil buffer:
1. Enable writing to the stencil buffer.
2. Render objects, updating the content of the stencil buffer.
3. Disable writing to the stencil buffer.
4. Render (other) objects, discarding certain fragments based on the content of the stencil buffer.

To enable stencil testing and clear the stencil buffer every frame:
```cpp
glEnable(GL_STENCIL_TEST);
glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

#### Stencil Mask
Similar to `glDepthMask`, we can use the function `glStencilMask` to control how the value should be written to the buffer.
We can set a bitmask using `glStencilMask`, which the value will be **AND**ed with the stencil value we want to write.
By default the bitmask is set to all **1**s, so it wont effect what we are writing to the buffer.

If we set the bitmask value to all **0**s, then its the same that we wont write any value to the stencil buffer.
```cpp
glStencilMask(0xFF); // set all bits to 1
glStencilMask(0x00); // set all bits to 0 and we wont be able to write to the buffer.
```

#### Stencil functions
Similar to depth testing, we can use some functions that OpenGL provides to control when a stencil test should pass using `glStencilFunc`, and how it should affect the stencil buffer with `glStencilOp`.

`glStencilFunc(GLenum func, GLint ref, GLuint mask)` will use the `mask` value to **AND** with the `ref` value and the stored value, the use the specified function to test against the *value in the stencil buffer* with the *reference value*.

Available `func` are GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, GL_NEVER and GL_ALWAYS.

`glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass)` allows us to specify the action to take for each of the options:
- `sfail`: action to take if the stencil test fails.
- `dpfail`: action to take if the stencil test passes and depth test fails.
- `dppass`: action to take if both tests pass

Available actions are listed bellow:

|Action|Description|
|---|---|
|`GL_KEEP`|The currently stored stencil value is kept.|
|`GL_ZERO`|The stencil value is set to `0`.|
|`GL_REPLACE`|The stencil value is replaced with the reference value set with glStencilFunc.|
|`GL_INCR`|The stencil value is increased by `1` if it is lower than the maximum value.|
|`GL_INCR_WRAP`|Same as GL_INCR, but wraps it back to `0` as soon as the maximum value is exceeded.|
|`GL_DECR`|The stencil value is decreased by `1` if it is higher than the minimum value.|
|`GL_DECR_WRAP`|Same as GL_DECR, but wraps it to the maximum value if it ends up lower than `0`.|
|`GL_INVERT`|Bitwise inverts the current stencil buffer value.|



# Sample outline shader
