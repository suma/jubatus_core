// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#include <map>
#include <string>
#include <gtest/gtest.h>
#include "exception.hpp"
#include "num_filter_factory.hpp"
#include "num_filter_impl.hpp"

namespace jubatus {
namespace core {
namespace fv_converter {

TEST(num_filter_factory, unknown_name) {
  num_filter_factory f;
  EXPECT_THROW(f.create("unknonw", std::map<std::string, std::string>()),
      converter_exception);
}

TEST(num_filter_factory, create_add_filter_with_illegal_config) {
  num_filter_factory f;
  std::map<std::string, std::string> params;
  EXPECT_THROW(f.create("add", params), converter_exception);
  params["value"] = "hoge";
  EXPECT_THROW(f.create("add", params), std::bad_cast);
}

TEST(num_filter_factory, create_add_filter) {
  num_filter_factory f;

  std::map<std::string, std::string> params;
  params["value"] = "10";
  jubatus::util::lang::shared_ptr<num_filter> filter(f.create("add", params));

  EXPECT_EQ(typeid(add_filter).name(), typeid(*filter).name());
  EXPECT_EQ(20.0, filter->filter(10.0));
}

}  // namespace fv_converter
}  // namespace core
}  // namespace jubatus
