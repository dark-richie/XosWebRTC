///////////////////////////////////////////////////////////////////////
/// Copyright 2013, Google Inc.
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
///   File: XosWebRtcClientPlatformSocketServer.hpp
///
/// Author: $author$
///   Date: 1/26/2013
///////////////////////////////////////////////////////////////////////
#ifndef _XOSWEBRTCCLIENTPLATFORMSOCKETSERVER_HPP
#define _XOSWEBRTCCLIENTPLATFORMSOCKETSERVER_HPP

#include "XosPlatform_build.hpp"
#include "talk/base/physicalsocketserver.h"

#if defined(MACOSX)
#if !defined(MACOSX_SOCKETSERVER)
#if defined(WEBRTC_FBPLUGIN)
#define MACOSX_SOCKETSERVER
#endif // defined(WEBRTC_FBPLUGIN)
#endif // !defined(MACOSX_SOCKETSERVER)
#endif // defined(MACOSX)

#if defined(WINDOWS) 
// Windows 
#include "talk/base/win32socketserver.h"
#else // defined(WINDOWS) 
// Unix 
#if defined(MACOSX) 
// Mac SocketServer 
#include "talk/base/macsocketserver.h"
#else // defined(MACOSX) 
// Otherwise
#endif // defined(MACOSX) 
#endif // defined(WINDOWS) 

namespace talk_base {
#if defined(WINDOWS) 
// Windows 
typedef PhysicalSocketServer PlatformSocketServer;
#else // defined(WINDOWS) 
// Unix 
#if defined(MACOSX_SOCKETSERVER) 
// Mac SocketServer 
typedef MacCarbonSocketServer PlatformSocketServer;
#else // defined(MACOSX_SOCKETSERVER) 
// Otherwise
typedef PhysicalSocketServer PlatformSocketServer;
#endif // defined(MACOSX_SOCKETSERVER) 
#endif // defined(WINDOWS) 
}

#if defined(_NAMESPACE)
namespace _NAMESPACE {
#endif // defined(_NAMESPACE) 

#if defined(_NAMESPACE)
}
#endif // defined(_NAMESPACE) 

#endif // _XOSWEBRTCCLIENTPLATFORMSOCKETSERVER_HPP 
