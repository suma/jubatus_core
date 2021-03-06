// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2013 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
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

#include "key_manager.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "assert.hpp"

using std::string;
using std::vector;
using jubatus::util::data::unordered_map;

namespace jubatus {
namespace core {
namespace common {

typedef unordered_map<string, uint64_t>::const_iterator cit;

key_manager::key_manager()
    : next_id_(0u) {
}

uint64_t key_manager::append_key(const string& key) {
  JUBATUS_ASSERT_EQ(true,  // must not exist
                    key2id_.end() == key2id_.find(key),
                    "existing key appended");
  key2id_[key] = next_id_;
  id2key_[next_id_] = key;
  return next_id_++;
}

uint64_t key_manager::get_id(const string& key) {
  cit it = key2id_.find(key);
  if (it != key2id_.end()) {
    return it->second;
  }
  // TODO(beam2d): Make it exception safe.
  return append_key(key);
}

bool key_manager::set_key(const string& key) {
  cit it = key2id_.find(key);
  if (it != key2id_.end()) {
    return false;
  }
  // TODO(kumagi): Make it exception safe.
  append_key(key);
  return true;
}

uint64_t key_manager::get_id_const(const string& key) const {
  cit it = key2id_.find(key);
  if (it != key2id_.end()) {
    return it->second;
  } else {
    return NOTFOUND;
  }
}

const std::string key_not_found = "";  // const object has internal linkage

const string& key_manager::get_key(const uint64_t id) const {
  unordered_map<uint64_t, string>::const_iterator it = id2key_.find(id);
  if (it != id2key_.end()) {
    return it->second;
  } else {
    return key_not_found;
  }
}

std::vector<std::string> key_manager::get_all_id2key() const {
  std::vector<std::string> ret;
  ret.reserve(id2key_.size());
  for (unordered_map<uint64_t, string>::const_iterator it = id2key_.begin();
       it != id2key_.end();
       ++it) {
    ret.push_back(it->second);
  }
  return ret;
}

void key_manager::clear() {
  jubatus::util::data::unordered_map<std::string, uint64_t>().swap(key2id_);
  jubatus::util::data::unordered_map<uint64_t, std::string>().swap(id2key_);
  next_id_ = 0u;
}

void key_manager::init_by_id2key(const std::vector<std::string>& id2key) {
  key2id_.clear();
  id2key_.clear();

  for (size_t i = 0; i < id2key.size(); ++i) {
    key2id_[id2key[i]] = i;
    id2key_[i] = id2key[i];
  }
  next_id_ = id2key.size();
}

void key_manager::delete_key(const std::string& name) {
  const uint64_t id = get_id_const(name);
  if (id != NOTFOUND) {
    key2id_.erase(name);
    id2key_.erase(id);
  }
}

}  // namespace common
}  // namespace core
}  // namespace jubatus
