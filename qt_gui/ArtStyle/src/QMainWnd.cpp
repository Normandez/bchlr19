#include "QMainWnd.h"
#include "ui_QMainWnd.h"

QMainWnd::QMainWnd( const SContext* context, QWidget* parent /*= nullptr*/ )
	: QMainWindow(parent),
	  ui( new Ui::QMainWnd ),
	  m_last_img_dir("."),
	  m_last_video_dir(".")
{
	ui->setupUi(this);

	this->setWindowTitle("ArtStyle");
	this->setWindowIcon( QIcon(":/res/main_icon.png") );

	InitStylesUi();

	ui->progr_bar->setVisible(false);
	ui->status_bar->showMessage("Select a style");

	bool connect_chk = connect( ui->list_wdgt_style, &QListWidget::currentRowChanged, this, &QMainWnd::onStyleChanged );
	Q_ASSERT(connect_chk);
}

QMainWnd::~QMainWnd()
{
	delete ui;
}

void QMainWnd::InitStylesUi()
{
	QListWidgetItem* itm_anime = new QListWidgetItem( QIcon(":res/anime.jpg"), "Anime Style" );
	QListWidgetItem* itm_la_muse = new QListWidgetItem( QIcon(":/res/la_muse.jpg"), "La Muse" );
	QListWidgetItem* itm_pencil = new QListWidgetItem( QIcon(":/res/pencil.jpg"), "Pencil Style" );
	QListWidgetItem* itm_rain_princess = new QListWidgetItem( QIcon(":/res/rain_princess.jpg"), "Rain Princess" );
	QListWidgetItem* itm_the_scream = new QListWidgetItem( QIcon(":/res/the_scream.jpg"), "The Scream" );
	QListWidgetItem* itm_udnie = new QListWidgetItem( QIcon(":/res/udnie.jpg"), "Udnie" );
	QListWidgetItem* itm_wave = new QListWidgetItem( QIcon(":/res/wave.jpg"), "Wave" );
	QListWidgetItem* itm_wreck = new QListWidgetItem( QIcon(":/res/the_shipwreck_of_the_minotaur.jpg"), "The Shipwreck Of The Minotaur" );

	ui->list_wdgt_style->addItem(itm_anime);
	ui->list_wdgt_style->addItem(itm_la_muse);
	ui->list_wdgt_style->addItem(itm_pencil);
	ui->list_wdgt_style->addItem(itm_rain_princess);
	ui->list_wdgt_style->addItem(itm_the_scream);
	ui->list_wdgt_style->addItem(itm_udnie);
	ui->list_wdgt_style->addItem(itm_wave);
	ui->list_wdgt_style->addItem(itm_wreck);

	ui->list_wdgt_style->setIconSize( QSize( 300, 300 ) );
}

void QMainWnd::Show()
{
	this->show();
}

void QMainWnd::SetTransformedImage( const QString& out_image_url )
{
	ui->img_wdgt_out->SetImage(out_image_url);

	ui->btn_img_out_stop_transform->setEnabled(false);
	ui->progr_bar->setVisible(false);
}

void QMainWnd::SetTransformedVideo( const QString& out_video_url )
{
	ui->video_wdgt_out->SetVideo(out_video_url);

	ui->btn_video_out_stop_transform->setEnabled(false);
	ui->progr_bar->setVisible(false);
}

void QMainWnd::onStyleChanged( int current_row )
{
	ui->status_bar->showMessage( QString("Selected style: \"%1\"").arg( ui->list_wdgt_style->currentItem()->text() ) );
}

void QMainWnd::on_btn_img_in_load_clicked()
{
	QString file_name = QFileDialog::getOpenFileName( this, "Load Image", m_last_img_dir, "Images ( *.png *.jpg *.bmp )" );
	if( !file_name.isEmpty() )
	{
		ui->img_wdgt_in->SetImage(file_name);

		int last_dir_sep_pos = file_name.lastIndexOf("/");
		int file_name_length = file_name.length();
		m_last_img_dir = file_name.remove( last_dir_sep_pos, file_name_length - last_dir_sep_pos );

		ui->btn_img_out_transform->setEnabled(true);
	}
}

void QMainWnd::on_btn_video_in_load_clicked()
{
	QString file_name = QFileDialog::getOpenFileName( this, "Load Video", m_last_video_dir, "Video ( *.mp4 )" );
	if( !file_name.isEmpty() )
	{
		ui->video_wdgt_in->SetVideo(file_name);

		int last_dir_sep_pos = file_name.lastIndexOf("/");
		int file_name_length = file_name.length();
		m_last_video_dir = file_name.remove( last_dir_sep_pos, file_name_length - last_dir_sep_pos );

		ui->btn_video_out_transform->setEnabled(true);
	}
}

void QMainWnd::on_btn_img_out_transform_clicked()
{
	int selected_style_index = ui->list_wdgt_style->currentRow();
	if( selected_style_index == -1 )
	{
		QMessageBox notice_msg( QMessageBox::Information, "INFO", "Style not selected" );
		notice_msg.setWindowIcon( QIcon(":/res/main_icon.png") );
		notice_msg.setStyleSheet("QMessageBox{background-color: #252525;}\
								  QMessageBox QLabel {color: #FFFFFF;}\
								  QMessageBox QPushButton {color: #FFFFFF; background-color: #252525}\
								  QMessageBox QPushButton:hover{background-color: #1a1a1a;}");
		notice_msg.exec();
		return;
	}

	emit startTransformation( ETransformationType::ETransformationType_Img, selected_style_index, ui->img_wdgt_in->GetImageUrl() );

	ui->btn_img_out_stop_transform->setEnabled(true);
	ui->progr_bar->setVisible(true);
}

void QMainWnd::on_btn_img_out_stop_transform_clicked()
{
	emit stopTransformation(ETransformationType::ETransformationType_Img);

	ui->btn_img_out_stop_transform->setEnabled(false);
	ui->progr_bar->setVisible(false);
}

void QMainWnd::on_btn_video_out_transform_clicked()
{
	int selected_style_index = ui->list_wdgt_style->currentRow();
	if( selected_style_index == -1 )
	{
		QMessageBox notice_msg( QMessageBox::Information, "INFO", "Style not selected" );
		notice_msg.setWindowIcon( QIcon(":/res/main_icon.png") );
		notice_msg.setStyleSheet("QMessageBox{background-color: #252525;}\
								  QMessageBox QLabel {color: #FFFFFF;}\
								  QMessageBox QPushButton {color: #FFFFFF; background-color: #252525}\
								  QMessageBox QPushButton:hover{background-color: #1a1a1a;}");
		notice_msg.exec();
		return;
	}

	emit startTransformation( ETransformationType::ETransformationType_Video, selected_style_index, ui->video_wdgt_in->GetViedoUrl() );

	ui->btn_video_out_stop_transform->setEnabled(true);
	ui->progr_bar->setVisible(true);
}

void QMainWnd::on_btn_video_out_stop_transform_clicked()
{
	emit stopTransformation(ETransformationType::ETransformationType_Video);

	ui->btn_video_out_stop_transform->setEnabled(false);
	ui->progr_bar->setVisible(false);
}

void QMainWnd::closeEvent( QCloseEvent* ev )
{
	QMessageBox exit_question_msg ( QMessageBox::Question, "EXIT", "Are you sure want to quit?" );
	exit_question_msg.setStyleSheet("QMessageBox{background-color: #252525;}\
									 QMessageBox QLabel {color: #FFFFFF;}\
									 QMessageBox QPushButton {color: #FFFFFF; background-color: #252525}\
									 QMessageBox QPushButton:hover{background-color: #1a1a1a;}");
	exit_question_msg.addButton(QMessageBox::StandardButton::Yes);
	exit_question_msg.addButton(QMessageBox::StandardButton::No);
	exit_question_msg.addButton(QMessageBox::StandardButton::Cancel);
	int res = exit_question_msg.exec();

    if ( res != QMessageBox::Yes )
	{
        ev->ignore();
    }
	else
	{
        ev->accept();
    }
}
