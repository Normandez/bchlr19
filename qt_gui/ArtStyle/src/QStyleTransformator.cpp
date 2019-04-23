#include "QStyleTransformator.h"

QStyleTransformator::QStyleTransformator( const SContext* global_context, QObject* parent /*= nullptr*/ )
	: QObject(parent)
{
	QMainWnd* main_wnd = new QMainWnd(global_context);
	m_main_wnd.reset( std::move(main_wnd) );

	// Init style paths
	m_style_chkpt_list.append( global_context->config.style_path + "la_muse.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "rain_princess.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "scream.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "udnie.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "wave.ckpt" );
	m_style_chkpt_list.append( global_context->config.style_path + "wreck.ckpt" );
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
