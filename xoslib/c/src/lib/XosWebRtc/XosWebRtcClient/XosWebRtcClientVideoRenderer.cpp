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
///   File: XosWebRtcClientVideoRenderer.cpp
///
/// Author: $author$
///   Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientVideoRenderer.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientVideoRenderer
///
/// Author: $author$
///   Date: 6/24/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoRenderer::SetSize
///
///    Author: $author$
///      Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientVideoRenderer::SetSize
(int width, int height, int reserved)
{
    bool handled = true;
    AutoLock<XosWebRtcClientVideoRenderer> lock(this);
    if ((m_isRemote))
        handled = handled;
    UpdateImageSize(width, height);
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoRenderer::RenderFrame
///
///    Author: $author$
///      Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
bool XosWebRtcClientVideoRenderer::
RenderFrame(const cricket::VideoFrame* frame) 
{
    bool handled = false;
    if ((m_isRemote))
        handled = handled;
    if ((frame))
    {
        AutoLock<XosWebRtcClientVideoRenderer> lock(this);

        frame_height_ = frame->GetHeight();
        frame_width_ = frame->GetWidth();

        ASSERT(image_.get() != NULL);

        frame->ConvertToRgbBuffer
        (RenderImageFormat(), image_.get(),
         image_size_, image_width_ * 4);

        UpdateVisibleFrame();
        handled = true;
    }
    return handled;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoRenderer::ConvertARGBToABGR
///
///    Author: $author$
///      Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientVideoRenderer::ConvertARGBToABGR()
{
    enum { ARGB_B, ARGB_G, ARGB_R, ARGB_A };
    enum { ABGR_R, ABGR_G, ABGR_B, ABGR_A };
    uint8 argbImageT;
    uint8* argbImage;
    uint8* argbImageEnd;

    //
    // Convert from ARGB to ABGR
    //
    if ((argbImage = image_.get()))
    for (argbImageEnd = argbImage+image_size_; 
         argbImage < argbImageEnd; argbImage += 4)
    {
        argbImageT = argbImage[ARGB_B];
        argbImage[ABGR_R] = argbImage[ARGB_R];
        argbImage[ABGR_B] = argbImageT;
    }
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoRenderer::UpdateImageSize
///
///    Author: $author$
///      Date: 6/24/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientVideoRenderer::UpdateImageSize(int width, int height)
{
    if ((image_size_ = (image_width_ = width) * (image_height_ = height) * 4))
        image_.reset(new uint8[image_size_]);
    uint8* image = d_image();
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

        

