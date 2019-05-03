#ifndef QTRANSFORMAPIHANDLER_H
#define QTRANSFORMAPIHANDLER_H

#include <QObject>

#include <QProcess>

#include "SContext.h"

class QTransformApiHandler
	: public QObject
{
	Q_OBJECT

public:
	QTransformApiHandler( const SContext* global_context, QObject* parent = nullptr );
	QTransformApiHandler( const QTransformApiHandler& other ) = delete;
	QTransformApiHandler( QTransformApiHandler&& other ) = delete;
	void operator=( const QTransformApiHandler& other ) = delete;
	void operator=( QTransformApiHandler&& other ) = delete;
	~QTransformApiHandler();

	void StartTransform( ETransformationType transformation_type, const QString& checkpoint, const QString& in_path, const QString& out_path );
	void StopTransform();

	bool IsInProgress() const;

private:
	const SContext* m_context;

	QProcess m_transform_proc;
	ETransformationType m_current_transform_type;
	bool m_is_in_progress;

signals:
	void transformationFinished( ETransformationType transformation_type, int exit_status, const QString& output );

private slots:
	void onProcessFinished( int exit_code, QProcess::ExitStatus exit_status );
	void onProcessError( QProcess::ProcessError error );

};

#endif // QTRANSFORMAPIHANDLER_H
