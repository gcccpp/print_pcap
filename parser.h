#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <iostream>

#include "filter.h"

class Parser
{
	static Filter _filter;
public:
	explicit Parser( const Filter& filter );
	virtual ~Parser();

	static void pcap_handler( u_char* user, const struct pcap_pkthdr* h, const u_char* bytes );

	void start( const char* file );

private:
};

#endif // PARSER_H
