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
///   File: XosWebRtcClientVideoCodec.hpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTVIDEOCODEC_HPP
#define _XOSWEBRTCCLIENTVIDEOCODEC_HPP

#include "XosWebRtcClientVideoCodecMode.hpp"
#include "XosInstanceBase.hpp"
#include "XosString.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
/// Typedef: XosWebRtcClientVideoCodecExtend
///
///  Author: $author$
///    Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
typedef XosInstanceBase
XosWebRtcClientVideoCodecExtend;
///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientVideoCodec
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
class c_INSTANCE_CLASS XosWebRtcClientVideoCodec
: //virtual public XosWebRtcClientVideoCodecImplement,
  public XosWebRtcClientVideoCodecExtend
{
public:
    //typedef XosWebRtcClientVideoCodecImplement Implements;
    typedef XosWebRtcClientVideoCodecExtend Extends;

    ///////////////////////////////////////////////////////////////////////
    ///  Constructor: XosWebRtcClientVideoCodec
    ///
    ///       Author: $author$
    ///         Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    XosWebRtcClientVideoCodec
    (XosWebRtcClientVideoCodecMode videoServiceVideoCodecMode=XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NONE)
    {
        if (0 < (videoServiceVideoCodecMode))
            SetDefaultMode(videoServiceVideoCodecMode);
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Destructor: ~XosWebRtcClientVideoCodec
    ///
    ///      Author: $author$
    ///        Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual ~XosWebRtcClientVideoCodec()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    ///  Function: SetDefaultMode
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientVideoCodecMode SetDefaultMode
    (XosWebRtcClientVideoCodecMode toMode);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetDefaultMode
    ///
    ///    Author: $author$
    ///      Date: 4/1/2012
    ///////////////////////////////////////////////////////////////////////
    virtual XosWebRtcClientVideoCodecMode GetDefaultMode() const;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: SetDefaultOptions
    ///
    ///    Author: $author$
    ///      Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void SetDefaultOptions
    (int codecWidth, int codecHeight,
     int frameRate, int minBitrate);
    ///////////////////////////////////////////////////////////////////////
    ///  Function: GetDefaultOptions
    ///
    ///    Author: $author$
    ///      Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    virtual void GetDefaultOptions
    (int& codecWidth, int& codecHeight,
     int& frameRate, int& minBitrate) const;

    ///////////////////////////////////////////////////////////////////////
    ///  Function: ModeToString
    ///
    ///    Author: $author$
    ///      Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    static std::string ModeToString(XosWebRtcClientVideoCodecMode mode)
    {
        std::string s;
        switch (mode)
        {
        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_CIF;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_VGA;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_HD;
            break;

        case XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD:
            s = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_FHD;
            break;
        }
        return s;
    }
    ///////////////////////////////////////////////////////////////////////
    ///  Function: StringToMode
    ///
    ///    Author: $author$
    ///      Date: 4/12/2012
    ///////////////////////////////////////////////////////////////////////
    static XosWebRtcClientVideoCodecMode StringToMode(const std::string& s)
    {
        XosWebRtcClientVideoCodecMode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;

        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_CIF)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_4CIF)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QQVGA)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_QVGA)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_VGA)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_HD)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD;
        else
        if (!(s.compare(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_NAME_FHD)))
            mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD;

        return mode;
    }
};

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTVIDEOCODEC_HPP 
