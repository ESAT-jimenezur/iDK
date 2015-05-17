#include "../include/dev/gpumanager.h"


namespace iDK{

  namespace dev{

    // Allocs buffer space
    void GPUManager::newBuffer(EDK3::ref_ptr<Buffer> * b){
      b->allocT<iDK::dev::Buffer>();
    }

    // Allocs shader space
    void GPUManager::newShader(EDK3::ref_ptr<Shader>* s){
      s->allocT<iDK::dev::Shader>();
    }

    // Allocs program space
    void GPUManager::newProgram(EDK3::ref_ptr<Program>* p){
      p->allocT<iDK::dev::Program>();
    }

    // Enable the attributes
    void GPUManager::enableVertexAttribute(
      const EDK3::dev::Buffer *buffer,
      const unsigned int attribute_index,
      const EDK3::Type type,
      const bool normalized = false,
      const unsigned int offset = 0,
      const unsigned int stride = 0){

      buffer->bind(EDK3::dev::Buffer::Target::kTarget_Vertex_Data);

      glVertexAttribPointer(attribute_index, 1, type, normalized, stride, (void *)offset);
      glEnableVertexAttribArray(attribute_index);
    }

    // Disable the attributes
    void GPUManager::disableVertexAttribute(const unsigned int attrib_index){
      glDisableVertexAttribArray(attrib_index);
    }

    // Draw elements
    void drawElements(
      const iDK::dev::GPUManager::DrawMode mode,
      unsigned int count,
      const EDK3::dev::Buffer *buffer,
      const EDK3::Type element_type = EDK3::Type::T_USHORT,
      const unsigned int offset = 0){

      GLenum mode_e, type_e;

      switch (mode){
        case EDK3::dev::GPUManager::kDrawMode_Triangles:
          mode_e = GL_TRIANGLES;
          break;
        case EDK3::dev::GPUManager::kDrawMode_TriangleStrip:
          mode_e = GL_TRIANGLE_STRIP;
          break;
        case EDK3::dev::GPUManager::kDrawMode_Points:
          mode_e = GL_POINTS;
          break;
        case EDK3::dev::GPUManager::kDrawMode_Lines:
          mode_e = GL_LINES;
          break;
        case EDK3::dev::GPUManager::kDrawMode_LineStrip:
          mode_e = GL_LINE_STRIP;
          break;
        case EDK3::dev::GPUManager::kDrawMode_LineLoop:
          mode_e = GL_LINE_LOOP;
          break;
        default:
          printf(" *** This shouldnt be here *** ");
          break;
      }

      switch (element_type){
        case EDK3::Type::T_UBYTE:
          type_e = GL_UNSIGNED_BYTE;
          break;
        case EDK3::Type::T_USHORT:
          type_e = GL_UNSIGNED_SHORT;
          break;
        case EDK3::Type::T_UINT:
          type_e = GL_UNSIGNED_INT;
          break;
        default:
          printf(" *** This shouldnt be here *** ");
          break;
        }

      buffer->bind(EDK3::dev::Buffer::Target::kTarget_Elements);
      glDrawElements(mode_e, count, type_e, (void*)offset);
    }


  } //_ end dev namespace

} //_ end iDK namespace