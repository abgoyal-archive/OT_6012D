// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_HOST_PORT_PAIR_H_
#define NET_BASE_HOST_PORT_PAIR_H_
#pragma once

#include <string>
#include "base/basictypes.h"
/// M: HTML5 web socket
#include "net/base/net_export.h"

struct addrinfo;
class GURL;

namespace net {

/// M: HTML5 web socket
class NET_EXPORT HostPortPair {
 public:
  HostPortPair();
  // If |in_host| represents an IPv6 address, it should not bracket the address.
  HostPortPair(const std::string& in_host, uint16 in_port);

  // Creates a HostPortPair for the origin of |url|.
  static HostPortPair FromURL(const GURL& url);

  // Creates a HostPortPair from an addrinfo struct.
  static HostPortPair FromAddrInfo(const struct addrinfo* ai);

  // TODO(willchan): Define a functor instead.
  // Comparator function so this can be placed in a std::map.
  bool operator<(const HostPortPair& other) const {
    if (port_ != other.port_)
      return port_ < other.port_;
    return host_ < other.host_;
  }

  // Equality test of contents. (Probably another violation of style guide).
  bool Equals(const HostPortPair& other) const {
    return host_ == other.host_ && port_ == other.port_;
  }

  const std::string& host() const {
    return host_;
  }

  uint16 port() const {
    return port_;
  }

  void set_host(const std::string& in_host) {
    host_ = in_host;
  }

  void set_port(uint16 in_port) {
    port_ = in_port;
  }

  // ToString() will convert the HostPortPair to "host:port".  If |host_| is an
  // IPv6 literal, it will add brackets around |host_|.
  std::string ToString() const;

  // Returns |host_|, adding IPv6 brackets if needed.
  std::string HostForURL() const;

 private:
  // If |host_| represents an IPv6 address, this string will not contain
  // brackets around the address.
  std::string host_;
  uint16 port_;
};

}  // namespace net

#endif  // NET_BASE_HOST_PORT_PAIR_H_
