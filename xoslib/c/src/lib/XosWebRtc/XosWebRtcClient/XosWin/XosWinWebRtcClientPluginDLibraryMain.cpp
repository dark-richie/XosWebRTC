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
///   File: XosWinWebRtcClientPluginDLibraryMain.cpp
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
#include "talk/base/win32window.h"
#include "XosWinWebRtcClientPluginDLibraryMain.hpp"
#include "XosWinWebRtcClientPluginDLibraryInterface.hpp"

#if defined(c_NAMESPACE)
namespace c_NAMESPACE {
#endif // defined(c_NAMESPACE) 

///////////////////////////////////////////////////////////////////////
///  Function: GetThisModuleHandle
///
///    Author: $author$
///      Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
static HMODULE GetThisModuleHandle()
{
    static const TCHAR VariableInModule = 0; 
    HMODULE hModule = 0;
    GetModuleHandleEx
    (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
     GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
     &VariableInModule, &hModule);
    return hModule;
}

////////////////////////////////////////////////////////////////////////
///
/// Exported functions
///
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
/// Function: XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
PLATFORM_EXPORT XosWinWebRtcClientPluginInterface*
XOSWINWEBRTCCLIENTPLUGIN_ACQUIRE(XosError& error)
{
    XosWinWebRtcClientPluginInterface* plugin = 0;
    XosWinWebRtcClientPluginExporter* exporter = 0;
    error = XOS_ERROR_FAILED;
    if ((exporter = XosWinWebRtcClientPluginExporter::GetExporter()))
        plugin = exporter->AcquirePlugin(error);
    return plugin;
}
///////////////////////////////////////////////////////////////////////
/// Function: XOSWINWEBRTCCLIENTPLUGIN_RELEASE
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
PLATFORM_EXPORT XosError
XOSWINWEBRTCCLIENTPLUGIN_RELEASE
(XosWinWebRtcClientPluginInterface* plugin)
{
    XosError error = XOS_ERROR_FAILED;
    XosWinWebRtcClientPluginExporter* exporter = 0;
    if ((exporter = XosWinWebRtcClientPluginExporter::GetExporter()))
        error = exporter->ReleasePlugin(plugin);
    return error;
}

///////////////////////////////////////////////////////////////////////
///  Class: XosWinWebRtcClientPluginDLibraryMain
///
/// Author: $author$
///   Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
static HMODULE hModule = 0;

///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientPluginDLibraryMain::WinInit
///
///    Author: $author$
///      Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientPluginDLibraryMain::WinInit()
{
    bool isTrue = true;
    if ((hModule = GetThisModuleHandle()))
        talk_base::Win32Window::SetInstance(hModule);
    return isTrue;
}
///////////////////////////////////////////////////////////////////////
///  Function: XosWinWebRtcClientPluginDLibraryMain::WinFinish
///
///    Author: $author$
///      Date: 12/10/2012
///////////////////////////////////////////////////////////////////////
bool XosWinWebRtcClientPluginDLibraryMain::WinFinish()
{
    bool isTrue = true;
    if ((hModule))
    {
        talk_base::Win32Window::Shutdown();
        hModule = 0;
    }
    return isTrue;
}

#if defined(c_NAMESPACE)
}
#endif // defined(c_NAMESPACE) 

        

