#include "QImageViewWdgt.h"

QImageViewWdgt::QImageViewWdgt( QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_no_source_pixmap(":/res/no_source.png")
{
	m_img_placeholder = new QScrollArea();
	m_img_placeholder->setFixedSize( QSize( 632, 525 ) );
	m_img_placeholder->setBackgroundRole(QPalette::Dark);
	m_img_placeholder->setStyleSheet("border:0px");
	m_img = new QLabel();
	m_img->setScaledContents(true);
	QVBoxLayout* scrollarea_lyt = new QVBoxLayout( m_img_placeholder->viewport() );
	scrollarea_lyt->addWidget(m_img);
	scrollarea_lyt->setAlignment( m_img, Qt::AlignCenter );

	m_btn_normal_size = new QPushButton( QIcon(":/res/normal_size.png"), "" );
	m_btn_fit_to_wnd = new QPushButton( QIcon(":/res/fit_to_wnd.png"), "" );
	m_btn_zoom_in = new QPushButton( QIcon(":/res/zoom_in.png"), "" );
	m_btn_zoom_out = new QPushButton( QIcon(":/res/zoom_out.png"), "" );
	QHBoxLayout* control_btn_lyt = new QHBoxLayout();
	control_btn_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum ) );
	control_btn_lyt->addWidget(m_btn_normal_size);
	control_btn_lyt->addWidget(m_btn_fit_to_wnd);
	control_btn_lyt->addWidget(m_btn_zoom_in);
	control_btn_lyt->addWidget(m_btn_zoom_out);
	control_btn_lyt->addSpacerItem( new QSpacerItem( 20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum ) );

	QVBoxLayout* wdgt_lyt = new QVBoxLayout();
	wdgt_lyt->addWidget(m_img_placeholder);
	wdgt_lyt->addLayout(control_btn_lyt);
	this->setLayout(wdgt_lyt);

	DisableUi();
}

QImageViewWdgt::~QImageViewWdgt()
{

}

void QImageViewWdgt::DisableUi()
{
	m_img->setPixmap(m_no_source_pixmap);

	m_btn_normal_size->setEnabled(false);
	m_btn_fit_to_wnd->setEnabled(false);
	m_btn_zoom_in->setEnabled(false);
	m_btn_zoom_out->setEnabled(false);
}
