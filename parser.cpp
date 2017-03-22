#include "parser.h"

Filter Parser::_filter;

Parser::Parser( const Filter& filter )
{
	_filter.setIp( filter.getIp() );
	_filter.setPort( filter.getPort() );
}


Parser::~Parser()
{

}


void Parser::start( const char* file )
{
	pcap_t *descr;
	char errbuf[PCAP_ERRBUF_SIZE];

	descr = pcap_open_offline( file, errbuf );
	if ( descr == NULL )
	{
		std::cout << Q_FUNC_INFO << " failed: " << errbuf << endl;
		return;
	}

	if ( pcap_loop( descr, 0, pcap_handler, NULL ) < 0 )
	{
		std::cout << Q_FUNC_INFO << " failed: " << pcap_geterr( descr );
		return;
	}
}


void Parser::pcap_handler( u_char*, const pcap_pkthdr* h, const u_char* bytes )
{
	const struct ether_header* ethernetHeader;
	const struct ip* ipHeader;
	const struct udphdr* udpHeader;

	char destIp[INET_ADDRSTRLEN];
	u_int destPort;
	u_char *data;
	int dataLength = 0;

	ethernetHeader = (struct ether_header*)bytes;
	if ( ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP )
	{
		ipHeader = (struct ip*)(bytes + sizeof(struct ether_header));
		inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);

		QString timestamp( QString::number( h->ts.tv_sec ) + "." + QString::number( h->ts.tv_usec ) );

		if ( ipHeader->ip_p == IPPROTO_UDP )
		{
			udpHeader = (udphdr*)(bytes + sizeof(struct ether_header) + sizeof(struct ip));
			destPort = ntohs(udpHeader->dest);
			data = (u_char*)(bytes + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));
			dataLength = h->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct udphdr));

			if ( _filter.pass( QString( destIp ), destPort ) )
			{
				std::cout << timestamp.toStdString() << "\t" << destIp << "\t" \
						  << destPort << "\t" << dataLength << "\n";
			}
		}
	}
}

