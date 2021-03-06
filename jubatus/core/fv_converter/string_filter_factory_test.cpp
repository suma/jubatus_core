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
#include "regexp_filter.hpp"
#include "string_filter_factory.hpp"

namespace jubatus {
namespace core {
namespace fv_converter {

#if defined(HAVE_RE2) || defined(HAVE_ONIGURUMA)
TEST(string_filter_factory, trivial) {
  string_filter_factory f;
  std::map<std::string, std::string> p;
  p["pattern"] = ".*";
  p["replace"] = "";

  jubatus::util::lang::shared_ptr<string_filter> filter(f.create("regexp", p));
  EXPECT_TRUE(typeid(*filter) == typeid(regexp_filter));
}
#endif

TEST(string_filter_factory, unknown) {
  string_filter_factory f;
  std::map<std::string, std::string> p;
  EXPECT_THROW(f.create("unknown", p), converter_exception);
}

}  // namespace fv_converter
}  // namespace core
}  // namespace jubatus
