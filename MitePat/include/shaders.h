#include <string>

// Please watch below how there're crappy undefines, that's because Qt devs had to go out of their way iserting their dirty defines for precision
// Borking the out vec4 for fragment shaders in the process!
// Those shilly arsholes are so up in the frameworks, that they don't care basic outputs are shreded

namespace MITED_SHADERS
{
  static const char* vertex = R""""(
#version 300 es
  #undef lowp
  #undef mediump
  #undef highp

  precision mediump float; 

  in vec2 pos;

  void main() 
  {
	  gl_Position = vec4(pos,0.0,1.0);
  }
  )"""";

  static const char* fragment = R""""(
#version 300 es
  #undef lowp
  #undef mediump
  #undef highp

  precision mediump float; 

  out vec4 fragColor;

  void main()
	{
    fragColor = vec4(1.0,1.0,1.0,1.0);
  }
  )"""";

}
