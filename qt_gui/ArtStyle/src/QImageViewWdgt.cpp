#include "QImageViewWdgt.h"

QImageViewWdgt::QImageViewWdgt( QWidget* parent /*= nullptr*/ )
	: QWidget(parent),
	  m_img_url(""),
	  m_is_adjusted(false),
	  m_no_source_pixmap(":/res/no_source.png")
{
	m_img_placeholder = new QScrollArea();
	m_img_placeholder->setFixedSize( QSize( 623, 525 ) );
	m_img_placeholder->setBackgroundRole(QPalette::Dark);
	m_img_placeholder->setStyleSheet("border:0px");
	m_img = new QLabel();
	m_img->setScaledContents(true);
	m_img_placeholder->setWidget(m_img);
	m_img_placeholder->setAlignment(Qt::AlignCenter);

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

	bool connection_chk = connect( m_btn_normal_size, &QPushButton::clicked, this, &QImageViewWdgt::onBtnNormalSizeClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_fit_to_wnd, &QPushButton::clicked, this, &QImageViewWdgt::onBtnFitToWindowClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_zoom_in, &QPushButton::clicked, this, &QImageViewWdgt::onBtnZoomInClicked );
	Q_ASSERT(connection_chk);
	connection_chk = connect( m_btn_zoom_out, &QPushButton::clicked, this, &QImageViewWdgt::onBtnZoomOutClicked );
	Q_ASSERT(connection_chk);

	DisableUi();
}

QImageViewWdgt::~QImageViewWdgt()
{
	this->disconnect();
}

void QImageViewWdgt::SetImage( const QString& img_url )
{
	m_img_url = img_url;

	if(!m_is_enable_ui)
	{
		EnableUi();
	}

	m_loaded_pixmap.load(m_img_url);
	m_img->setPixmap(m_loaded_pixmap);

	m_img_placeholder->setStyleSheet("background-color:black");

	NormalSize();
}

QString QImageViewWdgt::GetImageUrl() const
{
	return m_img_url;
}

void QImageViewWdgt::EnableUi()
{
	m_is_enable_ui = true;

	m_btn_normal_size->setEnabled(m_is_enable_ui);
	m_btn_fit_to_wnd->setEnabled(m_is_enable_ui);
	m_btn_zoom_in->setEnabled(m_is_enable_ui);
	m_btn_zoom_out->setEnabled(m_is_enable_ui);
}

void QImageViewWdgt::DisableUi()
{
	m_is_enable_ui = false;

	m_img->setPixmap(m_no_source_pixmap);
	m_img->adjustSize();

	m_btn_normal_size->setEnabled(m_is_enable_ui);
	m_btn_fit_to_wnd->setEnabled(m_is_enable_ui);
	m_btn_zoom_in->setEnabled(m_is_enable_ui);
	m_btn_zoom_out->setEnabled(m_is_enable_ui);
}

void QImageViewWdgt::NormalSize()
{
	m_img->adjustSize();
	m_is_adjusted = true;
}

void QImageViewWdgt::FitToWindow()
{
	m_img->resize( m_img_placeholder->size() );
	m_is_adjusted = false;
}

void QImageViewWdgt::ZoomIn()
{
	if(!m_is_adjusted)
	{
		NormalSize();
	}
	m_img->resize( 1.25 * m_img->size() );
}

void QImageViewWdgt::ZoomOut()
{
	if(!m_is_adjusted)
	{
		NormalSize();
	}
	m_img->resize( 0.8 * m_img->size() );
}

void QImageViewWdgt::onBtnNormalSizeClicked()
{
	NormalSize();
}

void QImageViewWdgt::onBtnFitToWindowClicked()
{
	FitToWindow();
}

void QImageViewWdgt::onBtnZoomInClicked()
{
	ZoomIn();
}

void QImageViewWdgt::onBtnZoomOutClicked()
{
	ZoomOut();
}
