#version 330 core

layout (location = 0) in vec2 v_position;

uniform vec2 iPosition;
uniform float iRadius;
uniform vec2 iResolution;

void main()
{
    mat2 scale = mat2(
        iRadius, 0.0,
        0.0, iRadius
    );
    gl_Position = vec4(v_position * scale, 0.0, 1.0);
    vec2 delta = (iPosition.xy / iResolution.xy) * 2.0 - 1.0;
    delta.y = -delta.y;
    gl_Position += vec4(delta, 0.0, 0.0);
}