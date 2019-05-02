#include <QApplication>

#include <QMessageBox>

#include "SContext.h"
#include "QStyleTransformator.h"

//#include <Windows.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
	QString app_dir_path = app.applicationDirPath();

	// Load global config
	SContext global_context;
	QString config_load_err = "";
	if( !global_context.config.LoadConfig( QString("%1/config.xml").arg(app_dir_path), config_load_err ) )
	{
		QMessageBox err_msg( QMessageBox::Critical, "ERROR", config_load_err );
		err_msg.exec();
		return 1;
	}

	// Init and start app
	QStyleTransformator style_transformator(&global_context);
	style_transformator.Start();

    return app.exec();
}
