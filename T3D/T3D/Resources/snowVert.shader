varying out vec4 P;
varying out vec3 N;
varying out float height;

void main()
{
    // Transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	height = gl_Vertex.y;

	P = gl_ModelViewMatrix * gl_Vertex;
	N = normalize(gl_NormalMatrix * gl_Normal);
}