#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "EDK3\dev\buffer.h"

namespace iDK{
  namespace dev{

    class Buffer : public EDK3::dev::Buffer{
      public:
        
        enum Target {
          kTarget_Vertex_Data,
          kTarget_Elements,
        };

        virtual void init(unsigned int size) = 0;
        virtual void bind(const Target t) const = 0;
        virtual unsigned int size() const = 0;
        virtual void uploadData(
          const void *data,
          unsigned int size,
          unsigned int offset = 0) = 0;
        virtual void release() = 0;

      protected:
        Buffer() {}
        virtual ~Buffer() {}

      private:
        Buffer(const Buffer&);
        Buffer& operator=(const Buffer&);

        
    };

  }
}

#endif //__BUFFER_H__