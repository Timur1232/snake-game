#version 330 core

// uniform float iThickness;
// uniform float iFade;
// uniform vec2 iResolution;
// uniform vec2 iSize;
// uniform vec2 iPosition;
uniform vec3 iColor;

// out vec4 FragColor;

void main()
{
    // vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    // float aspect = iResolution.x / iResolution.y;
    // uv.x *= aspect;

    // vec2 delta = iPosition.xy;
    // delta = (delta / iResolution.xy * 2.0 - 1.0);
    // delta.x *= aspect;
    // delta.y = -delta.y;
    // uv -= delta;

    // vec2 pos = iPosition.xy / iResolution.xy * 2.0 - 1.0;
    // pos.x *= aspect;

    // float alpha = smoothstep(pos.x, pos.x + iFade, uv.x) * smoothstep(pos.x + iSize.x, pos.x - iFade + iSize.x, uv.x) * 
    //     smoothstep(pos.y, pos.y + iFade, uv.y) * smoothstep(pos.y + iSize.x, pos.y - iFade + iSize.x, uv.y);

    // vec4 color = vec4(iColor, 1.0);
    // color = color * alpha + gl_FragColor.rgba * (1.0 - alpha);

    // FragColor = color;

    gl_FragColor = vec4(iColor, 1.0);
}