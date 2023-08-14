## Affine Transformation
Translate Matrix:
$$\begin{bmatrix}
1 & 0 & 0 & tx \\
0 & 1 & 0 & ty \\
0 & 0 & 1 & tz \\
0 & 0 & 0 & 1 
\end{bmatrix}$$
Scale Matrix:
$$\begin{bmatrix}
sx & 0 & 0 & 0 \\
0 & sy & 0 & 0 \\
0 & 0 & sz & 0 \\
0 & 0 & 0 & 1 
\end{bmatrix}$$

Rotation Matrix:
X Rotation:
$$\begin{bmatrix}
1 & 0 & 0 & 0 \\
0 & cos~\theta & -sin~\theta & 0 \\
0 & sin~\theta & cos~ \theta & 0 \\
0 & 0 & 0 & 1 
\end{bmatrix}$$
Y Rotation:
$$\begin{bmatrix}
cos~\theta & 0 & sin~\theta & 0 \\
0 & 1 & 0 & 0 \\
-sin~\theta & 0 & cos~ \theta & 0 \\
0 & 0 & 0 & 1 
\end{bmatrix}$$
Z Rotation:
$$\begin{bmatrix}
cos~\theta & -sin~\theta & 0 & 0 \\
sin~\theta & cos~\theta & 0 & 0 \\
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1 
\end{bmatrix}$$
