#version 330 core

uniform vec2 iPosition;
uniform float iThickness;
uniform float iFade;
uniform vec2 iResolution;
uniform float iRadius;
uniform vec3 iColor;

out vec4 FragColor;

void main()
{
    // Normalized pixel coordinates (from -1 to 1)
    vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    float aspect = iResolution.x / iResolution.y;
    uv.x *= aspect;

    vec2 delta = iPosition.xy;
    delta = (delta / iResolution.xy * 2.0 - 1.0);
    delta.x *= aspect;
    delta.y = -delta.y;
    uv -= delta;

    float dist = length(uv);
    float alpha = smoothstep(iRadius - iThickness, iRadius - iThickness + iFade, dist) * smoothstep(iRadius, iRadius - iFade, dist);

    vec4 color = vec4(iColor, 1.0);
    color = color * alpha + gl_FragColor.rgba * (1.0 - alpha);

    FragColor = color;
}