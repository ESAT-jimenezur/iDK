#ifndef __PROGRAM_H__
#define __PROGRAM_H__


namespace iDK{
  namespace dev{

    //class Shader;
    //class Uniform;

    class Program {

      public:
        //virtual void attach(Shader *) = 0;
        //virtual bool link(scoped_array<char> *link_log = 0L) = 0;
        virtual void use() const = 0;
        virtual  int get_attrib_location(const char *name) const = 0;
        virtual int  get_uniform_position(const char *name) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const Type uniform_type,
          const float *) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const Type uniform_type,
          const int*) const = 0;
        virtual void set_uniform_value(
          const int uniform_pos,
          const Type uniform_type,
          const unsigned int*) const = 0;

        /** returns the internal program ID*/
        virtual unsigned int internal_id() const = 0;
      protected:
        Program() {}
        virtual ~Program() {}

      private:
        Program(const Program&);
        Program& operator=(const Program&);
      };


    };

  }
}


#endif //__PROGRAM_H__