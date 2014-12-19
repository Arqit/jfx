/*
 * Copyright (c) 2010, 2014, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#ifndef _VIDEO_FRAME_H_
#define _VIDEO_FRAME_H_

#include <stdlib.h>

/**
 * class CVideoFrame
 *
 * Class representing a video frame.  Specific engines may have their own derived
 * classes.  For example, CGstVideoFrame.
 */
class CVideoFrame
{
public:
    enum FrameType
    {
        UNKNOWN,
        // NOTE: These MUST be kept in sync with the native types in com.sun.media.jfxmedia.control.VideoFormat
        ARGB = 1,
        BGRA_PRE = 2,
        YCbCr_420p = 100,
        YCbCr_422 = 101,
        YCbCr_422_rev = 102
    };

public:
    CVideoFrame();
    virtual ~CVideoFrame();

    virtual void        Dispose() {}

    double              GetTime();

    int                 GetWidth();
    int                 GetHeight();
    int                 GetEncodedWidth();
    int                 GetEncodedHeight();

    FrameType           GetType();
    bool                HasAlpha();

    int                 GetPlaneCount();
    void*               GetDataForPlane(int planeIndex);
    unsigned long       GetSizeForPlane(int planeIndex);
    int                 GetStrideForPlane(int planeIndex);

    virtual CVideoFrame *ConvertToFormat(FrameType type);

    bool                GetFrameDirty() { return m_FrameDirty; }
    void                SetFrameDirty(bool dirty) { m_FrameDirty = dirty; }

protected:
    int                 m_iWidth;
    int                 m_iHeight;
    int                 m_iEncodedWidth;
    int                 m_iEncodedHeight;
    FrameType           m_typeFrame;
    bool                m_bHasAlpha;
    double              m_dTime;
    bool                m_FrameDirty;

    // frame data buffers
    int                 m_iPlaneCount;
    void*               m_pvPlaneData[4];
    unsigned long       m_pulPlaneSize[4];
    int                 m_piPlaneStrides[4];

    void SwapPlanes(int aa, int bb);
};

#endif  //_VIDEO_FRAME_H_
