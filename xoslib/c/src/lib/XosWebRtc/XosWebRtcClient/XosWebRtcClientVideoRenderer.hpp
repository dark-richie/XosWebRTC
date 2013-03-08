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
///   File: XosWebRtcClientVideoRenderer.hpp
///
/// Author: $author$
///   Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTVIDEORENDERER_HPP
#define _XOSWEBRTCCLIENTVIDEORENDERER_HPP

#include <map>
#include <string>

#include "talk/session/phone/mediachannel.h"
#include "talk/session/phone/videocommon.h"
#include "talk/session/phone/videoframe.h"
#include "talk/session/phone/videorenderer.h"

#include "XosExportBase.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

class _EXPORT_CLASS XosWebRtcClientVideoRendererImplemented;
///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientVideoRendererExtend
///
///  Author: $author$
///    Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
typedef cricket::VideoRenderer
XosWebRtcClientVideoRendererExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientVideoRenderer
///
/// Author: $author$
///   Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
class _EXPORT_CLASS XosWebRtcClientVideoRenderer
: public XosWebRtcClientVideoRendererExtend
{
public:
    typedef XosWebRtcClientVideoRendererExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    /// A little helper class to make sure we always to proper locking and
    /// unlocking when working with VideoRenderer buffers.
    ///////////////////////////////////////////////////////////////////////
    template <typename T>
    class AutoLock
    {
    public:
        explicit AutoLock(T* obj) : obj_(obj) { obj_->Lock(); }
        ~AutoLock() { obj_->Unlock(); }
    protected:
        T* obj_;
    };

    bool m_isRemote;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientVideoRenderer
    ///
    ///       Author: $author$
    ///         Date: 6/24/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientVideoRenderer
    (size_t width=0, size_t height=0, bool isRemote=false)
    : frame_width_(0), frame_height_(0),
      image_width_(width), image_height_(height),
      image_size_(width * height * 4),
      m_isRemote(isRemote)
    {
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientVideoRenderer
    ///
    ///      Author: $author$
    ///        Date: 6/24/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientVideoRenderer()
    {
    }

    virtual bool SetSize(int width, int height, int reserved = 0);

    virtual bool RenderFrame(const cricket::VideoFrame* frame);

    virtual void ConvertARGBToABGR();

    virtual cricket::FourCC RenderImageFormat() const 
    { return cricket::FOURCC_ARGB; }

    virtual XosWebRtcClientVideoRendererImplemented* RendererImplemented() const
    { return 0; }

    virtual void UpdateImageSize(int width, int height);
    virtual void UpdateVisibleFrame() {}

    virtual void Lock() {}
    virtual void Unlock() {}

    size_t frame_width() const { return frame_width_; }
    size_t frame_height() const { return frame_height_; }

    size_t image_width() const { return image_width_; }
    size_t image_height() const { return image_height_; }

    const uint8* image() const { return image_.get(); }
    uint8* d_image() const { return image_.get(); }

    size_t frame_width_;
    size_t frame_height_;
    size_t image_width_;
    size_t image_height_;
    size_t image_size_;
    talk_base::scoped_array<uint8> image_;
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTVIDEORENDERER_HPP 
