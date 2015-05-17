#include "../include/dev/shader.h"

namespace iDK{

  namespace dev{

    // Shader class constructor
    Shader::Shader(){}


    // Loads the shader source code
    void Shader::loadSource(
      const EDK3::Type shader_type,
      const char *source,
      const unsigned int source_size){

      shader_type_ = shader_type;

      switch (shader_type){
      case kType_Vertex:
        shader_id_ = glCreateShader(GL_VERTEX_SHADER);
        break;
      case kType_Fragment:
        shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
        break;
      case kType_Geometry:
        shader_id_ = glCreateShader(GL_GEOMETRY_SHADER);
        break;
      default:
        printf("Shader type wrong");
        break;
      }

      int size = source_size;

      glShaderSource(shader_id_, 1, &source, &size);
    }
    

    // Compiles the current shader. Fill the output log, if it failed or not
    bool Shader::compile(EDK3::scoped_array<char> *output_log = NULL){
      shader_compiled_ = false;

      // Compiles the passed shader
      glCompileShader(shader_id_);

      GLsizei lenght;
      GLint shader_size;
     
      glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &shader_size);
      
      // Fills the ouput log with the results
      if (output_log != NULL){
        output_log->alloc(shader_size);
        glGetShaderInfoLog(shader_id_, shader_size, &lenght, output_log->get());
      }
      shader_compiled_ = true;

      return shader_compiled_;
    }


    // Returns the shader compilation status
    // If is compiled or not
    bool Shader::is_compiled() const{
      return shader_compiled_;
    }


    // Returns the current type of the shader
    const EDK3::Type Shader::type()const{
      return shader_type_;
    }


    // Returns the current shader id
    unsigned int Shader::internal_id()const{
      return shader_id_;
    }

  } //_ End dev namespace

} //_ End iDK namespace