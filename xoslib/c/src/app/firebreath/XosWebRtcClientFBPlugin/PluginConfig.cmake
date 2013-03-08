########################################################################
# Copyright 2012, Google Inc.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote products
#     derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#   File: PluginConfig.cmake
#
# Author: $author$
#   Date: 4/3/2012
########################################################################

set(PLUGIN_NAME "XosWebRtcClientFBPlugin")
set(PLUGIN_MIMETYPE "application/x-xoswebrtcclientfbplugin")
set(PLUGIN_PREFIX "XWRTCCFBP")
set(PLUGIN_VERSION "1.0.0.0")
set(COMPANY_NAME "$organization$")
set(YEAR "2012")

#
# ActiveX constants
#
set(FBTYPELIB_NAME ${PLUGIN_NAME}Lib)
set(FBTYPELIB_DESC "${PLUGIN_NAME} ${PLUGIN_VERSION} Type Library")
set(IFBControl_DESC "${PLUGIN_NAME} Control Interface")
set(FBControl_DESC "${PLUGIN_NAME} Control Class")
set(IFBComJavascriptObject_DESC "${PLUGIN_NAME} IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "${PLUGIN_NAME} ComJavascriptObject Class")
set(IFBComEventSource_DESC "${PLUGIN_NAME} IFBComEventSource Interface")
set(AXVERSION_NUM "1")

#
# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
#
set(FBTYPELIB_GUID E505B5EE-0373-49B3-A946-147ACBE2F5DD)
set(IFBControl_GUID 0BFEC083-E472-488D-8B98-B5ABF380BEF4)
set(FBControl_GUID 1E0B9F77-6AFA-45CB-8936-257400815ED4)
set(IFBComJavascriptObject_GUID 00FDB872-6426-4D2C-88EC-A87AC54B69CD)
set(FBComJavascriptObject_GUID 1841D80B-6428-4AA7-B0CD-ACD27880EBBB)
set(IFBComEventSource_GUID F956F48E-2DBB-4057-8F58-31B79C2703C1)

#
# these are the pieces that are relevant to using it from Javascript
#
set(ACTIVEX_PROGID "${COMPANY_NAME}.${PLUGIN_NAME}")
set(MOZILLA_PLUGINID "${COMPANY_NAME}/${PLUGIN_NAME}")

#
# strings
#
set(FBSTRING_CompanyName "${COMPANY_NAME}")
set(FBSTRING_FileDescription "${PLUGIN_NAME} Plugin")
set(FBSTRING_PLUGIN_VERSION "${PLUGIN_VERSION}")
set(FBSTRING_LegalCopyright "Copyright ${YEAR} ${COMPANY_NAME}")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "${PLUGIN_NAME}")
set(FBSTRING_FileExtents "")
set(FBSTRING_PluginName "${PLUGIN_NAME}")
set(FBSTRING_MIMEType "${PLUGIN_MIMETYPE}")

# If you're not planning on your plugin doing any drawing, uncomment this line
#set (FB_GUI_DISABLED 1) 

#
# Mac plugin settings. If your plugin does not draw, set these all to 0
#
set(FBMAC_USE_QUICKDRAW 1)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 1)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 1)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1) 
