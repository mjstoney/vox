#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 offset;
//layout (location = 3) in int boolData; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec3 normal;


void main()
{   

  
        //gl_Position = vec4(100000.0, 100000.0, 100000.0, 1.0); 

        vec3 pos = aPos + offset;
        normal = vec3(model * vec4(aNormal, 1.0));
        fragPos = vec3(model * vec4(pos, 1.0));
        gl_Position = projection * view * model * vec4(pos + offset, 1.0);
    
}