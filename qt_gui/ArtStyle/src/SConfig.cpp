#include "SConfig.h"

/*
Load file content into file object
    Arguments:
        'file_name' - config file full name (XML format)
    Returns:
        Boolean true - all OK, false - loading failed
*/
bool SConfig::LoadConfig( const QString& file_name, QString& err_output /*= QString()*/ )
{
	// Load content
	QFile config_file(file_name);
	if( !config_file.open(QIODevice::ReadOnly) )
	{
		err_output = "Config file not opened\n" + file_name;
		return false;
	}
	QDomDocument xml_doc;
	if( !xml_doc.setContent(&config_file) )
	{
		err_output = "Config file bad format: XML parsing failed\n" + file_name;
		return false;
	}

	// Parse content
	QDomElement root = xml_doc.documentElement();
	this->style_path = root.firstChildElement("style_path").text();
	this->style_transformator = root.firstChildElement("style_transformator").text();
	{
		QDomElement transformation_scripts = root.firstChildElement("transformation_scripts");
		this->transformation_scripts.root_path = transformation_scripts.firstChildElement("root_path").text();
		this->transformation_scripts.image = transformation_scripts.firstChildElement("image").text();
		this->transformation_scripts.video = transformation_scripts.firstChildElement("video").text();
	}

	// All OK
	err_output = "";
	return true;
}
