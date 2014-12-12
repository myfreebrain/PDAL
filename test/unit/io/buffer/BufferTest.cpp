/******************************************************************************
* Copyright (c) 2014, Hobu Inc. (hobu@hobu.inc)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#include "gtest/gtest.h"

#include <pdal/PointBuffer.hpp>
#include <pdal/StageFactory.hpp>
#include <BufferReader.hpp>
#include <StatsFilter.hpp>

using namespace pdal;

namespace
{

TEST(BufferTest, test_basic)
{
    PointContext ctx;

    PointBufferPtr buf(new PointBuffer(ctx));

    ctx.registerDim(Dimension::Id::X);
    ctx.registerDim(Dimension::Id::Y);
    ctx.registerDim(Dimension::Id::Z);

    for (int i = 0; i < 20; ++i)
    {
        buf->setField(Dimension::Id::X, i, i);
        buf->setField(Dimension::Id::Y, i, 2 * i);
        buf->setField(Dimension::Id::Z, i, -i);
    }

    Options ops;
    BufferReader r;
    r.setOptions(ops);
    r.addBuffer(buf);

    StatsFilter s;
    s.setOptions(ops);
    s.setInput(&r);

    s.prepare(ctx);
    PointBufferSet pbSet = s.execute(ctx);
    EXPECT_EQ(pbSet.size(), 1u);
    buf = *pbSet.begin();
    EXPECT_EQ(buf->size(), 20u);

    stats::Summary xSummary = s.getStats(Dimension::Id::X);
    EXPECT_FLOAT_EQ(xSummary.minimum(), 0);
    EXPECT_FLOAT_EQ(xSummary.maximum(), 19);
    EXPECT_EQ(xSummary.count(), 20u);
    EXPECT_FLOAT_EQ(xSummary.average(), 9.5);

    stats::Summary ySummary = s.getStats(Dimension::Id::Y);
    EXPECT_FLOAT_EQ(ySummary.minimum(), 0);
    EXPECT_FLOAT_EQ(ySummary.maximum(), 38);
    EXPECT_EQ(ySummary.count(), 20u);
    EXPECT_FLOAT_EQ(ySummary.average(), 19);

    stats::Summary zSummary = s.getStats(Dimension::Id::Z);
    EXPECT_FLOAT_EQ(zSummary.minimum(), -19);
    EXPECT_FLOAT_EQ(zSummary.maximum(), 0);
    EXPECT_EQ(zSummary.count(), 20u);
    EXPECT_FLOAT_EQ(zSummary.average(), -9.5);
}

}
