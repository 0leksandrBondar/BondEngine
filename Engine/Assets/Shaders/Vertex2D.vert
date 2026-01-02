//#version 460 core
//
//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec2 aTexCoord;
//
//out vec2 TexCoord;
//
//uniform mat4 viewMat;
//uniform mat4 modelMat;
//uniform mat4 projectionMat;
//
//void main()
//{
//    TexCoord = aTexCoord;
//    //gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 0.0, 1.0);
//    gl_Position = projectionMat  vec4(aPos, 0.0, 1.0);
//}



#version 330 core
layout (location = 0) in vec4 vertex;// <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}

