#include <string>

namespace MITED_SHADERS
{
  const char* Vertex = R""""(
  #version 330
  #ifdef GL_ES
  // Set default precision to medium
  precision mediump int;
  precision mediump float;
  #endif
  uniform mat4 VIEWMAT;
  in vec2 vertexBuffer;

  void main() 
  {
    gl_Position = vec4(vertexBuffer.x,0.0,vertexBuffer.y,1.0);
  }
  )"""";

  const char* Fragment = R""""(
  #version 330
  #ifdef GL_ES
  // Set default precision to medium
  precision mediump int;
  precision mediump float;
  #endif

  out vec4 fragColor;
  void main()
  {
    fragColor=vec4(1.0, 0.0, 0.0, 1.0);
  }
  )"""";
}
