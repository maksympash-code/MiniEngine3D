#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 uViewPos;

uniform Material uMaterial;
uniform PointLight uLight;

void main() {
    vec3 norm = normalize(Normal);

    vec3 lightDir = normalize(uLight.position - FragPos);

    // Ambient
    vec3 ambient = uMaterial.ambient * uLight.color;

    // Diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uMaterial.diffuse * diff * uLight.color;

    // Specular
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uMaterial.specular * spec * uLight.color;

    // Attenuation
    float distance = length(uLight.position - FragPos);
    float attenuation = 1.0 / (
    uLight.constant +
    uLight.linear * distance +
    uLight.quadratic * distance * distance
    );

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}