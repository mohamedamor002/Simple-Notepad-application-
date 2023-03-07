#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QPrintDialog>
#include <QPrinter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
file_path = ""   ;
ui->textEdit->setText("") ;
}

void MainWindow::on_actionOpen_triggered()
{
QString file_name   =  QFileDialog::getOpenFileName(this,"Open this file ") ;
QFile   file(file_name) ;
file_path= file_name ;
if(!file.open(QFile::ReadOnly | QFile::Text))
{
    QMessageBox ::warning(this,"..","file not open\n")  ;
    return  ;
}
QTextStream  in(&file)  ;
QString  text =  in.readAll()  ;
ui->textEdit->setText(text)  ;
file.close() ;
 }

void MainWindow::on_actionSave_triggered()
{
    QFile   file(file_path) ;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox ::warning(this,"..","file not open\n")  ;
        return  ;
    }
    QTextStream  out(&file)  ;
    QString  text =  ui->textEdit->toPlainText()   ;
    out << text  ;
    file.flush()  ;
    file.close() ;
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_name   =  QFileDialog::getSaveFileName(this,"Open this file ") ;
    QFile   file(file_name) ;
    file_path=file_name ;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox ::warning(this,"..","file not open\n")  ;
        return  ;
    }
    QTextStream  out(&file)  ;
    QString  text =  ui->textEdit->toPlainText()   ;
    out << text  ;
    file.flush()  ;
    file.close() ;

}

void MainWindow::on_actionCut_triggered()
{
ui->textEdit->cut() ;
}

void MainWindow::on_actionCopy_triggered()
{
ui->textEdit->copy() ;
}

void MainWindow::on_actionPaste_triggered()
{
ui->textEdit->paste() ;
}

void MainWindow::on_actionRedo_triggered()
{
ui->textEdit->redo() ;
}

void MainWindow::on_actionUndo_triggered()
{ui->textEdit->undo() ;

}

void MainWindow::on_actionAbout_notepad_triggered()
{ QString  about_text   ;
    about_text= "Author: Mohamed Amor\n" ;
    about_text+= "Date : 07/03/2023\n"  ;
    about_text+="(C) Notepas Appilcation(R)\n"  ;

QMessageBox :: about( this,"About Notepad",about_text)  ;
}

void MainWindow::on_actionFont_triggered()
{
    bool ok ;
    QFont font = QFontDialog::getFont(&ok,this) ;
    if(ok)
    {
        ui->textEdit->setFont(font) ;
    }
    else

   return  ;
}

void MainWindow::on_actionColor_triggered()
{
 QColor  color = QColorDialog::getColor(Qt::white,this,"Choose Color")  ;
if(color.isValid())
{
    ui->textEdit->setTextColor(color) ;
}
}

void MainWindow::on_actionBackground_Color_triggered()
{
    QColor  color = QColorDialog::getColor(Qt::white,this,"Choose Color")  ;
   if(color.isValid())
   {
      ui->textEdit->setTextBackgroundColor(color) ;

   }

}

void MainWindow::on_actionBackgounrd_window_triggered()
{ QColor  color = QColorDialog::getColor(Qt::white,this,"Choose Color")  ;
    if(color.isValid())
    ui->textEdit->setPalette(  QPalette (color)) ;

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer ;
    printer.setPrinterName("desired printer name\n")  ;
    QPrintDialog dialog(&printer,this);
    if(dialog.exec() == QDialog::Rejected) return  ;
    ui->textEdit->print(&printer) ;

}
