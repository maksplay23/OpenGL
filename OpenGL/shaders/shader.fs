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

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Выполняем деление перспективы
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
 
    // Преобразуем в диапазон [0,1]
    projCoords = projCoords * 0.5 + 0.5;
 
    // Получаем наиболее близкое значение глубины, исходя из перспективы с точки зрения источника света (используя диапазон [0,1] fragPosLight в качестве координат)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
 
    // Получаем глубину текущего фрагмента, исходя из перспективы с точки зрения источника света
    float currentDepth = projCoords.z;
 
    // Проверяем, находится ли текущий фрагмент в тени
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
 
    return shadow;
}  

void main()
{
    float specularStrength = 0.5;
    float ambientStrength = 0.9;

    vec3 color = texture(ourTexture, TexCoord).rgb;
    vec3 ambient = 0.8 * color;
    
    normal = normalize(Normal);
    lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    
    vec3 specular = vec3(0.3) * spec; // подразумеваем яркий белый свет

    float shadow = ShadowCalculation(FragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;  
    FragColor = vec4(lighting, 1.0);
    //FragColor = vec4(ambient + diffuse + specular, 1.0);
}