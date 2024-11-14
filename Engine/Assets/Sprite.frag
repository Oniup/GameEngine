out vec4 FragColor;
uniform vec3 u_ShapeColor;

in vec2 o_Uv;

void main()
{
    FragColor = vec4(o_Uv.xy, 1.0, 1.0);
};
