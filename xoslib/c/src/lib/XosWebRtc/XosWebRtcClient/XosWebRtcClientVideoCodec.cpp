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
///   File: XosWebRtcClientVideoCodec.cpp
///
/// Author: $author$
///   Date: 12/8/2012
///////////////////////////////////////////////////////////////////////
#include "XosWebRtcClientVideoCodec.hpp"

namespace webrtc
{
extern int vcm_default_codec_width;
extern int vcm_default_codec_height;
extern int vcm_default_frame_rate;
extern int vcm_default_min_bitrate;
extern int vcm_default_flush_inicator;
}

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWebRtcClientVideoCodec
///
/// Author: $author$
///   Date: 4/1/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoCodec::SetDefaultMode
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientVideoCodecMode XosWebRtcClientVideoCodec::SetDefaultMode
(XosWebRtcClientVideoCodecMode toMode)
{
    XosWebRtcClientVideoCodecMode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;
    int video_codec_cols;
    int video_codec_rows;

    if (0 < (video_codec_cols = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_COLS(toMode)))
    if (0 < (video_codec_rows = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_ROWS(toMode)))
    {
        webrtc::vcm_default_codec_width = video_codec_cols;
        webrtc::vcm_default_codec_height = video_codec_rows;
        mode = toMode;
    }
    return mode;
}
XosWebRtcClientVideoCodecMode
MatchMode(XosWebRtcClientVideoCodecMode toMode, int width, int height)
{
    XosWebRtcClientVideoCodecMode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;
    int video_codec_cols;
    int video_codec_rows;

    if (0 < (video_codec_cols = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_COLS(toMode)))
    if (0 < (video_codec_rows = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_ROWS(toMode)))
    if ((video_codec_cols == width) && (video_codec_rows == height))
        return toMode;
    return mode;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoCodec::GetDefaultMode
///
///    Author: $author$
///      Date: 4/1/2012
///////////////////////////////////////////////////////////////////////
XosWebRtcClientVideoCodecMode XosWebRtcClientVideoCodec::GetDefaultMode() const
{
    XosWebRtcClientVideoCodecMode mode = XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_UNKNOWN;
    int width = webrtc::vcm_default_codec_width;
    int height = webrtc::vcm_default_codec_height;

    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_CIF, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_4CIF, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QQVGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_QVGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_VGA, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_HD, width, height)))
    if (0 >= (mode = MatchMode(XOS_WEBRTC_CLIENT_VIDEO_CODEC_MODE_FHD, width, height)))
        return mode;
    return mode;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoCodec::SetDefaultOptions
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientVideoCodec::SetDefaultOptions
(int codecWidth, int codecHeight,
 int frameRate, int minBitrate)
{
    webrtc::vcm_default_codec_width = codecWidth;
    webrtc::vcm_default_codec_height = codecHeight;
    webrtc::vcm_default_frame_rate = frameRate;
    webrtc::vcm_default_min_bitrate =  minBitrate;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWebRtcClientVideoCodec::GetDefaultOptions
///
///    Author: $author$
///      Date: 4/12/2012
///////////////////////////////////////////////////////////////////////
void XosWebRtcClientVideoCodec::GetDefaultOptions
(int& codecWidth, int& codecHeight,
 int& frameRate, int& minBitrate) const
{
    codecWidth = webrtc::vcm_default_codec_width;
    codecHeight = webrtc::vcm_default_codec_height;
    frameRate = webrtc::vcm_default_frame_rate;
    minBitrate = webrtc::vcm_default_min_bitrate;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
