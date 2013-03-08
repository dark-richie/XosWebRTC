///////////////////////////////////////////////////////////////////////
/// Copyright 2012, Google Inc.
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
/// 
///  1. Redistributions of source code must retain the above copyright notice,
///     this list of conditions and the following disclaimer.
///  2. Redistributions in binary form must reproduce the above copyright notice,
///     this list of conditions and the following disclaimer in the documentation
///     and/or other materials provided with the distribution.
///  3. The name of the author may not be used to endorse or promote products
///     derived from this software without specific prior written permission.
/// 
/// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
/// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
/// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
/// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
/// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
/// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
/// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///   File: XosWinWebRtcClientOpenGLVideoRenderer.cpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#include "XosWinWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWinWebRtcClientOpenGLVideoRenderer
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWinWebRtcClientOpenGLVideoRenderer::
XosWinWebRtcClientOpenGLVideoRenderer(HWND hWnd)
: m_hWnd(NULL),
  m_hDC(NULL),
  m_hRC(NULL)
{
    if ((hWnd))
    if (!(init(hWnd)))
        hasFailed();
}
///////////////////////////////////////////////////////////////////////
///   Destructor: ~XosWinWebRtcClientOpenGLVideoRenderer
///
///       Author: $author$
///         Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
XosWinWebRtcClientOpenGLVideoRenderer::
~XosWinWebRtcClientOpenGLVideoRenderer()
{
    finish();
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientOpenGLVideoRenderer::init
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientOpenGLVideoRenderer::init(HWND hWnd)
{
    bool isSuccess = false;

    if ((Extends::init()))
    if ((m_hWnd = hWnd))
    {
        if ((m_hDC = GetDC(m_hWnd)))
        {
            PIXELFORMATDESCRIPTOR pfd, *ppfd;
            int pixelformat;

            ppfd = &pfd;
            ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
            ppfd->nVersion = 1;
            ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            ppfd->dwLayerMask = PFD_MAIN_PLANE;
            ppfd->iPixelType = PFD_TYPE_COLORINDEX;
            ppfd->cColorBits = 16;
            ppfd->cDepthBits = 16;
            ppfd->cAccumBits = 0;
            ppfd->cStencilBits = 0;

            if ((pixelformat = ChoosePixelFormat(m_hDC, ppfd)))
            {
                if ((SetPixelFormat(m_hDC, pixelformat, ppfd)))
                {
                    if ((m_hRC = wglCreateContext(m_hDC)))
                    {
                        if ((wglMakeCurrent(m_hDC, m_hRC)))
                        {
                            prepareOpenGL();
                            return isSuccess = true;
                        }
                        wglDeleteContext(m_hRC);
                        m_hRC = NULL;
                    }
                    else
                    XOS_DBE(("() failed on wglCreateContext()\n"));
                }
                else
                XOS_DBE(("() failed on SetPixelFormat()\n"));
            }
            else
            XOS_DBE(("() failed on ChoosePixelFormat()\n"));

            ReleaseDC(m_hWnd, m_hDC);
            m_hDC = NULL;
        }
        else
        XOS_DBE(("() failed on GetDC()\n"));

        m_hWnd = NULL;
    }
    return isSuccess;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientOpenGLVideoRenderer::finish
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientOpenGLVideoRenderer::finish()
{
    bool isSuccess = true;
    if ((m_hRC))
    {
        if ((m_hDC))
        if (!(wglMakeCurrent(NULL, NULL)))
        {
            XOS_DBE(("() failed on wglMakeCurrent()\n"));
            isSuccess = false;
        }
        wglDeleteContext(m_hRC);
        m_hRC = NULL;
    }
    if ((m_hDC))
    {
        if ((m_hWnd))
        if (!(ReleaseDC(m_hWnd, m_hDC)))
        {
            XOS_DBE(("() failed on ReleaseDC()\n"));
            isSuccess = false;
        }
        m_hDC = NULL;
    }
    if ((m_hWnd))
        m_hWnd = NULL;
    if (!(Extends::finish()))
        isSuccess = false;
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientOpenGLVideoRenderer::swapBuffers
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientOpenGLVideoRenderer::swapBuffers()
{
    bool isSuccess = false;
    if ((m_hDC))
        isSuccess = SwapBuffers(m_hDC);
    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientOpenGLVideoRenderer::reshape
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientOpenGLVideoRenderer::reshape()
{
    bool isSuccess = true;
    if ((m_hWnd))
    {
        RECT rect;
        GetClientRect(m_hWnd, &rect);
        Extends::reshape(rect.right, rect.bottom);
    }
    return isSuccess;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
