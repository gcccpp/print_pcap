#include <QCoreApplication>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>

#include "parser.h"
#include "filter.h"

Filter filter;

int main( int argc, char *argv[] )
{
	QCoreApplication app( argc, argv );

	int par = 0;

	while( (par = getopt(argc, argv, "a:p:")) != -1 )
	{
		switch ( par )
		{
		case 'a' :
		{
			filter.setIp( QString( optarg ) );
			break;
		}
		case 'p' :
		{
			filter.setPort( QString( optarg ).toInt() );
			break;
		}
		}
	};


	Parser parser( filter );

	parser.start( argv[ optind ] );

	return app.exec();
}

