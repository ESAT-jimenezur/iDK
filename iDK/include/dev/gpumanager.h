#ifndef __GPUMANAGER__
#define __GPUMANAGER__

#include "EDK3\ref_ptr.h""
#include "EDK3\referenced.h"
#include "EDK3\constants.h"
#include "EDK3\texture.h"

#include "EDK3\dev\gpumanager.h"
#include "EDK3\dev\opengl.h"
#include "EDK3\dev\buffer.h"


namespace iDK {
  class Engine;

  namespace dev {

    class Shader;
    class Program;
    class Buffer;
    class Framebuffer;

    class GPUManager : public EDK3::dev::GPUManager {
    public:
      // Singleton Pattern
      static GPUManager *Instance();

      // Replace GPU Manager Implementation
      // Must be done before creating the Window
      static void ReplaceGPUManagerImplementation(GPUManager *g);

      // Called by Engine once render context is set and ready to start drawing
      virtual void onStart() {}

      // Called by Engine once at before shuting down the render context
      virtual void onFinish() {}

      // 1st Implement buffer mechanism
      virtual void newBuffer(EDK3::ref_ptr<Buffer> *output);
      // 2nd Implement Shader-Program-Uniforms
      virtual void newShader(EDK3::ref_ptr<Shader> *output);
      virtual void newProgram(EDK3::ref_ptr<Program> *output);

      virtual void newTexture1D(const EDK3::Texture::Format internal_format, const unsigned int size, EDK3::ref_ptr<EDK3::Texture> *output);
      virtual void newTexture2D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, EDK3::ref_ptr<EDK3::Texture> *output);
      virtual void newTexture3D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, const unsigned int depth, EDK3::ref_ptr<EDK3::Texture> *output);

      enum FrameBufferElement {
        kFrameBufferColor = 1 << 0,
        kFrameBufferDepth = 1 << 1,
        kFrameBufferStencil = 1 << 2,
      };

      virtual void clearFrameBuffer(
        const float rgba[4],
        const unsigned int FrameBufferOrMask =
        kFrameBufferColor | kFrameBufferDepth);

      virtual void enableVertexAttribute(
        const EDK3::dev::Buffer *buffer,
        const unsigned int attribute_index,
        const EDK3::Type type,
        const bool normalized = false,
        const unsigned int offset = 0,
        const unsigned int stride = 0);

      virtual void disableVertexAttribute(const unsigned int attrib_index);

      enum DrawMode {
        kDrawMode_Triangles,
        kDrawMode_TriangleStrip,
        kDrawMode_Points,
        kDrawMode_Lines,
        kDrawMode_LineStrip,
        kDrawMode_LineLoop
      };

      virtual void drawElements(
        const DrawMode mode,
        unsigned int count,
        const Buffer *buffer,
        const EDK3::Type element_type = EDK3::T_USHORT,
        const unsigned int offset = 0) const;

      enum CompareFunc {
        kCompareFunc_Never,          // false -> always fails
        kCompareFunc_Less,           // a < b
        kCompareFunc_LessOrEqual,    // a <= b
        kCompareFunc_Equal,          // a == b
        kCompareFunc_NotEqual,       // a != b
        kCompareFunc_GreaterOrEqual, // a >= b
        kCompareFunc_Greater,        // a > b
        kCompareFunc_Always          // true -> always passes
      };

      virtual void enableDepthTest(const CompareFunc f);
      virtual void disableDepthTest();

      enum FaceType {
        kFace_Back,
        kFace_Front,
        kFace_FrontAndBack
      };

      virtual void enableCullFaces(const FaceType f);
      virtual void disableCullFaces();

      virtual void enableScissor(
        int x, int y,
        unsigned int width,
        unsigned int height);
      virtual void disableScissor();

      virtual void changeColorMask(
        const bool red = true,
        const bool green = true,
        const bool blue = true,
        const bool alpha = true);
      virtual void changeDepthMask(bool enable = true);

      virtual void newFramebuffer(EDK3::ref_ptr<Framebuffer> *output);
      virtual void bindDefaultFramebuffer();

      static void CheckGLError(const char *msg = 0L);
      static void EnableCheckGLError(bool v);

      // Called by window manager when gpu-manager needs to be initialized
      // Do not call manually.
      void doOnStart();
      void doOnFinish();
    protected:
      GPUManager();
      virtual ~GPUManager();

    private:
      GPUManager(const GPUManager&);
      GPUManager& operator=(const GPUManager&);
      static GPUManager *default_;
    };


  }

}

#endif // __GPUMANAGER__
