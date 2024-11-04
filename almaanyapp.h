#ifndef ALMAANYAPP_H
#define ALMAANYAPP_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QStringListModel>
#include <QModelIndex>

namespace Ui {
class AlmaanyApp;
}

class AlmaanyApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlmaanyApp(QWidget *parent = nullptr);
    ~AlmaanyApp();

private:
    Ui::AlmaanyApp *ui;
    QSqlDatabase m_db;
    bool m_dbOpened;
    QStringListModel m_model;

    void init();

private slots:
    void updateSuggestions(const QString &searchKey);
    void displaySelection(const QModelIndex &keyIndex);
};

#endif // ALMAANYAPP_H
