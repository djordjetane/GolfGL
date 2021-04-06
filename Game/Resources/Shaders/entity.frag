#version 330 core
out vec4 FragColor;

struct Material
{        
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
  
in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec3 lightColor = vec3(1,1,1);

void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightColor * (spec * material.specular);  
        
        
    FragColor = vec4( ambient + diffuse + specular , 1.0);
}





/*
void main()
{
    vec3 ambientDiffuse = texture(material.diffuse, TexCoords).rgb;

    vec3 ambient = light.ambient * ambientDiffuse;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * ambientDiffuse;    

    vec3 viewDir = normalize(viewPos - FragPos);    
    vec3 reflectionDir = reflect(-lightDir, norm);
    float spec = pow( max( dot(viewDir, reflectionDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;        

    FragColor = vec4(ambient + diffuse + specular, 1.0);        
}
*/