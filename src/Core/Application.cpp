#include "Application.hpp"

namespace HYT
{
    void Application::pushLayer(Layer * layer)
    {
        m_layers.push_back(layer);
        layer->init();
    }

    void Application::popLayer(Layer * layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if(it != m_layers.end())
        {
            layer->terminate();
            m_layers.erase(it);
        }
    }
} // namespace HYT
