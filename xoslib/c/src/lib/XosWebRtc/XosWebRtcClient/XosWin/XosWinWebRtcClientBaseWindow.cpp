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
///   File: XosWinWebRtcClientBaseWindow.cpp
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
#include "XosWinWebRtcClientBaseWindow.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientBaseWindow
///
/// Author: $author$
///   Date: 4/3/2012
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientBaseWindow::OnPaintBlank
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientBaseWindow::OnPaintBlank()
{
    bool isSuccess = true;
    RECT rc;
    PAINTSTRUCT ps;

    GetClientRect(Attached(), &rc);
    BeginPaint(Attached(), &ps);

    if (!(m_showConnectionState) || (ui_ == STREAMING))
    {
        //
        // Show blank background before connected to peer.
        //
        HBRUSH brush = CreateSolidBrush(RGB
        (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_RED, 
         XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_GREEN, 
         XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_BACKGROUND_BLUE));
        FillRect(ps.hdc, &rc, brush);
        DeleteObject(brush);
    }
    else
    if ((ui_ == LIST_PEERS))
    {
        HBRUSH brush = CreateSolidBrush(RGB
        (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_RED, 
         XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_GREEN, 
         XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_PEER_BLUE));
        FillRect(ps.hdc, &rc, brush);
        DeleteObject(brush);

        std::string text(m_ConnectToPeerBefore.c_str());
        text += m_connectToPeerName;
        text += m_ConnectToPeerAfter.c_str();

        DrawWhiteText
        (ps.hdc, rc, text.c_str(),
         DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        text = m_PeerBefore.c_str();
        text += GetThisPeerName().c_str();
        text += m_PeerAfter.c_str();

        DrawWhiteText
        (ps.hdc, rc, text.c_str(),
         DT_CENTER | DT_BOTTOM);
    }
    else 
    if ((ui_ == CONNECT_TO_SERVER))
    {
      HBRUSH brush = CreateSolidBrush(RGB
      (XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_RED, 
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_GREEN, 
       XOSWEBRTCCLIENTBASEWINDOW_DEFAULT_CONNECT_TO_SERVER_BLUE));
      FillRect(ps.hdc, &rc, brush);
      DeleteObject(brush);

      std::string text(m_ConnectToServerBefore.c_str());
      text += m_serverName;
      text += m_ConnectToServerAfter.c_str();

      DrawWhiteText
      (ps.hdc, rc, text.c_str(),
       DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    }
    EndPaint(Attached(), &ps);

    return isSuccess;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientBaseWindow::OnRenderImage
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientBaseWindow::OnRenderImage
(const uint8* remote_image, int remote_width, int remote_height,
 const uint8* local_image, int local_width, int local_height,
 bool is_local) 
{
    XosWebRtcClientVideoRendererImplemented* local_video = local_video_->RendererImplemented();
    XosWebRtcClientVideoRendererImplemented* remote_video = remote_video_->RendererImplemented();
    PAINTSTRUCT ps;
    RECT rc;

    BeginPaint(Attached(), &ps);
    GetClientRect(Attached(), &rc);

    const BITMAPINFO& bmi = (is_local)?(local_video->bmi()):(remote_video->bmi());
    remote_height = abs(bmi.bmiHeader.biHeight);
    remote_width = bmi.bmiHeader.biWidth;

    HDC dc_mem = CreateCompatibleDC(ps.hdc);
    SetStretchBltMode(dc_mem, HALFTONE);

    // Set the map mode so that the ratio will be maintained.
    //
    HDC all_dc[] = { ps.hdc, dc_mem };
    for (int i = 0; i < ARRAY_SIZE(all_dc); ++i) 
    {
        SetMapMode(all_dc[i], MM_ISOTROPIC);
        SetWindowExtEx(all_dc[i], remote_width, remote_height, NULL);
        SetViewportExtEx(all_dc[i], rc.right, rc.bottom, NULL);
    }

    HBITMAP bmp_mem = CreateCompatibleBitmap(ps.hdc, rc.right, rc.bottom);
    HGDIOBJ bmp_old = SelectObject(dc_mem, bmp_mem);

    POINT logical_area = { rc.right, rc.bottom };
    DPtoLP(ps.hdc, &logical_area, 1);

    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    RECT logical_rect = {0, 0, logical_area.x, logical_area.y };
    FillRect(dc_mem, &logical_rect, brush);
    DeleteObject(brush);

    int max_unit = max(remote_width, remote_height);
    int x = (logical_area.x / 2) - (remote_width / 2);
    int y = (logical_area.y / 2) - (remote_height / 2);

    StretchDIBits
    (dc_mem, x, y, remote_width, remote_height,
     0, 0, remote_width, remote_height, 
     remote_image, &bmi, DIB_RGB_COLORS, SRCCOPY);

    bool isALocalImage = ((local_image) && ((rc.right - rc.left) > 200) && ((rc.bottom - rc.top) > 200));
    if ((isALocalImage))
    {
        const BITMAPINFO& bmi = local_video->bmi();
        int thumb_width = (bmi.bmiHeader.biWidth / 4);
        int thumb_height = (abs(bmi.bmiHeader.biHeight) / 4);
        int thumb_x = (logical_area.x - (thumb_width + 10));
        int thumb_y = (logical_area.y - (thumb_height + 10));
        local_width = (bmi.bmiHeader.biWidth);
        local_height = (abs(bmi.bmiHeader.biHeight));

        StretchDIBits
        (dc_mem, thumb_x, thumb_y, thumb_width, thumb_height,
         0, 0, local_width, local_height,
         local_image, &bmi, DIB_RGB_COLORS, SRCCOPY);
    }

    BitBlt
    (ps.hdc, 0, 0, logical_area.x, logical_area.y,
     dc_mem, 0, 0, SRCCOPY);

    const char* kRemote = "Remote: ";
    const char* kLocal = "Local: ";
    XosString text((isALocalImage)?(kRemote):((is_local)?(kLocal):(kRemote)));
    text << remote_width;
    text << "x";
    text << remote_height;
    if ((isALocalImage))
    {
        text << " ";
        text << kLocal;
        text << local_width;
        text << "x";
        text << local_height;
    }
    SetMapMode(ps.hdc, MM_TEXT);
    DrawWhiteText(ps.hdc, rc, text.c_str(), DT_SINGLELINE);

    // Cleanup
    SelectObject(dc_mem, bmp_old);
    DeleteObject(bmp_mem);
    DeleteDC(dc_mem);

    EndPaint(Attached(), &ps);
    return true;
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientBaseWindow::DrawWhiteText
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
void XosWinWebRtcClientBaseWindow::DrawWhiteText
(HDC dc, RECT& rect, const char* text, int flags)
{
    HGDIOBJ old_font = SelectObject(dc, GetDefaultFont());
    SetTextColor(dc, RGB(0xff, 0xff, 0xff));
    SetBkMode(dc, TRANSPARENT);
    DrawTextA(dc, text, -1, &rect, flags);
    SelectObject(dc, old_font);
}

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientBaseWindow::GetDefaultFont
///
///    Author: $author$
///      Date: 4/3/2012
///////////////////////////////////////////////////////////////////////
HFONT XosWinWebRtcClientBaseWindow::GetDefaultFont()
{
    HFONT font = (HFONT)(GetStockObject(DEFAULT_GUI_FONT));
    return font;
}
#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 
