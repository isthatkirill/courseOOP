#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_dialog.h"
#include "show_data.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "Vector.h"
#include "QHeaderView"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setStyleSheet("selection-background-color:#d4ebff;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#98ccfd;}");
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    setWindowIcon(QIcon(":/images/icons/radio.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nНесохраненные изменения будут потеряны.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    ui->tableWidget->setRowCount(0);
    _vector.clear();
    filename = "";
    setWindowTitle("*" + filename + " – Характеристики радиодеталей");
}

void MainWindow::on_action_Add_triggered()
{
    Add_Dialog myDialog;
    if (myDialog.exec() == QDialog::Accepted)
    {
        Radio t = myDialog.getData();

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getType()));
        ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->setTextColor(QColor(120, 170, 255));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getNominal()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(t.getCountry()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getArt()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(t.getComment()));
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        _vector.push_back(t);
        ui->statusBar->showMessage("Запись добавлена.");
        setWindowTitle("*" + filename + " – Характеристики радиодеталей");
    }
}


void MainWindow::on_action_Exit_triggered()
{
    if (ui->tableWidget->rowCount() > 0 || filename != "") {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите выйти?\nНесохраненные изменения будут потеряны.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    exit(0);
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentCell(-1, -1);
    if (arg1 == "") {
        return;
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        ui->tableWidget->setItemSelected(item, true);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusBar->showMessage("Найдено " + QString::number(len) + " совпаден.");
}


void MainWindow::on_action_Edit_triggered()
{
    auto list = ui->tableWidget->selectedItems();

    if (list.size() > 0) {
        Add_Dialog myDialog;
        myDialog.setType(list.at(0)->text());
        myDialog.setNominal(list.at(1)->text());
        myDialog.setCountry(list.at(2)->text());
        myDialog.setArt(list.at(3)->text());
        myDialog.setComment(list.at(4)->text());

        QItemSelectionModel *selectModel = ui->tableWidget->selectionModel();
        if (selectModel->hasSelection())
           selectModel->selectedRows().first().row();

        if (myDialog.exec() == QDialog::Accepted)
        {
            Radio t = myDialog.getData();
            list.at(0)->setText(t.getType());
            list.at(1)->setText(t.getNominal());
            list.at(2)->setText(t.getCountry());
            list.at(3)->setText(t.getArt());
            list.at(4)->setText(t.getComment());
            _vector[list.at(0)->row()].setType(t.getType());
            _vector[list.at(1)->row()].setNominal(t.getNominal());
            _vector[list.at(2)->row()].setCountry(t.getCountry());
            _vector[list.at(3)->row()].setArt(t.getArt());
            _vector[list.at(4)->row()].setComment(t.getComment());

            ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

            ui->statusBar->showMessage("Запись отредактирована.");
            setWindowTitle("*" + filename + " – Характеристики радиодеталей");
        }
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}


void MainWindow::on_action_Delete_triggered()
{
    auto list = ui->tableWidget->selectionModel()->selectedRows();
    if (list.size() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить выделенную строку?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            for (auto k = list.rbegin(); k != list.rend(); ++k) {
                auto index = (*k).row();
                _vector.erase(index);
                ui->tableWidget->removeRow(index);
            }
            ui->statusBar->showMessage("Запись удалена.");
            setWindowTitle("*" + filename + " – Характеристики радиодеталей");
        }
    } else ui->statusBar->showMessage("Таблица пуста.");
}


void MainWindow::on_action_Clear_triggered()
{
    ui->tableWidget->setColumnWidth(0, 192);
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите очистить таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->tableWidget->setRowCount(0);
            _vector.clear();
            ui->statusBar->showMessage("Таблица очищена.");
            setWindowTitle("*" + filename + " – Характеристики радиодеталей");
        }
    } else ui->statusBar->showMessage("Таблица пуста.");
}


void MainWindow::on_action_Clear_triggered_open()
{
    ui->tableWidget->setRowCount(0);
    _vector.clear();
    setWindowTitle(filename + " – Характеристики радиодеталей");

}


void MainWindow::on_action_Open_triggered(bool isClean)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile()) {
        if (!isClean) {
            on_action_Clear_triggered_open();
        }
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Radio f;
                QString line = in.readLine();
                QStringList strArr = line.split(";");
                if (strArr.size() == 5) { //4
                    f.setType(strArr[0].simplified());
                    f.setNominal(strArr[1].simplified());
                    f.setCountry(strArr[2].simplified());
                    f.setArt(strArr[3].simplified());
                    f.setComment(strArr[4].simplified());
                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(f.getType()));
                    ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->setTextColor(QColor(120, 170, 255));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(f.getNominal()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(f.getCountry()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(f.getArt()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(f.getComment()));

                    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

                    _vector.push_back(f);
                }
            }
            file.close();
            ui->statusBar->showMessage("Записи из файла добавлены.");
            filename = file_name;
            setWindowTitle(filename + " – Характеристики радиодеталей");
        } else ui->statusBar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
    } else ui->statusBar->showMessage("Файл '" + file_name + "' не существует");
}


void MainWindow::on_action_Save_triggered()
{
    if (filename == "") {
        MainWindow::on_action_SaveAs_triggered();
        return;
    }
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        int len = ui->tableWidget->rowCount();
        for (int i = 0; i < len; ++i) {
            QString type = ui->tableWidget->item(i, 0)->text();
            QString name = ui->tableWidget->item(i, 1)->text();
            QString country = ui->tableWidget->item(i, 2)->text();
            QString year = ui->tableWidget->item(i, 3)->text();
            QString comment = ui->tableWidget->item(i, 4)->text();
            out << type << ";" << name << ";" << country << ";" << year << ";" << comment << "\n";
        }
        file.close();
        ui->statusBar->showMessage("Файл сохранен.");
        setWindowTitle(filename + " – Характеристики радиодеталей");
    }
}


void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    if (file_name != "") {
        filename = file_name;
        MainWindow::on_action_Save_triggered();
    }
}


void MainWindow::on_action_Merge_triggered()
{
    QString old_file = filename;
    MainWindow::on_action_Open_triggered(true);
    filename = old_file;
    ui->statusBar->showMessage("Данные объединены");
    setWindowTitle("*" + filename + " – Характеристики радиодеталей");
}


void MainWindow::on_action_ShowData_triggered()
{
    Show_Data myDialog;
    QString s;
    for (auto &k : _vector) {
        s += k.getType() + ";" + k.getNominal() + ";" + k.getCountry() + ";" + k.getArt() + ";" + k.getComment() + "\n";
    }
    myDialog.setText(s);
    myDialog.exec();
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       "Об авторе и программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Тема: Класс, характеризующий радиодетали\n"
                       "Вариант: 5\n"
                       "Автор: Емельянов Кирилл, ИКПИ-12\n"
                       "Емельянов Кирилл\n"
                       "Санкт-Петербург, 2022 год\n");
}
