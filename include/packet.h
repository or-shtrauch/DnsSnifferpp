#ifndef __PACKET_H__
#define __PACKET_H__

#include <string>

enum dns_record_type
{
	A = 1,
	CNAME = 5,
	AAAA = 28,
};

// struct dns_a

class dns_packet
{
	std::string domain;
	dns_record_type record_type;

	// public:
	// 	dns_packet(const std::string& domain,)
};

#endif // __PACKET_H__