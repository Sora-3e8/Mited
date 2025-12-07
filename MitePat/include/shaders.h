#include <string>

// Please watch below how there're crappy undefines, that's because Qt devs had to go out of their way iserting their dirty defines for precision
// Borking the out vec4 for fragment shaders in the process!
// Those shilly arsholes are so up in the frameworks, that they don't care basic outputs are shreded
// Why am I yapping here, because bakas are so self centered there's no way to report it unless you're business customer
// // Maybe check your cr*p before asking me to pay!
namespace MITED_SHADERS
{
  static const char* vertex = R""""(
#version 330 core
  
  uniform mat4 VIEWMAT;


  in vec2 pos;

  void main() 
  {
	  gl_Position = vec4(pos.x,0.0,pos.y,1.0);
  }
  )"""";

  static const char* fragment = R""""(
#version 330 core
out vec4 colorOutput;

void main()
{
  colorOutput = vec4(1.0,0.0,0.0,1.0);
}
  )"""";

}
