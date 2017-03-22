#ifndef FILTER_H
#define FILTER_H

#include <QDebug>

class Filter
{
public:
	explicit Filter();
	~Filter();

	inline void setIp( QString ip ) { _ip = ip; }
	inline QString getIp() const { return _ip; }

	inline void setPort( u_int port ) { _port = port; }
	inline u_int getPort() const { return _port; }

	bool pass( QString ip, u_int port );

private:
	QString _ip;
	u_int _port;

	bool passIp( QString ip );
	bool passPort( u_int port );
};

#endif // FILTER_H
