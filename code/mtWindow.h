#ifndef TM_WINDOW_H
#define TM_WINDOW_H

#include <Windows.h>
#include <GL/gl.h>
#include <stdint.h>

namespace mt {

    struct window_info
    {
        int Width;
        int Height;
        const char* Title;
        bool Keys[256];
    };

    typedef BOOL(WINAPI wglSwapInterval_t) (int interval);

    class Window
    {
    private:

        window_info m_Data;

        static LRESULT CALLBACK StaticWindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);

        HWND m_Window;
        HDC m_DeviceContext;
        HGLRC m_OpenGLContext;

        wglSwapInterval_t* wglSwapInterval;
        bool m_ShouldClose;

        void CreateOpenGLContext();

    public:
        Window(int Width, int Height, const char* Title);
        void Init();
        void Update();
        void SetVSync(bool value);
        void Clear(float r, float g, float b);

        HWND GetWindow()const {return m_Window;}
        bool GetKey(char Key) const {return m_Data.Keys[Key];}
        bool ShoudClose()const {return m_ShouldClose;}
        window_info* GetInfo() {return &m_Data;}
        int GetWidth()const {return m_Data.Width;}
        int GetHeight()const {return m_Data.Height;}
    };

    Window::Window(int Width, int Height, const char* Title)
    {
        m_Data.Width = Width;
        m_Data.Height = Height;
        m_Data.Title = Title;
        m_ShouldClose = false;

        m_DeviceContext = 0;
        m_OpenGLContext = 0;

        ZeroMemory(m_Data.Keys, sizeof(m_Data.Keys));
    }

    void Window::Init()
    {
        WNDCLASS WindowClass = {};
        WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        WindowClass.lpfnWndProc = StaticWindowProc;
        WindowClass.hInstance = GetModuleHandle(0);
        //WindowClass.hIcon = 0;
        //WindowClass.hCursor = 0;
        WindowClass.lpszClassName = "ENGINE_GL";

        if(RegisterClassA(&WindowClass))
        {
            m_Window = CreateWindowExA(0, WindowClass.lpszClassName, m_Data.Title,
                                          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                          CW_USEDEFAULT, CW_USEDEFAULT,
                                          m_Data.Width, m_Data.Height,
                                          0, 0, GetModuleHandle(0), this);
        }
    }

    void Window::CreateOpenGLContext()
    {
        PIXELFORMATDESCRIPTOR PixelFormatDescription = {};
        PixelFormatDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        PixelFormatDescription.nVersion = 1;
        PixelFormatDescription.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        PixelFormatDescription.iPixelType = PFD_TYPE_RGBA;
        PixelFormatDescription.cColorBits = 32;
        PixelFormatDescription.cDepthBits = 32;
        PixelFormatDescription.iLayerType = PFD_MAIN_PLANE;

        int PixelFormat = ChoosePixelFormat(m_DeviceContext, &PixelFormatDescription);
        bool PixelFormatResult = SetPixelFormat(m_DeviceContext, PixelFormat, &PixelFormatDescription);

        if(!PixelFormatResult)
        {
            OutputDebugString("Error Creating OpenGLContext\n");
        }

        m_OpenGLContext = wglCreateContext(m_DeviceContext);
        wglMakeCurrent(m_DeviceContext, m_OpenGLContext);

        wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
        glViewport(0, 0, m_Data.Width, m_Data.Height);
    }

    void Window::Clear(float r, float g, float b)
    {
    	glClearColor(r, g, b, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::Update()
    {
        MSG Message;
        while(PeekMessageA(&Message, m_Window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        SwapBuffers(m_DeviceContext);
    }

    void Window::SetVSync(bool value)
    {
        if(wglSwapInterval)
        {
            wglSwapInterval((int)value);
        }
    }

    LRESULT Window::WindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
    {
        switch(uMessage)
        {
        case WM_CREATE:
        {
            m_DeviceContext = GetDC(m_Window);
            CreateOpenGLContext();
        }break;
        case WM_SIZE:
        {
            m_Data.Width = LOWORD(lParam);
            m_Data.Height = HIWORD(lParam);
            glViewport(0, 0, m_Data.Width, m_Data.Height);
        }break;
        case WM_CLOSE:
        case WM_DESTROY:
        {
            m_ShouldClose = true;
        }break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
            m_Data.Keys[wParam] = true;
        }break;
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            m_Data.Keys[wParam] = false;
        }break;
        default:
        {
            return DefWindowProcA(hWindow, uMessage, wParam, lParam);
        }break;
        };

        return 0;
    }

    LRESULT CALLBACK Window::StaticWindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
    {
        Window* Parent;
        if(uMessage == WM_NCCREATE)
        {
            Parent = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLongPtr(hWindow, GWLP_USERDATA, (LONG_PTR)Parent);
        }

        Parent = (Window*)GetWindowLongPtr(hWindow, GWLP_USERDATA);
        if(!Parent)
        {
            return DefWindowProc(hWindow, uMessage, wParam, lParam);
        }

        Parent->m_Window = hWindow;
        return Parent->WindowProc(hWindow, uMessage, wParam, lParam);
    }
}

#endif
