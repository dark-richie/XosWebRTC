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
///   File: XosWebRtcClientOpenGLVideoRenderer.hpp
///
/// Author: $author$
///   Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP
#define _XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP
/*
#include <map>
#include <string>

#include "talk/session/phone/mediachannel.h"
#include "talk/session/phone/videocommon.h"
#include "talk/session/phone/videoframe.h"
#include "talk/session/phone/videorenderer.h"
*/
#include "XosPlatform_opengl.hpp"
#include "XosInterfaceBase.hpp"
#include "XosExportBase.hpp"

#define XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_MINIMUM 128
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_OFFSET 10
#define XOS_WEBRTC_PEERCONNECTION_CLIENT_REMOTE_WINDOW_RATIO 4

#if defined(_XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP) 
#else // defined(_XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP) 
#endif // defined(_XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP) 

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

typedef XosInterfaceBase XosWebRtcClientOpenGLVideoRendererImplement;
typedef XosExportBase XosWebRtcClientOpenGLVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientOpenGLVideoRenderer
///
/// Author: $author$
///   Date: 7/7/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientOpenGLVideoRenderer
: virtual public XosWebRtcClientOpenGLVideoRendererImplement,
  public XosWebRtcClientOpenGLVideoRendererExtend
{
public:
    typedef XosWebRtcClientOpenGLVideoRendererImplement Implements;
    typedef XosWebRtcClientOpenGLVideoRendererExtend Extends;

    enum
    {
        REMOTE_TEXTURE,
        LOCAL_TEXTURE,
        TEXTURES
    };
    struct GLPoint
    {
        float x, y;
        GLPoint(float nx, float ny) : x(nx), y(ny) { }
        GLPoint(int nx, int ny) : x((float)nx), y((float)ny) { }
        GLPoint() : x(0), y(0) { }
    };
    struct GLSize
    {
        float width, height;
        GLSize(float nw, float nh) : width(nw), height(nh) { }
        GLSize(int nw, int nh) : width((float)nw), height((float)nh) { }
        GLSize() : width(0), height(0) { }
    };
    struct GLRect
    {
        GLPoint origin;
        GLSize    size;
        GLRect(float nx, float ny, float nw, float nh) : origin(nx, ny), size(nw, nh) { }
        GLRect(int nx, int ny, int nw, int nh) : origin(nx, ny), size(nw, nh) { }
        GLRect() : origin(), size() { }
    };
    struct ColorIndex {
        uint8_t Red, Green, Blue, Alpha;
    };

    bool    _dontUse;
    bool    _hasFailed;
    int     _width, _height;
    int     _remoteWindowMinimum;
    int     _remoteWindowOffet;
    int     _remoteWindowRatio;
    GLint   _textureMagFilter;
    GLint   _textureMinFilter;
    GLuint texture[TEXTURES];

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientOpenGLVideoRenderer
    ///
    ///       Author: $author$
    ///         Date: 7/7/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientOpenGLVideoRenderer();
    virtual ~XosWebRtcClientOpenGLVideoRenderer();

    virtual bool init()
    { return true; }
    virtual bool finish()
    { return true; }

    virtual bool swapBuffers()
    { return true; }

    virtual void prepareOpenGL();
    virtual void reshape(int width, int height);
    virtual void render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight,
     const void* localImage, int localImageWidth, int localImageHeight);
    virtual void render
    (const void* remoteImage, int remoteImageWidth, int remoteImageHeight);
    virtual void loadTexture(int textureID, const void* image, int w, int h);
    virtual void drawTexture(int textureID, GLPoint p, GLSize s);
    virtual void ResizeRect
    (GLRect& rect, const GLSize& fromSize, const GLSize& toSize);

    virtual GLenum textureImageFormat() const 
    { return GL_BGRA; }

    virtual ColorIndex textureImageColorIndex() const {
        static ColorIndex index = {2, 1, 0, 3};
        return index;
    }

    virtual bool setHasFailed(bool isTrue=true)
    { if ((isTrue)) hasFailed(); return _hasFailed; }
    virtual bool getHasFailed() const 
    { return _hasFailed; }

    virtual void hasFailed()
    { _hasFailed = true; dontUse();}

    virtual void dontUse()
    { setDontUse(); }
    virtual void use()
    { setDontUse(false); }

    virtual bool setDontUse(bool isTrue=true)
    { if (!(_hasFailed)) _dontUse = isTrue; return _dontUse; }
    virtual bool getDontUse() const
    { return _dontUse; }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTOPENGLVIDEORENDERER_HPP 
