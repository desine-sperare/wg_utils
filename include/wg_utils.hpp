#pragma once

#include <string>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include "time.hpp"

namespace timlibs
{
	std::string execute_command(const std::string& command);
	std::string wg_genkey();
	std::string wg_pubkey(const std::string& private_key);
	void wg_quick_up(const std::string& interface_name);
	void wg_quick_down(const std::string& interface_name);
	void wg_set_remove(const std::string& interface_name, const std::string& public_key);
	void wg_set(const std::string& interface_name, const std::string& public_key, const std::string& allowed_ips);
	std::unordered_map<std::string, Time> wg_show_latest_handshakes(const std::string& interface_name);
	std::vector<std::string> wg_show_peers(const std::string& interface_name);
}
