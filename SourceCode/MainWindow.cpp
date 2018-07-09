#include <QDebug>
#include <QMessageBox>

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

///
/// \brief コンストラクタ
///
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_proc(this)
{
	ui->setupUi(this);

	// スロット設定
	connect(&m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(ProcOutput()));
	connect(&m_proc, SIGNAL(readyReadStandardError()), this, SLOT(ProcError()));
	connect(&m_proc, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(ProcFinished(int,QProcess::ExitStatus)));

	// pythonを別プロセスで実行
	QString pythonCodePath = "C:/QtTestPython01/python/test1.py";	// 注：自分の環境に合わせて書き換える
	QStringList args;
	args << pythonCodePath;
	m_proc.start("python", args);
}

///
/// \brief デストラクタ
///
MainWindow::~MainWindow()
{
	delete ui;
}

///
/// \brief 標準出力を取り出して文字列にしてUIにセット
///
void MainWindow::ProcOutput()
{
	QByteArray output = m_proc.readAllStandardOutput();
	QString str = QString::fromLocal8Bit(output);

	ui->label->setText(str);
}

///
/// \brief 標準エラー出力を取り出して文字列にしてUIにセット
///
void MainWindow::ProcError()
{
	QByteArray output = m_proc.readAllStandardError();
	QString str = QString::fromLocal8Bit(output);

	ui->label->setText(str);
}

///
/// \brief プロセス終了時
/// \param exitCode
/// \param exitStatus
///
void MainWindow::ProcFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	if( exitStatus == QProcess::CrashExit )
	{
		QMessageBox::warning(this, "Error", "Crashed");
	}
	else if( exitCode != 0 )
	{
		QMessageBox::warning(this, "Error", "Failed");
	}
	else
	{
		// 成功時の処理はここに入れる
	}
}

