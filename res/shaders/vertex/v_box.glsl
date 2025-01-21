#version 330 core

layout (location = 0) in vec2 v_position;

uniform vec2 iPosition;
uniform vec2 iSize;
uniform vec2 iResolution;

void main()
{
    mat2 scale = mat2(
        iSize.x / iResolution.x / 2.0, 0.0,
        0.0, iSize.y / iResolution.y /2.0
    );
    vec2 pos = v_position;
    pos.x *= iResolution.y / iResolution.x;
    gl_Position = vec4(pos * scale, 0.0, 1.0);
    vec2 delta = (iPosition.xy / iResolution.xy) * 2.0 - 1.0;
    delta.y = -delta.y;
    gl_Position += vec4(delta, 0.0, 0.0);
}