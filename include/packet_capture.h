#ifndef __PACKET_CAPTURE_H__
#define __PACKET_CAPTURE_H__

#include <memory>
#include <string>

constexpr char filter[] = "udp port 53";

class PacketCapture {
	public:
		PacketCapture();
		~PacketCapture();
		void captrue();

	private:
		class Impl;
		std::unique_ptr<Impl> pImpl;
		std::string if_name;
};

#endif /* __PACKET_CAPTURE_H__ */