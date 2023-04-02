﻿// -----------------------------------------------------------------------------------------
//     rkmppenc by rigaya
// -----------------------------------------------------------------------------------------
// The MIT License
//
// Copyright (c) 2014-2017 rigaya
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// IABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// ------------------------------------------------------------------------------------------

#pragma once
#include "rgy_version.h"
#include "rgy_err.h"
#include "rgy_util.h"
#include "rgy_filter.h"
#include "mpp_util.h"


class RGAFilter : public RGYFilter {
public:
    RGAFilter();
    virtual ~RGAFilter();
    RGY_ERR filter_rga(RGYFrameInfo *pInputFrame, RGYFrameInfo **ppOutputFrames, int *pOutputFrameNum, int *sync);
protected:
    virtual RGY_ERR run_filter(const RGYFrameInfo *pInputFrame, RGYFrameInfo **ppOutputFrames, int *pOutputFrameNum, RGYOpenCLQueue &queue, const std::vector<RGYOpenCLEvent> &wait_events, RGYOpenCLEvent *event) override;
    virtual RGY_ERR run_filter_rga(const RGYFrameInfo *pInputFrame, RGYFrameInfo **ppOutputFrames, int *pOutputFrameNum, int *sync) = 0;
    virtual RGY_ERR AllocFrameBuf(const RGYFrameInfo &frame, int frames) override;
    virtual RGY_ERR AllocFrameBufRGA(const RGYFrameInfo &frame, int frames);

    std::vector<std::unique_ptr<RGYMPPRGAFrame>> m_frameBufRGA;
};

class RGAFilterResize : public RGAFilter {
public:
    RGAFilterResize();
    virtual ~RGAFilterResize();
    virtual RGY_ERR init(shared_ptr<RGYFilterParam> param, shared_ptr<RGYLog> pPrintMes) override;
protected:
    virtual RGY_ERR run_filter_rga(const RGYFrameInfo *pInputFrame, RGYFrameInfo **ppOutputFrames, int *pOutputFrameNum, int *sync) override;
    RGY_ERR checkParams(const RGYFilterParam *param);  
    virtual void close() override;

    rga_buffer_handle_t getRGABufferHandle(const RGYFrameInfo *frame);
};
