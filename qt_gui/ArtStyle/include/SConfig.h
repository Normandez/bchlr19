#ifndef SCONFIG_H
#define SCONFIG_H

#include <QString>
#include <QDomDocument>
#include <QFile>

// Global app's config
struct SConfig
{
	QString style_path;

	bool LoadConfig( const QString& file_name, QString& err_output = QString() );
};

#endif //SCONFIG_H
