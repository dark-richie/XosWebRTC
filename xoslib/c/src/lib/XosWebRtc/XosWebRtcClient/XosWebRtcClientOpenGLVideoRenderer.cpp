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
///   File: XosWebRtcClientOpenGLVideoRenderer.cpp
///
/// Author: $author$
///   Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientOpenGLVideoRenderer.hpp"
#include "XosDebug.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 7/7/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Constructor: XosWebRtcClientOpenGLVideoRenderer::XosWebRtcClientOpenGLVideoRenderer
///
///       Author: $author$
///         Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientOpenGLVideoRenderer::XosWebRtcClientOpenGLVideoRenderer()
: _dontUse(false),
  _hasFailed(false),
  _width(0),
  _height(0),
  _remoteWindowMinimum(XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_MINIMUM),
  _remoteWindowOffet(XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_OFFSET),
  _remoteWindowRatio(XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_RATIO),
  _textureMagFilter(GL_LINEAR),
  _textureMinFilter(GL_LINEAR)
{
}
///////////////////////////////////////////////////////////////////////
///   Destructor: XosWebRtcClientOpenGLVideoRenderer::~XosWebRtcClientOpenGLVideoRenderer
///
///       Author: $author$
///         Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientOpenGLVideoRenderer::~XosWebRtcClientOpenGLVideoRenderer()
{
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::prepareOpenGL
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::prepareOpenGL()
{
    if ((_hasFailed)) return;

    glGenTextures(TEXTURES, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0, 1, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDisable(GL_CULL_FACE);
    setHasFailed (GL_NO_ERROR != glGetError());
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::reshape
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::reshape
(int width, int height)
{
    XOS_DBT(("(int width=%d, int height=%d)...\n", width, height));
    _width = width; _height = height;
    glViewport(0, 0, width, height);
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::render
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::render
(const void* remoteImage, int remoteImageWidth, int remoteImageHeight,
 const void* localImage, int localImageWidth, int localImageHeight)
{
    GLRect rect;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    loadTexture
    (REMOTE_TEXTURE, remoteImage, remoteImageWidth, remoteImageHeight);

    ResizeRect
    (rect, GLSize(remoteImageWidth, remoteImageHeight), GLSize(_width, _height));

    drawTexture(REMOTE_TEXTURE, rect.origin, rect.size);

    if ((_width >= _remoteWindowMinimum) && (_height >= _remoteWindowMinimum))
    {
        float o = (float)(_remoteWindowOffet);
        float r = (float)(_remoteWindowRatio);
        float x = rect.origin.x + rect.size.width - (o / _width);
        float y = rect.origin.y + rect.size.height - (o / _height);

        loadTexture
        (LOCAL_TEXTURE, localImage, localImageWidth, localImageHeight);

        ResizeRect
        (rect, GLSize(localImageWidth, localImageHeight), GLSize(_width, _height));

        drawTexture
        (LOCAL_TEXTURE, 
         GLPoint(x - rect.size.width / r, y - rect.size.height / r),
         GLSize(rect.size.width / r, rect.size.height / r));
    }
    glFlush();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::render
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::render
(const void* remoteImage, int remoteImageWidth, int remoteImageHeight)
{
    GLRect rect;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 1, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    loadTexture
    (REMOTE_TEXTURE, remoteImage, remoteImageWidth, remoteImageHeight);

    ResizeRect
    (rect, GLSize(remoteImageWidth, remoteImageHeight), GLSize(_width, _height));

    drawTexture(REMOTE_TEXTURE, rect.origin, rect.size);

    glFlush();
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::loadTexture
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::loadTexture
(int textureID, const void* image, int w, int h)
{
    glBindTexture(GL_TEXTURE_2D, texture[textureID]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureMinFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, textureImageFormat(), GL_UNSIGNED_BYTE, image);
    setHasFailed(GL_NO_ERROR !=  glGetError());
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::drawTexture
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::drawTexture
(int textureID, GLPoint p, GLSize s)
{
    glBindTexture(GL_TEXTURE_2D, texture[textureID]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(p.x, p.y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(p.x + s.width, p.y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(p.x + s.width, p.y + s.height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(p.x, p.y + s.height);
    glEnd();
    setHasFailed (GL_NO_ERROR !=  glGetError());
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientOpenGLVideoRenderer::ResizeRect
///
///    Author: $author$
///      Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientOpenGLVideoRenderer::ResizeRect
(GLRect& rect, const GLSize& fromSize, const GLSize& toSize)
{
    if (toSize.height < toSize.width) {
        rect.size.width = (toSize.height * fromSize.width) / fromSize.height;
        rect.size.height = toSize.height;
    } else {
        rect.size.height = (toSize.width * fromSize.height) / fromSize.width;
        rect.size.width = toSize.width;
    }
    rect.origin.x = (toSize.width - rect.size.width) / 2;
    rect.origin.y = (toSize.height - rect.size.height) / 2;
    rect.origin.x /= toSize.width; rect.origin.y /= toSize.height;
    rect.size.width /= toSize.width; rect.size.height /= toSize.height;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
