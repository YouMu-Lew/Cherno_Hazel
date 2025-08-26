#pragma once

#include "Hazel/Layer.h"

import ApplicationEvent;
import KeyEvent;
import MouseEvent;

namespace Hazel {

    class HAZEL_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };

} // namespace Hazel
