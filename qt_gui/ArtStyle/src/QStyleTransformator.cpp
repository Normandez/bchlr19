#include "QStyleTransformator.h"

#include <QMessageBox>

QStyleTransformator::QStyleTransformator( const SContext* global_context, QObject* parent /*= nullptr*/ )
	: QObject(parent)
{
	QMainWnd* main_wnd = new QMainWnd(global_context);
	QTransformApiHandler* transform_api_handler = new QTransformApiHandler(global_context);

	// Init style paths
	m_style_chkpt_list.append( global_context->config.style_path + "la_muse.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "rain_princess.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "scream.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "udnie.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "wave.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "wreck.ckpt" );

	bool connect_chk = connect( main_wnd, &QMainWnd::startTransformation, this, &QStyleTransformator::onTransformationStart );
	Q_ASSERT(connect_chk);
	connect_chk = connect( main_wnd, &QMainWnd::stopTransformation, this, &QStyleTransformator::onTransformationStop );
	Q_ASSERT(connect_chk);
	connect_chk = connect( transform_api_handler, &QTransformApiHandler::transformationFinished, this, &QStyleTransformator::onTransformationFinished );
	Q_ASSERT(connect_chk);

	m_main_wnd.reset( std::move(main_wnd) );
	m_transform_api_handler.reset( std::move(transform_api_handler) );
}

QStyleTransformator::~QStyleTransformator()
{
	m_main_wnd.reset(nullptr);
	m_transform_api_handler.reset(nullptr);
}

void QStyleTransformator::Start()
{
	m_main_wnd->Show();
}

void QStyleTransformator::onTransformationStart( ETransformationType transformation_type, int checkpoint, const QString& in_path )
{
	if( m_transform_api_handler->IsInProgress() ) return;

	QString checkpoint_file = m_style_chkpt_list.at(checkpoint);
	QStringList in_path_parts = in_path.split("/");
	in_path_parts.last() = in_path_parts.last().split(".").first().append("_out_") + checkpoint_file.split("/").last().split(".").first() + "." + in_path_parts.last().split(".").last();
	m_transform_api_handler->StartTransform( transformation_type, m_style_chkpt_list.at(checkpoint), in_path, in_path_parts.join("/") );
}

void QStyleTransformator::onTransformationStop( ETransformationType transformation_type )
{
	m_transform_api_handler->StopTransform();
}

void QStyleTransformator::onTransformationFinished( ETransformationType transformation_type, int exit_code, const QString& output )
{
	if( exit_code == 0 )
	{
		switch(transformation_type)
		{
		case ETransformationType::ETransformationType_Img:
			m_main_wnd->SetTransformedImage(output);
			break;

		case ETransformationType::ETransformationType_Video:
			m_main_wnd->SetTransformedVideo(output);
			break;
		}
	}
	else
	{
		QMessageBox err_msg( QMessageBox::Critical, "ERROR", "Transformation failed" );
		err_msg.setWindowIcon( QIcon(":/res/main_icon.png") );
		err_msg.setStyleSheet("QMessageBox{background-color: #252525;}\
							   QMessageBox QLabel {color: #FFFFFF;}\
							   QMessageBox QPushButton {color: #FFFFFF; background-color: #252525}\
							   QMessageBox QPushButton:hover{background-color: #1a1a1a;}");
		err_msg.exec();
	}
}
