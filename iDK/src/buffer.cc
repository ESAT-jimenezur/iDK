#include "../include/dev/buffer.h"

namespace iDK{

  namespace dev{

    // Buffer class constructor
    Buffer::Buffer(const Buffer&){}
    

    /* Buffer initialization */
    void Buffer::init(unsigned int size){
      // This method can be called more than once
      // Thats why we check if is not 0
      if (data_size_ != 0){
        release();
      }
      data_size_ = size;

      // Generates -1- buffer (stored on buffer_id_)
      glGenBuffers(1, &buffer_id_);

      // Bind the generated buffer to a target (Array Buffer)
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);

      // Creates a new data store for the current buffer (target)
      glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
    }
    

    /* Buffer bind 
     * 
     * This method is used to bind the buffer to its data
     * If data is elements, bind to ELEMENT_ARRAY_BUFFER
     * If its Vertex, to an ARRAY_BUFFER
     */
    void Buffer::bind(const Buffer::Target t) const{
      switch (t){
        case EDK3::dev::Buffer::Target::kTarget_Elements:
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_);
          break;
        case EDK3::dev::Buffer::Target::kTarget_Vertex_Data:
          glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
          break;
        default:
          printf(" *** This shouldnt be called *** ");
          break;
      }
    }


    // Returns the data size of the current buffer
    unsigned int Buffer::size() const{
      return data_size_;
    }


    // Uploads the data to the current buffer
    void Buffer::uploadData(const void *data, unsigned int size, unsigned int offset){
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id_);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    // Deletes the curren buffer
    void Buffer::release(){
      glDeleteBuffers(1, &buffer_id_);
    }
  
  } //_ End dev namespace

}//_ End iDK namespace