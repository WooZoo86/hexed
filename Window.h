#pragma once

#include <Windows.h>
#include "ConsoleBuffer.h"
#include <vector>
#include <algorithm>

class Window
{
    public:
		Window(const char* filename);
        ~Window();

        virtual void OnWindowRefreshed();
		virtual void OnWindowResized(int width, int height);
        virtual void OnKeyEvent(const KEY_EVENT_RECORD& ker);

        static void SetConsoleBuffer(ConsoleBuffer* buffer);
        static void Add(Window* window);
        static void Remove(Window* window);
        static void Resize(int width, int height);
        static void Refresh();
        static void KeyEvent(const KEY_EVENT_RECORD& ker);

    protected:
        const char* m_filename;
        int m_width;
        int m_height;

        static ConsoleBuffer* s_consoleBuffer;

    private:
        static std::vector<Window*> s_windows;
};

inline void Window::SetConsoleBuffer(ConsoleBuffer* buffer)
{
    s_consoleBuffer = buffer;
}

inline void Window::Add(Window* window)
{
    s_windows.push_back(window);
}

inline void Window::Remove(Window* window)
{
    auto iter = std::remove(s_windows.begin(), s_windows.end(), window);
    s_windows.erase(iter);
}

inline void Window::Resize(int width, int height)
{
    s_consoleBuffer->OnWindowResize(width, height);
    for (size_t i = 0; i < s_windows.size(); i++)
        s_windows[i]->OnWindowResized(width, height);
}

inline void Window::Refresh()
{
    for (size_t i = 0; i < s_windows.size(); i++)
        s_windows[i]->OnWindowRefreshed();
    s_consoleBuffer->Flush();
}

inline void Window::KeyEvent(const KEY_EVENT_RECORD& ker)
{
    for (size_t i = 0; i < s_windows.size(); i++)
        s_windows[i]->OnKeyEvent(ker);
}

inline void Window::OnKeyEvent(const KEY_EVENT_RECORD& ker)
{
}
