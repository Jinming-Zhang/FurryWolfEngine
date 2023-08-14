# Mesh Rendering Setup
1. Define mesh by vertices in world position
2. For each frame
	1. Declare the shader program to use
	2. Setup the values of the matrices that will be used by the shader
		1. Affine transform matrix, define the translation of the mesh
		2. View matrix, define the matrix that translate object's coordinate from world space to camera space, depends on camera's properties (i.e. position, rotation...)
		3. Projection matrix, defines the field of view of the camera.