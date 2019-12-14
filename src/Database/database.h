#pragma once
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QFile>

#include "src/Other/config.h"

namespace Database
{
static QSqlDatabase _db;

void initialize();
bool openDatabase();
void closeDatabase();

void setupDefaultTables();

QVector<QStringList> execute(QString queryString);
};

