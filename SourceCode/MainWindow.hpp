#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QProcess>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void ProcOutput();
	void ProcError();
	void ProcFinished(int, QProcess::ExitStatus);

private:
	Ui::MainWindow *ui;
	QProcess		m_proc;

};

#endif // MAINWINDOW_HPP
