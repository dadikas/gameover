#pragma once

namespace gameover::core
{
    class Window
    {
    public:
        virtual bool Create();
        virtual void Shutdown();
        virtual void PumpEvents();

        virtual void GetSize(int& w, int& h);

        virtual void BeginRender();
        virtual void EndRender();

        virtual ~Window() = default;
    };


}