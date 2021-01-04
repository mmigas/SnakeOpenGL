#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout (location = 1) in vec4 in_Color;

out vec4 out_Color;

void main() {
    const float right = 640.0;
    const float left = 0.0;
    const float top = 0.0;
    const float bottom = 640.0;
    const float far = 1.0;
    const float near = -1.0;


    mat4 viewMatrix = mat4(vec4(2.0 / (right - left), 0, 0, 0),
    vec4(0, 2.0 / (top - bottom), 0, 0),
    vec4(0, 0, -2.0 / (far - near), 0),
    vec4(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1));
    gl_Position = viewMatrix * position;

    out_Color = in_Color;
}

    #shader fragment
    #version 330 core
out vec4 FragColor;

in vec4 out_Color;

void main() {
    FragColor = out_Color;
}