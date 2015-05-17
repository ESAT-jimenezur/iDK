#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "EDK3\dev\program.h"
#include "EDK3\dev\gpumanager.h"
#include "EDK3\dev\opengl.h"

namespace iDK{
  namespace dev{

    class Shader;
    class Uniform;

    class Program : public EDK3::dev::Program {

      public:
        virtual void attach(EDK3::dev::Shader *shader) = 0;
        virtual bool link(EDK3::scoped_array<char> *link_log = 0L) = 0;
        virtual void use() const = 0;
        virtual int get_attrib_location(const char *name) const = 0;
        virtual int  get_uniform_position(const char *name) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const EDK3::Type uniform_type,
          const float *) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const EDK3::Type uniform_type,
          const int*) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const EDK3::Type uniform_type,
          const unsigned int*) const = 0;

        virtual unsigned int internal_id() const = 0;
      protected:
        Program() {}
        virtual ~Program() {}

      private:

        GLuint program_id_, shader_id_;

        Program(const Program&);
        Program& operator=(const Program&);
      };


   }

}


#endif //__PROGRAM_H__