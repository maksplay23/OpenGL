#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform vec3 cameraDir;
uniform vec3 cameraRight;
uniform vec3 cameraUp;

uniform vec3 sunDir;

uniform float fov;
uniform float aspect;

void main()
{
    vec2 p = uv * 2.0 - 1.0;

    p.x *= aspect;

    float tanFov = tan(radians(fov) * 0.5);

    vec3 ray = normalize(
        cameraDir +
        p.x * tanFov * -cameraRight +
        p.y * tanFov * cameraUp
    );

    vec3 topColor = vec3(0.2,0.4,0.8);
    vec3 horizonColor = vec3(0.9,0.9,1.0);

    float t = ray.y * 0.5 + 0.5;
    vec3 sky = mix(horizonColor, topColor, t);

    float sun = pow(max(dot(ray, normalize(sunDir)),0.0),2000.0);

    vec3 sunColor = vec3(1.0,0.9,0.6) * sun * 10.0;

    FragColor = vec4(sky + sunColor,1.0);
}