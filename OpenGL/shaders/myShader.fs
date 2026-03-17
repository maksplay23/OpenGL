#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D ourTexture;
uniform sampler2D shadowMap;
uniform vec3 color;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 sunDir;

vec3 normal;
vec3 lightDir;

void main()
{
    float ambientStrength = 1.0;

    vec3 color = texture(ourTexture, TexCoord).rgb;
    color *= ambientStrength;

    vec3 lightDir = normalize(lightPos - FragPos);  

    float diff = max(dot(normalize(Normal), lightDir), 0.0);

    FragColor = vec4(color, 1.);
}