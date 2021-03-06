#ifndef __SHADER__
#define __SHADER__

#include "EDK3\referenced.h"
#include "EDK3\scoped_array.h"
#include "EDK3\dev\gpumanager.h"
#include "EDK3\dev\opengl.h"

namespace iDK {
  namespace dev {

    class Shader : public EDK3::Referenced {
    public:
      // Type of the shader
      enum Type {
        kType_Invalid,
        kType_Vertex,
        kType_Fragment,
        kType_Geometry,
      };

      // Loads the source of the Shader
      virtual void loadSource(
        const EDK3::Type shader_type,
        const char *source,
        const unsigned int source_size) = 0;

      // Compiles the shader. Optionally it can fill the output log of the compilation
      // Returns true if the shader was successfully compiled
      virtual bool compile(EDK3::scoped_array<char> *output_log = NULL) = 0;
      // Checks if the shader is compiled
      virtual bool is_compiled() const = 0;

      // Returns the type of shader
      virtual const EDK3::Type type() const = 0;

      virtual unsigned int internal_id() const = 0;

    protected:
      Shader() {}
      virtual ~Shader() {}

    private:

      GLuint shader_id_;
      bool shader_compiled_;
      EDK3::Type shader_type_;

      Shader(const Shader&);
      Shader& operator=(const Shader&);
    };

  }
}

#endif // __SHADER__
