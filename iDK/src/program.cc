#include "../include/dev/program.h"

namespace iDK{

  namespace dev{

    // Program class constructor
    // Creates a program in our program_id_
    Program::Program(){
      program_id_ = glCreateProgram();
    }


    // Attach the shader to our Program
    void Program::attach(EDK3::dev::Shader *shader){

      // FIX
      // shader_id_ = shader->internal_id();
      glAttachShader(program_id_, shader_id_);
    }


    // Links the current program
    bool Program::link(EDK3::scoped_array<char> *link_log = 0L){
      // Link the program
      glLinkProgram(program_id_);

      GLsizei program_lenght;
      GLint program_size, program_linked;

      glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &program_size);
      glGetProgramiv(program_id_, GL_LINK_STATUS, &program_linked);

      // If link failed (Log can be generated withot any fail too)
      // save the log and return it
      if (link_log != 0L){
        link_log->alloc(program_size);
        glGetProgramInfoLog(program_id_, program_size, &program_lenght, link_log->get());
      }

      // Check if was succesfully linked
      if (program_linked == GL_TRUE){
        return true;
      }else{
        return false;
      }

    }


    // Installs our program in current render state
    void Program::use() const{
      glUseProgram(program_id_);
    }


    // Returns the location of a attribute variable by name
    int Program::get_attrib_location(const char *name) const{
      return glGetAttribLocation(program_id_, name);
    }


    // Returns the location of a uniform position by name
    int Program::get_uniform_position(const char *name) const{
      return glGetUniformLocation(program_id_, name);
    }


    // Sets the uniform value depending on value type
    void Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const float *value) const{
      switch (uniform_type){
        case EDK3::Type::T_FLOAT_1:
          glUniform1fv(uniform_pos, 1, value);
          break;
        case EDK3::Type::T_FLOAT_2:
          glUniform2fv(uniform_pos, 1, value);
          break;
        case EDK3::Type::T_FLOAT_3:
          glUniform3fv(uniform_pos, 1, value);
          break;
        case EDK3::Type::T_FLOAT_4:
          glUniform4fv(uniform_pos, 1, value);
          break;
        case EDK3::Type::T_MAT_2x2:
          glUniformMatrix2fv(uniform_pos, 1, false, value);
          break;
        case EDK3::Type::T_MAT_3x3:
          glUniformMatrix3fv(uniform_pos, 1, false, value);
          break;
        case EDK3::Type::T_MAT_4x4:
          glUniformMatrix4fv(uniform_pos, 1, false, value);
          break;
        default:
          printf(" *** This shouldnt be called *** ");
          break;
      }
    }


    // Sets the uniform value depending on value type
    void Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type,const int *value) const{
      switch (uniform_type){
      case EDK3::Type::T_INT_1:
        glUniform1iv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_INT_2:
        glUniform2iv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_INT_3:
        glUniform3iv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_INT_4:
        glUniform4iv(uniform_pos, 1, value);
        break;
      default:
        printf(" *** This shouldnt be called *** ");
        break;
      }
    }


    // Sets the uniform value depending on value type
    void Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const unsigned int *value) const{
      switch (uniform_type){
      case EDK3::Type::T_UINT_1:
        glUniform1uiv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_UINT_2:
        glUniform2uiv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_UINT_3:
        glUniform3uiv(uniform_pos, 1, value);
        break;
      case EDK3::Type::T_UINT_4:
        glUniform4uiv(uniform_pos, 1, value);
        break;
      }
    }


    // Returns the program ID
    unsigned int Program::internal_id() const{
      return program_id_;
    }

  } //_ End dev namespace

} //_ End iDK namespace