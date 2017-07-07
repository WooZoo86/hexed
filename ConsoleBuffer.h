#pragma once

#include <Windows.h>

class ConsoleBuffer
{
    public:
        ConsoleBuffer(HANDLE stdoutHandle);
        ~ConsoleBuffer();

        void Write(int x, int y, WORD attributes, const char* format, ...);
        void FillLine(int y, char c, WORD attributes);
        void FillRect(int x, int y, int width, int height, char c, WORD attributes);
        void Clear();
        void OnWindowResize(int width, int height);
        void Flush(bool fullDraw);

    private:
        int m_width;
        int m_height;
        CHAR_INFO* m_buffer;
        CHAR_INFO* m_backBuffer;
        HANDLE m_stdoutHandle;
};
