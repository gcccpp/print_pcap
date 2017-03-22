#include "filter.h"

Filter::Filter() :
	_ip( QString() ),
	_port( 0 )
{

}


Filter::~Filter()
{

}


bool Filter::pass( QString ip, u_int port )
{
	return passIp( ip ) && passPort( port );
}


bool Filter::passIp( QString ip )
{
	return ( !getIp().isEmpty() ) ? ip == getIp() : true;
}

bool Filter::passPort( u_int port )
{
	return ( getPort() != 0 ) ? port == getPort() : true;
}

