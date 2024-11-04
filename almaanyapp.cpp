#include "almaanyapp.h"
#include "ui_almaanyapp.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QString>
#include <QStringList>
#include <QDebug>

QString dbFile = QString(SOURCE_DIR) + "/almaany.db";

AlmaanyApp::AlmaanyApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AlmaanyApp)
{
    ui->setupUi(this);
    init();

    connect(ui->searchLineEdit, &QLineEdit::textEdited, this, &AlmaanyApp::updateSuggestions);
    connect(ui->suggestionListView, &QListView::doubleClicked, this, &AlmaanyApp::displaySelection);
}

AlmaanyApp::~AlmaanyApp()
{
    delete ui;
}

void AlmaanyApp::init()
{
    // open the database
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbFile);
    m_dbOpened = m_db.open();
    if(!m_dbOpened)
        qDebug() << "data base not opened";
    // set the ListView model
    ui->suggestionListView->setModel(&m_model);
}

void AlmaanyApp::updateSuggestions(const QString &searchKey)
{
    if(!m_dbOpened)
        return;
    QStringList suggestions;
    QSqlQuery query;
    QString queryStr = "SELECT word FROM WordsTable WHERE searchword LIKE \"" + searchKey + "%\";";
    query.exec(queryStr);
    while(query.next())
    {
        suggestions << query.value("word").toString();
    }

    m_model.setStringList(suggestions);
}


void AlmaanyApp::displaySelection(const QModelIndex &keyIndex)
{
    QStringList selection;
    QString key = keyIndex.data().toString();
    QSqlQuery query;
    QString queryStr = "SELECT word, explination, meaning FROM WordsTable WHERE word=\""
                       + key + "\";";
    query.exec(queryStr);
    while(query.next())
    {
        selection << query.value(0).toString();
        selection << query.value(1).toString();
        selection << query.value(2).toString();
    }

    // display on outputTextEdit
    ui->outputTextEdit->setPlainText(selection.join('\n'));
    m_model.setStringList(QStringList {});
}
