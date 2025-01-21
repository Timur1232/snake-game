#version 330 core

uniform float iRadius;
uniform float iThickness;
uniform float iFade;
uniform vec2 iPosition;
uniform vec2 iResolution;
uniform vec3 iColor;

out vec4 FragColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    float aspect = iResolution.x / iResolution.y;
    uv.x *= aspect;
    
    float radius = iRadius;
    radius -= 1.0;
    
    vec2 pos = iPosition.xy;
    pos = (pos / iResolution.xy * 2.0 - 1.0);
    pos.x *= aspect;
    pos.y = -pos.y;
    uv -= pos;
    
    float fade = iFade;
    float thickness = iThickness;

    float dist = 1.0 + radius - length(uv);
    float alpha = smoothstep(0.0, fade, dist) * smoothstep(thickness + fade, thickness, dist);

    vec4 color = vec4(iColor, 1.0);
    color = color * alpha + gl_FragColor.rgba * (1.0 - alpha);

    FragColor = color;
}