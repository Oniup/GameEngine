layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_Uv;

out vec2 o_Uv;

void main() 
{
    gl_Position = vec4(a_Position.xyz, 1.0);
    o_Uv = a_Uv;
};

