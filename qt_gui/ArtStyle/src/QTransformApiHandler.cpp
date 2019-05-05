#include "QTransformApiHandler.h"

static const QString s_out_file_line_pattern = "OUT_FILE=";

QTransformApiHandler::QTransformApiHandler( const SContext* global_context, QObject* parent /*= nullptr*/ )
	: QObject(parent),
	  m_context(global_context),
	  m_current_transform_type(ETransformationType::ETransformationType_Empty),
	  m_is_in_progress(false)
{
	m_transform_proc.setWorkingDirectory(global_context->config.transformation_scripts.root_path);

	bool connect_chk = connect( &m_transform_proc, SIGNAL( finished( int, QProcess::ExitStatus ) ), this, SLOT( onProcessFinished( int, QProcess::ExitStatus ) ) );
	Q_ASSERT(connect_chk);
	connect_chk = connect( &m_transform_proc, SIGNAL( error( QProcess::ProcessError ) ), this, SLOT( onProcessError( QProcess::ProcessError ) ) );
	Q_ASSERT(connect_chk);
}

QTransformApiHandler::~QTransformApiHandler()
{
	this->disconnect();
	m_transform_proc.blockSignals(true);
	m_transform_proc.close();
	m_transform_proc.kill();
}

void QTransformApiHandler::StartTransform( ETransformationType transformation_type, const QString& checkpoint, const QString& in_path, const QString& out_path )
{
	m_is_in_progress = true;
	m_current_transform_type = transformation_type;

	QString script = "";
	switch(m_current_transform_type)
	{
	case ETransformationType::ETransformationType_Img:
		script = m_context->config.transformation_scripts.image;
		break;

	case ETransformationType::ETransformationType_Video:
		script = m_context->config.transformation_scripts.video;
		break;
	}

	QStringList launch_params = { script, "--checkpoint", checkpoint, "--in-path", in_path, "--out-path", out_path };

	m_transform_proc.start( m_context->config.style_transformator, launch_params );
}

void QTransformApiHandler::StopTransform()
{
	m_is_in_progress = false;
	m_current_transform_type = ETransformationType::ETransformationType_Empty;

	m_transform_proc.kill();
}

bool QTransformApiHandler::IsInProgress() const
{
	return m_is_in_progress;
}

void QTransformApiHandler::onProcessFinished( int exit_code, QProcess::ExitStatus exit_status )
{
	if (!m_is_in_progress) return;

	if( exit_code == 0 )
	{
		QStringList std_output_lines = QString( m_transform_proc.readAllStandardOutput() ).split("\n");
		QString out_file = "";
		foreach( QString str, std_output_lines )
		{
			if( str.contains(s_out_file_line_pattern) )
			{
				out_file = str.remove(s_out_file_line_pattern);
			}
		}

		emit transformationFinished( m_current_transform_type, 0, out_file );
	}
	else
	{
		QString std_error_output = m_transform_proc.readAllStandardError();
		emit transformationFinished( m_current_transform_type, exit_code, std_error_output );
	}

	m_is_in_progress = false;
	m_current_transform_type = ETransformationType::ETransformationType_Empty;
}

void QTransformApiHandler::onProcessError( QProcess::ProcessError error )
{
	if (!m_is_in_progress) return;

	emit transformationFinished( m_current_transform_type, 1, "Process startup failed. Check paths and names in config." );

	m_is_in_progress = false;
	m_current_transform_type = ETransformationType::ETransformationType_Empty;
}
