#include "hzpch.h"

export module GraphicsContext;

export namespace Hazel {

    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

} // namespace Hazel
