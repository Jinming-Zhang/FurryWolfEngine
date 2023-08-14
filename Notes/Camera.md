# Camera
## Coordinate Systems
There are 5 different coordinate systems that are important throughout the render pipeline:
- Local space (object's local coordinate)
- World space (world's coordinate)
- View  space (camera's coordinate, defined by the eye position, forward direction, field of view, etc.)
- Clip space (clipped coordinate, defined by the projection method (*orthographic / perspective*), clip plane distance, etc.)
- Screen space. (finally mapped clip space (in *NCD*) to pixels on screen).

Usually the input of the **vertex shader** begins from *local space*, and ends in **clip space**, which is in *normalized device coordinates*.

Through out the process:
1. vertices are transformed from their local object space to world space using *model* matrix
2. the world space then is transformed to view (camera) space using *view* matrix (this is a process of change of basis). 
3. finally the view space then is transformed to clip space using *projection* matrix (this is to clip out points outside of the specified range and normalize the points to *NDC* ).

After all, OpenGL will use the definition from  `glViewport` to transform the points from  *NDC*  to screen coordinates.

![[CameraCoordinateSystems.png]]


## Camera / View space
OpenGL doesn't have a notion of Camera, it only has a default rendering position. In order to simulate camera, we can transform all the objects in the scene in the reverse direction that we want the camera to move, so it gives an illusion that we are moving the camera.

> *View coordinates*: All the vertex coordinates as seen from the camera's perspective as the origin of the scene.
> *View matrix*: Transform all the world coordinates into view coordinates that is relative to the camera's **position** and **direction**.

To define a view port coordinate, we need the camera/eye position, looking direction, then we can calculate the basis of the view coordinate, as well as the view matrix that can transform the world coordinate to view coordinate.
![[CameraViewSpace.png]]

> Note that the view space is a **right-hand** coordinate system.

### Define camera coordinate
1. Define the position of the camera.
2. Define the looking target of the camera to get the positive z axis (forward vector).
3. Calculate right-direction vector by cross product forward vector with the world-up vector (0,1,0).
4. Calculate the camera-up vector by cross product right-direction vector with forward vector
```cpp
// forward axis
glm::vec3 zAxis{position - cameraTarget};
zAxis = glm::normalize(zAxis);
// right axis of view space
glm::vec3 worldUp{.0f, 1.f, .0f};
glm::vec3 rightAixs =glm::normalize(glm::cross(worldUp, zAxis));
// up axis of view space
glm::vec3 up{glm::normalize(glm::cross(zAxis, rightAixs))};
```

## Camera/View Space matrix
Let R be the right vector, U be the up vector, D be the (forward) direction vector, and P be the world position of camera, we can multiply a point in word space with the following LookAt matrix to transform it to coordinates in camera space.
$$LookAt=
\begin{bmatrix}
R_x & R_y & R_z & 0 \\
U_x & U_y & U_z & 0 \\
D_x & D_y & D_z & 0 \\
0 & 0 & 0 & 1 \\
\end{bmatrix}*
\begin{bmatrix}
1 & 0 & 0 & -P_x \\
0 & 1 & 0 & -P_y \\
0 & 0 & 1 & -P_z \\
0 & 0 & 0 & 1 \\
\end{bmatrix}$$
> A *LookAt* matrix creates a view matrix that loos at a given target.
> Note that *LookAt* matrix is the inverse matrix of the matrix that transform points from camera coordinates to world coordinates.
> More on [[#Change of basis]].

In `glm` library, the function that also does exactly this:
```cpp
// remember to also apply projection matrix as well 
glm::mat4 view = glm::lookAt(cameraPosition, targetPosition, worldUpVector);
```

With the view matrix, we can set it in the uniform variable in vertex shader, and have the points transformed to camera space (position seen from the camera's point of view).

## Free Camera Movement
In OpenGL, the positive Z axis is pointing out through the screen toward us.

> By default OpenGL has a view space with origin at (0, 0, 0) and pointing towards the world's -z axis.
> To make the camera has the same behavior as OpgenGL, we also make the camera so that it points to the **negative** z axis in its view space. (*which means the positive z axis is pointing to the opposite direction the camera is facing*).

#### Walk the Camera
Recall the purpose of a camera is to define a view matrix, which is defined by:
1. view / eye position
2. forward / looking direction
3. world's up vector

So walking the camera means updating the *view/eye position*.

Also note that OpenGL doesn't have a notion of a camera, which means it always renders at the same location. While we are defining the view matrix of the camera, what we want is really the (*opposite*) transformation matrix for all the world objects.

So, when we want to update the camera's position, what we actually need to do is to update the camera's position in an opposite direction than we want, which means it will update all world's objects' position in a opposite direction relative to where we want the camera to be.

#### Look Around
The feature of looking around basically is the same as determine the forward vector of the camera, and add it onto the camera's position to determine the look direction (still remember to negate the vector, since the camera is facing the negative z-axis).

###### Euler Angles
Pitch, Yaw and Roll are three terms that defines a rotation:
![[PitchYawRoll.png]]

Given a pitch, yaw, and roll value, we can convert them into a 3D vector that represents a new direction vector.
###### yaw
The yaw determines the x and y component of the direction vector, it representing the degree we look around horizontally. We can get the value of x and y component by computing $cos(yaw)$ and $sin(yaw)$ respectively.

Below is a top-down view of the world's coordinate:
![[trigYaw.png]]

###### pitch
The pitch determines the y component of the direction vector, it also affects the x and z components as well, since:
1. When we look up or down, we effectively lower the value of x and z component.
2. When we look over 90 degree or -90 degree, we might negating the sign of x and z component.
To get the y value from pitch, we can use $sin(pitch)$.
To get its effect on x and z component, we can use $cos(pitch)$.
![[pitchDirection.png]]

## Z-buffer
OpenGL **automatically** creates a *z-buffer*, or *depth buffer* that stores all the depth information. 

###### Depth Testing
Similar to *color buffer*, *depth buffer* stores within each fragment its Z value. Whenever the fragment wants to output its color, OpenGL compare its depth value with the *depth buffer*, if the value is behind the current value, then the new value is discarded, otherwise the new value will override the old value.

*Depth testing* is disabled by default, we need to enable it using the `glEnable` call with the proper configuration enum, then the *depth testing* process will be automatically done for us by OpenGL.
```cpp
glEnable(GL_DEPTH_TEST);
```
Then we also need to clear the depth buffer every frame:
```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```


## Review
The overall rendering process is on an shader-object basis, which means the screen is rendered object by object, based on the currently activated shader.

The overall process will be looked like the following:
1. Define a list of objects, each with its own vertices and drawing method (by vertices or indexed draw, etc.), as well as its transform/model matrix that defines its world position.
2. Define a camera, that has a position and projection method.
3. The rendering loop will loop through each object, for each object:
	1. Bind the object's vao (set up vertices data for rendering)
	2. update the uniform variables of the active shader, this tells the shader how to treat currently bound vertices:
	3. first get the world position of the object vertices using its transform/model matrix
	4. Then get the view (and) projectioin matrix from camera.
	5. ... some other shader settings as necessary
	6. Call the render function, at this time, the variables for the shader should be set up, active vao vertices should be the object to draw, then the render function will take the vao data and active shader to render the scene. Any vertex outside of the viewport after the sequence of transformation (model->view->projection) will be discarded.
## Appendix 
###### Change of basis
The process of changing basis is relatively simple.
- First, we representing the new basis in the form of our original world coordinates, and construct a column matrix, with each column set to our new basis.
- Second, we multiply points in our original world coordinates with the matrix, the result will be the points in our new coordinate system.

Think of the coordinates in original space to be a span of the basis of the original space, the each column of the transformation matrix tells us how to map each basis from the original space to the basis of the target space.

For example, in a 2D space, the world coordinate has a basis of $[1,0], [0,1]$ . 
Then we define another basis to be $[2,1],[-1,-1]$.
(In this new world, $[2,1]$ will be 1 unit to the right, and $[-1, -1]$ will be one unit to the up).
Note that the basis is represented in the span of the original world coordinate.
Say we have a point in new space: $[5,8]$, this means it spans 5 unit of the new basis' right axis, and 8 unit of the new basis' up axis.

We know that the right axis of the new basis is equal to the span of **2 times of the original world's right axis** and **1 times the original world's up axis**.
So the right coordinate in the original world basis is $5*[2,1]=[10,5]$, this is the point in the world space that representing the span of the right axis of the new space.

Similarly, the new up coordinate is the span of **-1 times the original world's right axis** and **-1 times the original world's up axis**.
So the new up coordinate in the world basis is $8*[-1, -1]=[-8,-8]$

Now we have the span of the new basis representing in our original world basis, we can simply add them and get the transformed point vector in our original space:
$[2,-3]$

The transformation matrix will be the following:
$$\begin{bmatrix}
2 & -1 \\
1 & -1 
\end{bmatrix}$$

Therefore, the matrix that with the column vectors of the basis of the new coordinate system represented using original coordinate system, we can transform points from the new coordinate system back to the original coordinate system.
The inverse of such matrix allows us to transform the points in the original coordinate system to the points in the new coordinate system.

