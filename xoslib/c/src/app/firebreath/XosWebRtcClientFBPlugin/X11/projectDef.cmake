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
#   File: projectDef.cmake
#
# Author: $author$
#   Date: 4/20/2012
########################################################################

#
# X11 template platform definition CMake file
# Included from ../CMakeLists.txt
#

if(NOT DEFINED BUILD_TYPE)
set (BUILD_TYPE "Debug")
endif()

set (SOURCE_ROOT "$ENV{HOME}/source/frameworks")

########################################################################
# WebRTC
# ...
########################################################################
if(NOT DEFINED WEBRTC_REVISION_NUMBER)
set (WEBRTC_REVISION_NUMBER "1125")
endif()

set (WEBRTC_GROUP "webrtc/")
set (WEBRTC_NAME "webrtc")
set (WEBRTC_VERSION "-trunk-r-")

set (WEBRTC_ROOT "${SOURCE_ROOT}/${WEBRTC_GROUP}${WEBRTC_NAME}${WEBRTC_VERSION}${WEBRTC_REVISION_NUMBER}")
set (WEBRTC_OUTPUT "${WEBRTC_ROOT}/out")
set (WEBRTC_BUILD "${WEBRTC_OUTPUT}/${BUILD_TYPE}")
set (WEBRTC_LIB "${WEBRTC_BUILD}")

set(WEBRTC_INCLUDE_DIRS 
${WEBRTC_ROOT}
${WEBRTC_ROOT}/src
${WEBRTC_ROOT}/third_party/libjingle/source
${WEBRTC_ROOT}/third_party_mods/libjingle/source
${WEBRTC_ROOT}/third_party/expat/files/lib
)

set(WEBRTC_LIB_DIRS 
${WEBRTC_BUILD}/obj.host/third_party 
${WEBRTC_BUILD}/obj.host/third_party/yasm 
${WEBRTC_BUILD}/obj.host/third_party/protobuf 
${WEBRTC_BUILD}/obj.target/src 
${WEBRTC_BUILD}/obj.target/src/modules 
${WEBRTC_BUILD}/obj.target/src/common_audio 
${WEBRTC_BUILD}/obj.target/src/common_video 
${WEBRTC_BUILD}/obj.target/src/voice_engine 
${WEBRTC_BUILD}/obj.target/src/video_engine 
${WEBRTC_BUILD}/obj.target/src/system_wrappers/source 
${WEBRTC_BUILD}/obj.target/third_party/libjpeg_turbo 
${WEBRTC_BUILD}/obj.target/third_party/libvpx 
${WEBRTC_BUILD}/obj.target/third_party/protobuf 
${WEBRTC_BUILD}/obj.target/third_party_mods/libjingle
)

set (WEBRTC_DEFINES 
-DLINUX
-DPOSIX
-DWEBRTC_REVISION=${WEBRTC_REVISION_NUMBER}
)

set(WEBRTC_1125_EXTERNAL_LIBS 
-lgtk-x11-2.0 
-lgdk-x11-2.0 
-latk-1.0 
-lgio-2.0 
-lpangoft2-1.0 
-lpangocairo-1.0 
-lgdk_pixbuf-2.0 
-lm 
-lcairo 
-lpng12 
-lpango-1.0 
-lfreetype 
-lfontconfig 
-lgobject-2.0 
-lgmodule-2.0 
-lgthread-2.0 
-lrt 
-lglib-2.0 
-lX11 
-lXext 
-lexpat 
-lGL
-lGLU
-ldl 
-lasound 
-lpulse
-lpthread
)

set(WEBRTC_1125_INTERNAL_LIB_A
${WEBRTC_LIB}/libWebRtc.a
)

set(WEBRTC_1125_INTERNAL_LIBS_A 
${WEBRTC_BUILD}/obj.target/src/system_wrappers/source/libsystem_wrappers.a 
${WEBRTC_BUILD}/obj.host/third_party/yasm/libgenperf_libs.a 
${WEBRTC_BUILD}/obj.host/third_party/protobuf/libprotobuf_lite.a 
${WEBRTC_BUILD}/obj.host/third_party/protobuf/libprotobuf_full_do_not_use.a 
${WEBRTC_BUILD}/obj.target/third_party_mods/libjingle/libjingle_app.a 
${WEBRTC_BUILD}/obj.target/third_party_mods/libjingle/libjsoncpp.a 
${WEBRTC_BUILD}/obj.target/src/modules/libvideo_capture_module.a 
${WEBRTC_BUILD}/obj.target/src/modules/libwebrtc_utility.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaudio_coding_module.a 
${WEBRTC_BUILD}/obj.target/src/modules/libCNG.a 
${WEBRTC_BUILD}/obj.target/src/common_audio/libsignal_processing.a 
${WEBRTC_BUILD}/obj.target/src/modules/libG711.a 
${WEBRTC_BUILD}/obj.target/src/modules/libG722.a 
${WEBRTC_BUILD}/obj.target/src/modules/libiLBC.a 
${WEBRTC_BUILD}/obj.target/src/modules/libiSAC.a 
${WEBRTC_BUILD}/obj.target/src/modules/libiSACFix.a 
${WEBRTC_BUILD}/obj.target/src/modules/libPCM16B.a 
${WEBRTC_BUILD}/obj.target/src/modules/libNetEq.a 
${WEBRTC_BUILD}/obj.target/src/common_audio/libresampler.a 
${WEBRTC_BUILD}/obj.target/src/common_audio/libvad.a 
${WEBRTC_BUILD}/obj.target/src/modules/libwebrtc_video_coding.a 
${WEBRTC_BUILD}/obj.target/src/modules/libwebrtc_i420.a 
${WEBRTC_BUILD}/obj.target/src/modules/libwebrtc_vp8.a 
${WEBRTC_BUILD}/obj.target/third_party/libvpx/libvpx.a 
${WEBRTC_BUILD}/obj.target/src/common_video/libwebrtc_vplib.a 
${WEBRTC_BUILD}/obj.target/src/modules/libvideo_render_module.a 
${WEBRTC_BUILD}/obj.target/src/video_engine/libvideo_engine_core.a 
${WEBRTC_BUILD}/obj.target/src/common_video/libwebrtc_jpeg.a 
${WEBRTC_BUILD}/obj.target/third_party/libjpeg_turbo/libjpeg_turbo.a 
${WEBRTC_BUILD}/obj.target/src/modules/libmedia_file.a 
${WEBRTC_BUILD}/obj.target/src/modules/librtp_rtcp.a 
${WEBRTC_BUILD}/obj.target/src/modules/libudp_transport.a 
${WEBRTC_BUILD}/obj.target/src/modules/libvideo_processing.a 
${WEBRTC_BUILD}/obj.target/src/voice_engine/libvoice_engine_core.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaudio_conference_mixer.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaudio_processing.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaec.a 
${WEBRTC_BUILD}/obj.target/src/modules/libapm_util.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaecm.a 
${WEBRTC_BUILD}/obj.target/src/modules/libagc.a 
${WEBRTC_BUILD}/obj.target/src/modules/libns.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaudioproc_debug_proto.a 
${WEBRTC_BUILD}/obj.target/third_party/protobuf/libprotobuf_lite.a 
${WEBRTC_BUILD}/obj.target/src/modules/libaudio_device.a 
${WEBRTC_BUILD}/obj.target/third_party_mods/libjingle/libjingle_p2p.a 
${WEBRTC_BUILD}/obj.target/third_party_mods/libjingle/libjingle.a
)

set(L_WEBRTC_1125_INTERNAL_LIBS 
-lgenperf_libs 
-lprotobuf_lite 
-lprotobuf_full_do_not_use 
-ljingle_app 
-ljsoncpp 
-lvideo_capture_module 
-lwebrtc_utility 
-laudio_coding_module 
-lCNG 
-lsignal_processing 
-lG711 
-lG722 
-liLBC 
-liSAC 
-liSACFix 
-lPCM16B 
-lNetEq 
-lresampler 
-lvad 
-lsystem_wrappers 
-lwebrtc_video_coding 
-lwebrtc_i420 
-lwebrtc_vp8 
-lvpx 
-lwebrtc_vplib 
-lvideo_render_module 
-lvideo_engine_core 
-lwebrtc_jpeg 
-ljpeg_turbo 
-lmedia_file 
-lrtp_rtcp 
-ludp_transport 
-lvideo_processing 
-lvoice_engine_core 
-laudio_conference_mixer 
-laudio_processing 
-laec 
-lapm_util 
-laecm 
-lagc 
-lns 
-laudioproc_debug_proto 
-lprotobuf_lite 
-laudio_device 
-ljingle_p2p 
-ljingle
)

set(WEBRTC_1125_INTERNAL_LIBS 
${WEBRTC_1125_INTERNAL_LIB_A}
)

set(WEBRTC_LIBS 
${WEBRTC_${WEBRTC_REVISION_NUMBER}_INTERNAL_LIBS} 
${WEBRTC_${WEBRTC_REVISION_NUMBER}_EXTERNAL_LIBS}
)
########################################################################
# ...
# WebRTC
########################################################################

########################################################################
# XosLib
# ...
########################################################################
set (XOSLIB_ROOT "${SOURCE_ROOT}/xoslib")
set (XOSLIB_OUTPUT "${XOSLIB_ROOT}/build/linux")
set (XOSLIB_BUILD "${XOSLIB_OUTPUT}/${BUILD_TYPE}")
set (XOSLIB_SRC "${XOSLIB_ROOT}/c/src")

set (XOSLIB_BUILD_BIN "${XOSLIB_BUILD}/bin")
set (XOSLIB_BUILD_LIB "${XOSLIB_BUILD}/lib")

set (XOSLIB_INCLUDE_DIRS 
"${XOSLIB_SRC}/lib/firebreath" 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient/XosX11" 
"${XOSLIB_SRC}/lib/XosWebRtc/XosWebRtcClient" 
"${XOSLIB_SRC}/lib/XosGui/XosGtk/XosGdk/XosPlatform" 
"${XOSLIB_SRC}/lib/XosGui/XosGtk/XosGdk" 
"${XOSLIB_SRC}/lib/XosGui/XosGtk/XosPlatform" 
"${XOSLIB_SRC}/lib/XosGui/XosGtk" 
"${XOSLIB_SRC}/lib/XosGui/XosX11/cgl/cplatform" 
"${XOSLIB_SRC}/lib/XosGui/XosX11/cx11/cplatform" 
"${XOSLIB_SRC}/lib/XosGui/XosX11/XosPlatform" 
"${XOSLIB_SRC}/lib/XosGui/XosX11" 
"${XOSLIB_SRC}/lib/XosGui" 
"${XOSLIB_SRC}/lib/XosNetwork/XosUnix" 
"${XOSLIB_SRC}/lib/XosNetwork" 
"${XOSLIB_SRC}/lib/XosCore/XosThread/XosUnix" 
"${XOSLIB_SRC}/lib/XosCore/XosThread" 
"${XOSLIB_SRC}/lib/XosCore" 
"${XOSLIB_SRC}/lib/Generic/Platform" 
"${XOSLIB_SRC}/lib/Generic" 
"${XOSLIB_SRC}/lib/XosPlatform" 
)

set (XOSLIB_LIB_DIRS 
"${XOSLIB_BUILD_LIB}"
)

set (XOSLIB_DEFINES 
)

set (XOSLIB_LIBS 
"${XOSLIB_BUILD_LIB}/libXosWebRtcCore.a"
"${XOSLIB_BUILD_LIB}/libXosWebRtcClient.a"
)
########################################################################
# ...
# XosLib
########################################################################

#
# remember that the current source dir is the project root; this file is in X11/
#
file (GLOB PLATFORM RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    X11/*.cpp
    X11/*.hpp
    X11/*.cc
    X11/*.h
    X11/*.cmake
    )

SOURCE_GROUP(X11 FILES ${PLATFORM})

#
# use this to add preprocessor definitions
#
add_definitions(
${WEBRTC_DEFINES}
${XOSLIB_DEFINES}
)

set (SOURCES
    ${SOURCES}
    ${PLATFORM}
    )

add_x11_plugin(${PROJECT_NAME} SOURCES)

#
# add incluide directories here
#
include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}/"
${XOSLIB_INCLUDE_DIRS}
${WEBRTC_INCLUDE_DIRS}
)

#
# add library directories here
#
#link_directories(
#${XOSLIB_LIB_DIRS}
#${WEBRTC_LIB_DIRS}
#)

#
# add library dependencies here; leave ${PLUGIN_INTERNAL_DEPS} there unless you know what you're doing!
#
target_link_libraries(${PROJECT_NAME}
    ${PLUGIN_INTERNAL_DEPS}
    ${XOSLIB_LIBS}
    ${WEBRTC_LIBS}
    )

