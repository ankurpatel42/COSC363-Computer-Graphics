#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;
uniform mat4 norMatrix;
uniform vec4 lightPos;

out vec4 oColor;

void main()
{
	vec4 white = vec4(1.0);
	vec4 grey = vec4(0.2);
	vec4 material = vec4(1.0, 0.64, 0.45, 1.0);
	float shininess = 100.0;

	vec4 posnEye = mvMatrix * position;
	vec4 normalEye = norMatrix * vec4(normal, 0);
	vec4 lgtVec = normalize(lightPos - posnEye); 
	vec4 viewVec = normalize(vec4(-posnEye.xyz, 0)); 
	vec4 halfVec = normalize(lgtVec + viewVec); 

	vec4 ambient = grey * material;
	float diffTerm = max(dot(lgtVec, normalEye), 0);
	vec4 diffuse = material * diffTerm;
	float specTerm = max(dot(halfVec, normalEye), 0);
	vec4 specular = white *  pow(specTerm, shininess);
	
	gl_Position = mvpMatrix * position;
	oColor = ambient + diffuse + specular;     
}

