#ifndef QSTYLETRANSFORMATOR_H
#define QSTYLETRANSFORMATOR_H

#include <memory>
#include <QObject>

#include "SContext.h"
#include "QMainWnd.h"
#include "QTransformApiHandler.h"

class QStyleTransformator
	: public QObject
{
	Q_OBJECT

public:
	explicit QStyleTransformator( const SContext* global_context, QObject* parent = nullptr );
	QStyleTransformator( const QStyleTransformator& other ) = delete;
	QStyleTransformator( QStyleTransformator&& other ) = delete;
	void operator=( const QStyleTransformator& other ) = delete;
	void operator=( QStyleTransformator&& other ) = delete;
	~QStyleTransformator();

	void Start();

private:
	std::unique_ptr<QMainWnd> m_main_wnd;
	std::unique_ptr<QTransformApiHandler> m_transform_api_handler;

	QStringList m_style_chkpt_list;

};

#endif // QSTYLETRANSFORMATOR_H
