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
///   File: XosWinWebRtcClientVideoRenderer.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWINWEBRTCCLIENTVIDEORENDERER_HPP
#define _XOSWINWEBRTCCLIENTVIDEORENDERER_HPP

#include "XosWebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWinWebRtcClientVideoRendererExtend
///
///  Author: $author$
///    Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
typedef XosWebRtcClientVideoRenderer 
XosWinWebRtcClientVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientVideoRenderer
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWinWebRtcClientVideoRenderer
: public XosWinWebRtcClientVideoRendererExtend
{
public:
    typedef XosWinWebRtcClientVideoRendererExtend Extends;

protected:
    HWND wnd_;
    BITMAPINFO bmi_;
    CRITICAL_SECTION buffer_lock_;

public:
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWinWebRtcClientVideoRenderer
    ///
    ///       Author: $author$
    ///         Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    XosWinWebRtcClientVideoRenderer
    (HWND wnd, size_t width, size_t height, bool isRemote=false)
    : Extends(width, height, isRemote),
      wnd_(wnd)
    {
        InitializeCriticalSection(&buffer_lock_);
        ZeroMemory(&bmi_, sizeof(bmi_));
        bmi_.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi_.bmiHeader.biPlanes = 1;
        bmi_.bmiHeader.biBitCount = 32;
        bmi_.bmiHeader.biCompression = BI_RGB;
        bmi_.bmiHeader.biWidth = width;
        bmi_.bmiHeader.biHeight = -height;
        bmi_.bmiHeader.biSizeImage = width * height * 4;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWinWebRtcClientVideoRenderer
    ///
    ///      Author: $author$
    ///        Date: 4/3/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWinWebRtcClientVideoRenderer()
    {
        DeleteCriticalSection(&buffer_lock_);
    }

    virtual void UpdateImageSize(int width, int height)
    {
        Extends::UpdateImageSize(width, height);
        bmi_.bmiHeader.biWidth = image_width_;
        bmi_.bmiHeader.biHeight = -image_height_;
        bmi_.bmiHeader.biSizeImage = image_size_;
    }
    virtual void UpdateVisibleFrame() 
    { 
        if ((wnd_)) 
            InvalidateRect(wnd_, NULL, TRUE); 
    }

    virtual void Lock() { ::EnterCriticalSection(&buffer_lock_); }
    virtual void Unlock() { ::LeaveCriticalSection(&buffer_lock_); }

    const BITMAPINFO& bmi() const { return bmi_; }
};

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientVideoRendererImplemented
///
/// Author: $author$
///   Date: 5/15/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientVideoRendererImplemented
: public XosWinWebRtcClientVideoRenderer
{
public:
    typedef XosWinWebRtcClientVideoRenderer Extends;
    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientVideoRendererImplemented
    ///
    ///       Author: $author$
    ///         Date: 5/15/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientVideoRendererImplemented
    (HWND wnd, size_t width, size_t height, bool isRemote=false)
    : Extends(wnd, width, height, isRemote)
    {
    }
    virtual XosWebRtcClientVideoRendererImplemented* RendererImplemented() const
    { return (XosWebRtcClientVideoRendererImplemented*)(this); }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWINWEBRTCCLIENTVIDEORENDERER_HPP 
        

