#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FaceNormal;  
in vec3 FragPos; 

in vec3 LightingColor; 

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform bool blinn;
uniform bool pongFlat;
uniform bool isLuz;
uniform bool off;
uniform bool gurond;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform Material material;
uniform Light light;

uniform float R;
uniform float G;
uniform float B;

void main()
{
	
	if(isLuz || gurond ){
		if(!(isLuz) || gurond){
			FragColor = vec4(LightingColor * vec3(R,G,B), 1.0);
		}else{
			FragColor = vec4(lightColor * vec3(R,G,B), 1.0);
		}
	}
	else{
		float shininess = 8.0;
		vec3 Mambient = vec3(0.0215, 0.1745, 0.0215);
		vec3 Mdiffuse = vec3(0.07568, 0.61424, 0.07568);
		vec3 Mspecular = vec3(0.633, 0.727811, 0.633);
		// ambient
		float ambientStrength = 0.4;
		vec3 ambient = light.ambient * material.ambient;
  		float specStr;
		float spec;
		vec3 diffuse;

		if(pongFlat){
			// diffuse 
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(light.position - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			diffuse = (material.diffuse * diff) * light.diffuse;

			// specular
			specStr = 0.5;
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			spec = 0.0;
			if(blinn)
			{
				vec3 halfwayDir = normalize(lightDir + viewDir);  
				spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
			}
			else
			{
				vec3 reflectDir = reflect(-lightDir, Normal);
				spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			}
		}
		else{
			// diffuse 
			vec3 norm = normalize(FaceNormal);
			vec3 lightDir = normalize(light.position - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			diffuse = (material.diffuse * diff) * light.diffuse;

			// specular
			specStr = 0.5;
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			spec = 0.0;
			if(blinn)
			{
				vec3 halfwayDir = normalize(lightDir + viewDir);  
				spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
			}
			else
			{
				vec3 reflectDir = reflect(-lightDir, FaceNormal);
				spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			}
		}
    

		vec3 specular = material.specular * spec * light.specular;
		vec3 result;
		if(off){
			 result = vec3(R,G,B);
		}else{
			 result = (ambient + diffuse + specular) * vec3(R,G,B);
		}
		//vec3 result = (ambient + diffuse + specular) * vec3(R,G,B);
		FragColor = vec4(result, 1.0);
	}
} 
