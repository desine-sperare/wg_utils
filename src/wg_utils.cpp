#include "wg_utils.hpp"
#include "string_utils.hpp"
#include <fstream>

#define WG_UTILS_TMP_FILE std::string("tmp.wireguard_api")

namespace timlibs
{
	std::string execute_command(const std::string& command)
	{
		std::system((command + " > " + WG_UTILS_TMP_FILE).c_str());
		std::ifstream file(WG_UTILS_TMP_FILE);
		std::string value{ "" };
		if (file.is_open()) value = file.get();
		file.close();
		std::system(("rm " + WG_UTILS_TMP_FILE).c_str());
		return value;
	}

	std::unordered_map<std::string, Time> wg_show_latest_handshakes(const std::string& interface_name)
	{
		std::string latest_handshakes = execute_command("wg show " + interface_name + " latest-handshakes");
		std::vector<std::string> splitted = split(latest_handshakes, '\n');
		std::unordered_map<std::string, Time> values;
		for (std::string latest_hanshake : splitted)
		{
			std::string public_key = split(latest_hanshake, ' ')[0];
			Time time = Time(std::stoi(split(latest_hanshake, ' ')[1]));
			values[public_key] = time;
		}
		return values;
	}

	std::string wg_genkey()
	{
		return execute_command("wg genkey");
	}

	std::string wg_pubkey(const std::string& private_key)
	{
		return execute_command("wg pubkey " + private_key);
	}

	void wg_quick_up(const std::string& interface_name)
	{
		execute_command("wg-quick up " + interface_name);
	}

	void wg_quick_down(const std::string& interface_name)
	{
		execute_command("wg-quick down " + interface_name);
	}

	void wg_set_remove(const std::string& interface_name, const std::string& public_key)
	{
		execute_command("wg set " + interface_name + " peer \"" + public_key + "\" remove");
	}

	void wg_set(const std::string& interface_name, const std::string& public_key, const std::string& allowed_ips)
	{
		execute_command("wg set " + interface_name + " peer \"" + public_key + "\" allowed-ips " + allowed_ips);
	}

	std::vector<std::string> wg_show_peers(const std::string& interface_name)
	{
		auto peers_public_keys_all = execute_command("wg show " + interface_name + " peers");
		std::vector<std::string> peers_public_keys{};
		for (std::string peer_public_key : split(peers_public_keys_all, '\n'))
		{
			peers_public_keys.push_back(peer_public_key);
		}
		return peers_public_keys;
	}
}