#ifndef SCONFIG_H
#define SCONFIG_H

#include <QString>
#include <QDomDocument>
#include <QFile>

// Global app's config
struct SConfig
{
	QString style_path;
	QString style_transformator;
	struct STransformationScripts
	{
		QString root_path;
		QString image;
		QString video;
	} transformation_scripts ;

	bool LoadConfig( const QString& file_name, QString& err_output = QString() );
};

#endif //SCONFIG_H
