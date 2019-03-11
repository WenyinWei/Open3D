// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
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
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "TestUtility/UnitTest.h"

#include "Open3D/Types/Types.h"

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Test reading/writing using the subscript operator.
// ----------------------------------------------------------------------------
TEST(Types, subscript_ops) {
    open3d::Matrix3f m = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};

    for (uint r = 0; r < m.ROWS; r++)
        for (uint c = 0; c < m.COLS; c++) {
            m[r][c] = r * 1.0f + c * 0.1f;
            EXPECT_FLOAT_EQ(m[r][c], r * 1.0f + c * 0.1f);
        }

    open3d::Vector3f v = {0.0f, 0.1f, 0.2f};

    for (uint c = 0; c < m.COLS; c++) {
        v[c] = c * 0.12f;
        EXPECT_FLOAT_EQ(v[c], c * 0.12f);
    }
}

// ----------------------------------------------------------------------------
// The data type size varies based on alignment:
// - without custom alignment the size matches N x sizeof(TYPE)
// - with custom alignment the size is different than N x sizeof(TYPE)
// ----------------------------------------------------------------------------
TEST(Types, sizeof_type) {
    EXPECT_EQ(3 * sizeof(double), sizeof(Eigen::Vector3d));

    EXPECT_EQ(3 * 3 * sizeof(double), sizeof(open3d::Matrix3d));
    EXPECT_EQ(3 * 3 * sizeof(float), sizeof(open3d::Matrix3f));

    EXPECT_EQ(4 * 4 * sizeof(float), sizeof(open3d::Matrix4f));
    EXPECT_EQ(4 * 4 * sizeof(double), sizeof(open3d::Matrix4d));

    EXPECT_EQ(6 * 6 * sizeof(float), sizeof(open3d::Matrix6f));
    EXPECT_EQ(6 * 6 * sizeof(double), sizeof(open3d::Matrix6d));

    EXPECT_EQ(3 * sizeof(double), sizeof(open3d::Vector3d));
    EXPECT_EQ(3 * sizeof(float), sizeof(open3d::Vector3f));
    EXPECT_EQ(3 * sizeof(int), sizeof(open3d::Vector3i));
}

// ----------------------------------------------------------------------------
// Test ==, !=, <=, >=.
// ----------------------------------------------------------------------------
TEST(Types, comparison_ops_float) {
    open3d::Matrix3f m0 = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f,
                           5.0f, 6.0f, 7.0f, 8.0f};
    open3d::Matrix3f m1 = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f,
                           5.0f, 6.0f, 7.0f, 8.0f};
    EXPECT_TRUE(m0 == m1);
    EXPECT_TRUE(m0 <= m1);

    m0[1][0] = 3.1f;
    EXPECT_TRUE(m0 != m1);
    EXPECT_TRUE(m0 >= m1);

    open3d::Vector3f v0 = {0.0f, 0.1f, 0.2f};
    open3d::Vector3f v1 = {0.0f, 0.1f, 0.2f};
    EXPECT_TRUE(v0 == v1);
    EXPECT_TRUE(v0 <= v1);

    v0[2] = 1.2f;
    EXPECT_TRUE(v0 != v1);
    EXPECT_TRUE(v0 >= v1);
}

// ----------------------------------------------------------------------------
// Test ==, !=, <=, >=.
// ----------------------------------------------------------------------------
TEST(Types, comparison_ops_double) {
    open3d::Matrix3d m0 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    open3d::Matrix3d m1 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    EXPECT_TRUE(m0 == m1);
    EXPECT_TRUE(m0 <= m1);

    m0[1][0] = 3.1;
    EXPECT_TRUE(m0 != m1);
    EXPECT_TRUE(m0 >= m1);

    open3d::Vector3d v0 = {0.0, 0.1, 0.2};
    open3d::Vector3d v1 = {0.0, 0.1, 0.2};
    EXPECT_TRUE(v0 == v1);
    EXPECT_TRUE(v0 <= v1);

    v0[2] = 1.2;
    EXPECT_TRUE(v0 != v1);
    EXPECT_TRUE(v0 >= v1);
}