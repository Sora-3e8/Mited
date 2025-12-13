#include <string>

namespace MITED_SHADERS
{
  const char* Vertex = R""""(
  #version 330

  uniform mat4 VIEWMAT;
  in vec2 vertexBuffer;
  out vec2 PointCoord;

  void main() 
  {
    gl_Position = VIEWMAT * vec4(vertexBuffer.xy,vertexBuffer.y,1.0);
    PointCoord = gl_Position.xy;
  }
  )"""";

  const char* Fragment = R""""(
  #version 330
  
  out vec4 fragColor;
  layout(pixel_center_integer) in vec4 gl_FragCoord;
  in vec2 PointCoord;
  void main()
  {
    fragColor = vec4(gl_FragCoord.x,0,0, 1);
  }
  )"""";
}
