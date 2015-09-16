//-----------------------------------------------------------------------------
// Copyright (c) 2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
//
// This demo shows you how to import Alias|Wavefront OBJ and MTL files into
// your OpenGL applications. The OBJ file format is one of the most widely
// supported 3D file formats. All of the most popular 3D content creation
// packages includes support for this file format either natively or through
// third party plugins.
//
// Models are rendered using either the fixed function pipeline or the
// programmable pipeline. The fixed function pipeline is used on hardware that
// only supports OpenGL 1.x. The programmable pipeline is used on hardware that
// supports OpenGL 2.0 and higher. The supported GLSL shaders are per fragment
// Blinn-Phong and normal Mapping. Both support only a single fixed directional
// light source shining down the OpenGL default negative z-axis.
//
// Most of the time the per fragment Blinn-Phong shader will be used. The
// normal mapping shader will be used only when the OBJ model's MTL file
// includes a material that has a bump map (specified using the 'map_bump'
// command). This demo assumes that any bump map associated with a material
// will be a normal map. All other bump map formats are not supported.
//
// When the MTL file contains a material with a normal map this demo will
// generate smooth tangent vectors for the OBJ model. The smooth tangent
// vectors are generated by summing the triangle face tangent vectors of
// adjacent triangle faces and then normalizing the resulting tangent vector.
// The bitangent vectors are not generated here. They are calculated in the
// normal mapping shader's vertex shader.
//
// A minimal file menu is provided to enable OBJ files to be loaded at runtime.
// The demo includes drag and drop support for OBJ files. Drop an OBJ file onto
// the demo's window and the OBJ file will be loaded. Alternatively drop the
// OBJ file onto the demo's EXE file. The demo will launch and load the OBJ
// file.
//
// This demo is completely self contained. The two GLSL shaders are embedded
// into the demo's EXE file as resources.
//
// Left click and drag using the mouse to translate the model.
// Middle click and drag using the mouse to zoom in and out of the model.
// Right click and drag using the mouse to rotate the model.
//
//-----------------------------------------------------------------------------

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <commdlg.h>	// for open file dialog box
#include <shellapi.h>   // for drag and drop support
#include <GL/gl.h>
#include <GL/glu.h>
#include <cassert>
#include <cmath>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(_DEBUG)
#include <crtdbg.h>
#endif

//#include "bitmap.h"

#include "gl2.h"

#include "model_obj.h"
#include "resource.h"
#include "WGL_ARB_multisample.h"

#include <fstream.h>
using std::ios;


//-----------------------------------------------------------------------------
// Constants.
//-----------------------------------------------------------------------------

#define APP_TITLE "OpenGL OBJ Viewer"

// Windows Vista compositing support.
#if !defined(PFD_SUPPORT_COMPOSITION)
#define PFD_SUPPORT_COMPOSITION 0x00008000
#endif

// GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#define CAMERA_FOVY  60.0f
#define CAMERA_ZFAR  10.0f
#define CAMERA_ZNEAR 0.1f

#define MOUSE_ORBIT_SPEED 0.30f     // 0 = SLOWEST, 1 = FASTEST
#define MOUSE_DOLLY_SPEED 0.02f     // same as above...but much more sensitive
#define MOUSE_TRACK_SPEED 0.005f    // same as above...but much more sensitive

//-----------------------------------------------------------------------------
// Type definitions.
//-----------------------------------------------------------------------------

typedef std::map<std::string, GLuint> ModelTextures;

//-----------------------------------------------------------------------------
// Globals.
//-----------------------------------------------------------------------------

HWND                g_hWnd;
HDC                 g_hDC;
HGLRC               g_hRC;
HINSTANCE           g_hInstance;
int                 g_framesPerSecond;
int                 g_windowWidth;
int                 g_windowHeight;
int                 g_msaaSamples;
GLuint              g_nullTexture;
GLuint              g_blinnPhongShader;
GLuint              g_normalMappingShader;
float               g_maxAnisotrophy;
float               g_heading;
float               g_pitch;
float               g_cameraPos[3];
float               g_targetPos[3];
bool                g_isFullScreen;
bool                g_hasFocus;
bool                g_enableWireframe;
bool                g_enableTextures = true;
bool                g_supportsProgrammablePipeline;
bool                g_cullBackFaces = true;
ModelOBJ            g_model;
ModelTextures       g_modelTextures;

//-----------------------------------------------------------------------------
// Functions Prototypes.
//-----------------------------------------------------------------------------

void    Cleanup();
void    CleanupApp();
GLuint  CompileShader(GLenum type, const GLchar *pszSource, GLint length);
HWND    CreateAppWindow(const WNDCLASSEX &wcl, const char *pszTitle);

void    DrawFrame();
void    DrawModelUsingFixedFuncPipeline();


bool    Init();
void    InitApp();
void    InitGL();
void    LoadModel(const char *pszFilename);

void    Log(const char *pszMessage);
void    ProcessMenu(HWND hWnd, WPARAM wParam, LPARAM lParam);
void    ProcessMouseInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void    ReadTextFileFromResource(const char *pResouceId, std::string &buffer);
void    ResetCamera();
void    SetProcessorAffinity();
void    ToggleFullScreen();
void    UnloadModel();
void    UpdateFrame(float elapsedTimeSec);
void    UpdateFrameRate(float elapsedTimeSec);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//-----------------------------------------------------------------------------
// Functions.
//-----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
#if defined _DEBUG
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
#endif

    MSG msg = {0};
    WNDCLASSEX wcl = {0};

    wcl.cbSize = sizeof(wcl);
    wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wcl.lpfnWndProc = WindowProc;
    wcl.cbClsExtra = 0;
    wcl.cbWndExtra = 0;
    wcl.hInstance = g_hInstance = hInstance;
    wcl.hIcon = LoadIcon(0, IDI_APPLICATION);
    wcl.hCursor = LoadCursor(0, IDC_ARROW);
    wcl.hbrBackground = 0;
    wcl.lpszMenuName = MAKEINTRESOURCE(MENU_FIXED_FUNC);
    wcl.lpszClassName = "GLWindowClass";
    wcl.hIconSm = 0;

    if (!RegisterClassEx(&wcl))
        return 0;

    g_hWnd = CreateAppWindow(wcl, APP_TITLE);

    if (g_hWnd)
    {
        SetProcessorAffinity();

        if (Init())
        {
            ShowWindow(g_hWnd, nShowCmd);
            UpdateWindow(g_hWnd);

            while (true)
            {
                while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    if (msg.message == WM_QUIT)
                        break;

                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

                if (msg.message == WM_QUIT)
                    break;

                if (g_hasFocus)
                {
                    
                    DrawFrame();
                    SwapBuffers(g_hDC);
                }
                else
                {
                    WaitMessage();
                }
            }
        }

        Cleanup();
        UnregisterClass(wcl.lpszClassName, hInstance);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static char szFilename[MAX_PATH];

    switch (msg)
    {
    case WM_ACTIVATE:
        switch (wParam)
        {
        default:
            break;

        case WA_ACTIVE:
        case WA_CLICKACTIVE:
            g_hasFocus = true;
            break;

        case WA_INACTIVE:
            if (g_isFullScreen)
                ShowWindow(hWnd, SW_MINIMIZE);
            g_hasFocus = false;
            break;
        }
        break;

    case WM_CHAR:
        switch (static_cast<int>(wParam))
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;

        case 'r':
        case 'R':
            PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(MENU_VIEW_RESET, 0), 0);
            break;

        case 't':
        case 'T':
            PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(MENU_VIEW_TEXTURED, 0), 0);
            break;

        case 'w':
        case 'W':
            PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(MENU_VIEW_WIREFRAME, 0), 0);
            break;

        default:
            break;
        }
        break;

    case WM_COMMAND:
        ProcessMenu(hWnd, wParam, lParam);
        return 0;

    case WM_CREATE:
        DragAcceptFiles(hWnd, TRUE);
        break;

    case WM_DESTROY:
        DragAcceptFiles(hWnd, FALSE);
        PostQuitMessage(0);
        return 0;

    case WM_DROPFILES:
        DragQueryFile(reinterpret_cast<HDROP>(wParam), 0, szFilename, MAX_PATH);
        DragFinish(reinterpret_cast<HDROP>(wParam));

        try
        {
            if (strstr(szFilename, ".obj") || strstr(szFilename, ".OBJ"))
            {
                UnloadModel();
                LoadModel(szFilename);
                ResetCamera();
            }
            else
            {
                throw std::runtime_error("File is not a valid .OBJ file");
            }            
        }
        catch (const std::runtime_error &e)
        {
            Log(e.what());
        }
        return 0;

    case WM_SIZE:
        g_windowWidth = static_cast<int>(LOWORD(lParam));
        g_windowHeight = static_cast<int>(HIWORD(lParam));
        break;

    case WM_SYSKEYDOWN:
        if (wParam == VK_RETURN)
            PostMessage(hWnd, WM_COMMAND, MAKEWPARAM(MENU_VIEW_FULLSCREEN, 0), 0);
        break;

    default:
        ProcessMouseInput(hWnd, msg, wParam, lParam);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Cleanup()
{
    CleanupApp();

    if (g_hDC)
    {
        if (g_hRC)
        {
            wglMakeCurrent(g_hDC, 0);
            wglDeleteContext(g_hRC);
            g_hRC = 0;
        }

        ReleaseDC(g_hWnd, g_hDC);
        g_hDC = 0;
    }
}

void CleanupApp()
{
    UnloadModel();

    if (g_nullTexture)
    {
        glDeleteTextures(1, &g_nullTexture);
        g_nullTexture = 0;
    }

    if (g_supportsProgrammablePipeline)
    {
        glUseProgram(0);

        if (g_blinnPhongShader)
        {
            glDeleteProgram(g_blinnPhongShader);
            g_blinnPhongShader = 0;
        }

        if (g_normalMappingShader)
        {
            glDeleteProgram(g_normalMappingShader);
            g_normalMappingShader = 0;
        }
    }
}



HWND CreateAppWindow(const WNDCLASSEX &wcl, const char *pszTitle)
{
    // Create a window that is centered on the desktop. It's exactly 1/4 the
    // size of the desktop. Don't allow it to be resized.

    DWORD wndExStyle = WS_EX_OVERLAPPEDWINDOW;
    DWORD wndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
        WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    HWND hWnd = CreateWindowEx(wndExStyle, wcl.lpszClassName, pszTitle,
        wndStyle, 0, 0, 0, 0, 0, 0, wcl.hInstance, 0);

    if (hWnd)
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int halfScreenWidth = screenWidth / 2;
        int halfScreenHeight = screenHeight / 2;
        int left = (screenWidth - halfScreenWidth) / 2;
        int top = (screenHeight - halfScreenHeight) / 2;
        RECT rc = {0};

        SetRect(&rc, left, top, left + halfScreenWidth, top + halfScreenHeight);
        AdjustWindowRectEx(&rc, wndStyle, FALSE, wndExStyle);
        MoveWindow(hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);

        GetClientRect(hWnd, &rc);
        g_windowWidth = rc.right - rc.left;
        g_windowHeight = rc.bottom - rc.top;
    }

    return hWnd;
}


void DrawFrame()
{
    glViewport(0, 0, g_windowWidth, g_windowHeight);
    glClearColor(0.3f, 0.5f, 0.9f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CAMERA_FOVY,
        static_cast<float>(g_windowWidth) / static_cast<float>(g_windowHeight),
        CAMERA_ZNEAR, CAMERA_ZFAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(g_cameraPos[0], g_cameraPos[1], g_cameraPos[2],
        g_targetPos[0], g_targetPos[1], g_targetPos[2],
        0.0f, 1.0f, 0.0f);

    glRotatef(g_pitch, 1.0f, 0.0f, 0.0f);
    glRotatef(g_heading, 0.0f, 1.0f, 0.0f);

const ModelOBJ::Mesh *pMesh = 0;
    const ModelOBJ::Material *pMaterial = 0;
    const ModelOBJ::Vertex *pVertices = 0;
    ModelTextures::const_iterator iter;

    for (int i = 0; i < g_model.getNumberOfMeshes(); ++i)
    {
        pMesh = &g_model.getMesh(i);
        pMaterial = pMesh->pMaterial;
        pVertices = g_model.getVertexBuffer();

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

        if (g_enableTextures)
        {
            iter = g_modelTextures.find(pMaterial->colorMapFilename);

            if (iter == g_modelTextures.end())
            {
                glDisable(GL_TEXTURE_2D);
            }
            else
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, iter->second);
            }
        }
        else
        {
            glDisable(GL_TEXTURE_2D);
        }

            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, g_model.getVertexSize(),   g_model.getVertexBuffer()->position);
       
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, g_model.getVertexSize(), g_model.getVertexBuffer()->texCoord);
       
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, g_model.getVertexSize(),      g_model.getVertexBuffer()->normal);
    
       




        glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT, g_model.getIndexBuffer() + pMesh->startIndex);



           glDisableClientState(GL_NORMAL_ARRAY);

            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

            glDisableClientState(GL_VERTEX_ARRAY);
    }
}



bool Init()
{
    try
    {
        InitGL();
        InitApp();
        return true;
    }
    catch (const std::exception &e)
    {
        std::ostringstream msg;

        msg << "Application initialization failed!" << std::endl << std::endl;
        msg << e.what();

        Log(msg.str().c_str());
        return false;
    }    
}

void InitApp()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



    if (__argc == 2)
    {
        LoadModel(__argv[1]);
        ResetCamera();
    }
}

void InitGL()
{
    if (!(g_hDC = GetDC(g_hWnd)))
        throw std::runtime_error("GetDC() failed.");

    int pf = 0;
    PIXELFORMATDESCRIPTOR pfd = {0};
    OSVERSIONINFO osvi = {0};

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (!GetVersionEx(&osvi))
        throw std::runtime_error("GetVersionEx() failed.");

    // When running under Windows Vista or later support composition.
    if (osvi.dwMajorVersion > 6 || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 0))
        pfd.dwFlags |=  PFD_SUPPORT_COMPOSITION;

    ChooseBestMultiSampleAntiAliasingPixelFormat(pf, g_msaaSamples);

    if (!pf)
        pf = ChoosePixelFormat(g_hDC, &pfd);

    SetPixelFormat(g_hDC, pf, &pfd);

    g_hRC = wglCreateContext(g_hDC);
        
    wglMakeCurrent(g_hDC, g_hRC);
     

    GL2Init();

}



void LoadModel(const char *pszFilename)
{
    // Import the OBJ file and normalize to unit length.

    SetCursor(LoadCursor(0, IDC_WAIT));

    if (!g_model.import(pszFilename))
    {
        SetCursor(LoadCursor(0, IDC_ARROW));
        throw std::runtime_error("Failed to load model.");
    }

					
					
	//g_model.normalize();





}



void Log(const char *pszMessage)
{
    MessageBox(0, pszMessage, "Error", MB_ICONSTOP);
}

void ProcessMenu(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    static char szFilename[MAX_PATH] = {'\0'};
    static OPENFILENAME ofn;

    switch (LOWORD(wParam))
    {
    case MENU_FILE_OPEN:
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hWnd;
        ofn.lpstrFilter = "Alias|Wavefront (*.OBJ)\0*.obj\0";
        ofn.lpstrCustomFilter = 0;
        ofn.nFilterIndex = 1;
        ofn.lpstrFile = szFilename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Open File";
        ofn.lpstrFileTitle = 0;
        ofn.lpstrDefExt = 0;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST;

        if (GetOpenFileName(reinterpret_cast<LPOPENFILENAME>(&ofn)))
        {
            UnloadModel();
            LoadModel(szFilename);
            ResetCamera();
        }

        break;

    case MENU_FILE_CLOSE:
        UnloadModel();
        break;

    case MENU_FILE_EXIT:
        SendMessage(hWnd, WM_CLOSE, 0, 0);
        break;

    case MENU_VIEW_FULLSCREEN:
        ToggleFullScreen();

        if (g_isFullScreen)
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_FULLSCREEN, MF_CHECKED);
        else
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_FULLSCREEN, MF_UNCHECKED);
        break;

    case MENU_VIEW_RESET:
        ResetCamera();
        break;

    case MENU_VIEW_CULLBACKFACES:
        if (g_cullBackFaces = !g_cullBackFaces)
        {
            glEnable(GL_CULL_FACE);
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_CULLBACKFACES, MF_CHECKED);
        }
        else
        {
            glDisable(GL_CULL_FACE);
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_CULLBACKFACES, MF_UNCHECKED);
        }
        break;

    case MENU_VIEW_TEXTURED:
        if (g_enableTextures = !g_enableTextures)
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_TEXTURED, MF_CHECKED);
        else
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_TEXTURED, MF_UNCHECKED);
        break;

    case MENU_VIEW_WIREFRAME:
        if (g_enableWireframe = !g_enableWireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_WIREFRAME, MF_CHECKED);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            CheckMenuItem(GetMenu(hWnd), MENU_VIEW_WIREFRAME, MF_UNCHECKED);
        }
        break;

    default:
        break;
    }
}

void ProcessMouseInput(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Use the left mouse button to track the camera.
    // Use the middle mouse button to dolly the camera.
    // Use the right mouse button to orbit the camera.

    enum CameraMode {CAMERA_NONE, CAMERA_TRACK, CAMERA_DOLLY, CAMERA_ORBIT};

    static CameraMode cameraMode = CAMERA_NONE;
    static POINT ptMousePrev = {0};
    static POINT ptMouseCurrent = {0};
    static int mouseButtonsDown = 0;
    static float dx = 0.0f;
    static float dy = 0.0f;

    switch (msg)
    {
    case WM_LBUTTONDOWN:
        cameraMode = CAMERA_TRACK;
        ++mouseButtonsDown;
        SetCapture(hWnd);
        ptMousePrev.x = static_cast<int>(static_cast<short>(LOWORD(lParam)));
        ptMousePrev.y = static_cast<int>(static_cast<short>(HIWORD(lParam)));
        ClientToScreen(hWnd, &ptMousePrev);
        break;

    case WM_RBUTTONDOWN:
        cameraMode = CAMERA_ORBIT;
        ++mouseButtonsDown;
        SetCapture(hWnd);
        ptMousePrev.x = static_cast<int>(static_cast<short>(LOWORD(lParam)));
        ptMousePrev.y = static_cast<int>(static_cast<short>(HIWORD(lParam)));
        ClientToScreen(hWnd, &ptMousePrev);
        break;

    case WM_MBUTTONDOWN:
        cameraMode = CAMERA_DOLLY;
        ++mouseButtonsDown;
        SetCapture(hWnd);
        ptMousePrev.x = static_cast<int>(static_cast<short>(LOWORD(lParam)));
        ptMousePrev.y = static_cast<int>(static_cast<short>(HIWORD(lParam)));
        ClientToScreen(hWnd, &ptMousePrev);
        break;

    case WM_MOUSEMOVE:
        ptMouseCurrent.x = static_cast<int>(static_cast<short>(LOWORD(lParam)));
        ptMouseCurrent.y = static_cast<int>(static_cast<short>(HIWORD(lParam)));
        ClientToScreen(hWnd, &ptMouseCurrent);

        switch (cameraMode)
        {
        case CAMERA_TRACK:
            dx = static_cast<float>(ptMouseCurrent.x - ptMousePrev.x);
            dx *= MOUSE_TRACK_SPEED;

            dy = static_cast<float>(ptMouseCurrent.y - ptMousePrev.y);
            dy *= MOUSE_TRACK_SPEED;

            g_cameraPos[0] -= dx;
            g_cameraPos[1] += dy;

            g_targetPos[0] -= dx;
            g_targetPos[1] += dy;

            break;

        case CAMERA_DOLLY:
            dy = static_cast<float>(ptMouseCurrent.y - ptMousePrev.y);
            dy *= MOUSE_DOLLY_SPEED;

            g_cameraPos[2] -= dy;

            if (g_cameraPos[2] < g_model.getRadius() + CAMERA_ZNEAR)
                g_cameraPos[2] = g_model.getRadius() + CAMERA_ZNEAR;

            if (g_cameraPos[2] > CAMERA_ZFAR - g_model.getRadius())
                g_cameraPos[2] = CAMERA_ZFAR - g_model.getRadius();

            break;

        case CAMERA_ORBIT:
            dx = static_cast<float>(ptMouseCurrent.x - ptMousePrev.x);
            dx *= MOUSE_ORBIT_SPEED;

            dy = static_cast<float>(ptMouseCurrent.y - ptMousePrev.y);
            dy *= MOUSE_ORBIT_SPEED;

            g_heading += dx;
            g_pitch += dy;

            if (g_pitch > 90.0f)
                g_pitch = 90.0f;

            if (g_pitch < -90.0f)
                g_pitch = -90.0f;

            break;
        }

        ptMousePrev.x = ptMouseCurrent.x;
        ptMousePrev.y = ptMouseCurrent.y;
        break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
        if (--mouseButtonsDown <= 0)
        {
            mouseButtonsDown = 0;
            cameraMode = CAMERA_NONE;
            ReleaseCapture();
        }
        else
        {
            if (wParam & MK_LBUTTON)
                cameraMode = CAMERA_TRACK;
            else if (wParam & MK_RBUTTON)
                cameraMode = CAMERA_ORBIT;
            else if (wParam & MK_MBUTTON)
                cameraMode = CAMERA_DOLLY;
        }
        break;

    default:
        break;
    }
}

void ReadTextFileFromResource(const char *pResouceId, std::string &buffer)
{
    HMODULE hModule = GetModuleHandle(0);
    HRSRC hResource = FindResource(hModule, pResouceId, RT_RCDATA);

    if (hResource)
    {
        DWORD dwSize = SizeofResource(hModule, hResource);
        HGLOBAL hGlobal = LoadResource(hModule, hResource);

        if (hGlobal)
        {
            if (LPVOID pData = LockResource(hGlobal))
            {
                buffer.assign(reinterpret_cast<const char *>(pData), dwSize);
                UnlockResource(hGlobal);
            }
        }
    }
}

void ResetCamera()
{
    g_model.getCenter(g_targetPos[0], g_targetPos[1], g_targetPos[2]);

    g_cameraPos[0] = g_targetPos[0];
    g_cameraPos[1] = g_targetPos[1];
    g_cameraPos[2] = g_targetPos[2] + g_model.getRadius() + CAMERA_ZNEAR + 0.4f;

    g_pitch = 0.0f;
    g_heading = 0.0f;
}

void SetProcessorAffinity()
{
    // Assign the current thread to one processor. This ensures that timing
    // code runs on only one processor, and will not suffer any ill effects
    // from power management.
    //
    // Based on DXUTSetProcessorAffinity() function from the DXUT framework.

    DWORD_PTR dwProcessAffinityMask = 0;
    DWORD_PTR dwSystemAffinityMask = 0;
    HANDLE hCurrentProcess = GetCurrentProcess();

    if (!GetProcessAffinityMask(hCurrentProcess, &dwProcessAffinityMask, &dwSystemAffinityMask))
        return;

    if (dwProcessAffinityMask)
    {
        // Find the lowest processor that our process is allowed to run against.

        DWORD_PTR dwAffinityMask = (dwProcessAffinityMask & ((~dwProcessAffinityMask) + 1));

        // Set this as the processor that our thread must always run against.
        // This must be a subset of the process affinity mask.

        HANDLE hCurrentThread = GetCurrentThread();

        if (hCurrentThread != INVALID_HANDLE_VALUE)
        {
            SetThreadAffinityMask(hCurrentThread, dwAffinityMask);
            CloseHandle(hCurrentThread);
        }
    }

    CloseHandle(hCurrentProcess);
}

void ToggleFullScreen()
{
    static DWORD savedExStyle;
    static DWORD savedStyle;
    static RECT rcSaved;

    g_isFullScreen = !g_isFullScreen;

    if (g_isFullScreen)
    {
        // Moving to full screen mode.

        savedExStyle = GetWindowLong(g_hWnd, GWL_EXSTYLE);
        savedStyle = GetWindowLong(g_hWnd, GWL_STYLE);
        GetWindowRect(g_hWnd, &rcSaved);

        SetWindowLong(g_hWnd, GWL_EXSTYLE, 0);
        SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
        SetWindowPos(g_hWnd, HWND_TOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        g_windowWidth = GetSystemMetrics(SM_CXSCREEN);
        g_windowHeight = GetSystemMetrics(SM_CYSCREEN);

        SetWindowPos(g_hWnd, HWND_TOPMOST, 0, 0,
            g_windowWidth, g_windowHeight, SWP_SHOWWINDOW);
    }
    else
    {
        // Moving back to windowed mode.

        SetWindowLong(g_hWnd, GWL_EXSTYLE, savedExStyle);
        SetWindowLong(g_hWnd, GWL_STYLE, savedStyle);
        SetWindowPos(g_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        g_windowWidth = rcSaved.right - rcSaved.left;
        g_windowHeight = rcSaved.bottom - rcSaved.top;

        SetWindowPos(g_hWnd, HWND_NOTOPMOST, rcSaved.left, rcSaved.top,
            g_windowWidth, g_windowHeight, SWP_SHOWWINDOW);
    }
}

void UnloadModel()
{
    SetCursor(LoadCursor(0, IDC_WAIT));

    ModelTextures::iterator i = g_modelTextures.begin();

    while (i != g_modelTextures.end())
    {
        glDeleteTextures(1, &i->second);
        ++i;
    }

    g_modelTextures.clear();
    g_model.destroy();

    SetCursor(LoadCursor(0, IDC_ARROW));
    SetWindowText(g_hWnd, APP_TITLE);
}

void UpdateFrame(float elapsedTimeSec)
{
    UpdateFrameRate(elapsedTimeSec);
}

void UpdateFrameRate(float elapsedTimeSec)
{
    static float accumTimeSec = 0.0f;
    static int frames = 0;

    accumTimeSec += elapsedTimeSec;

    if (accumTimeSec > 1.0f)
    {
        g_framesPerSecond = frames;

        frames = 0;
        accumTimeSec = 0.0f;
    }
    else
    {
        ++frames;
    }
}
