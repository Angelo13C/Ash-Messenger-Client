#pragma once
#include <QtSql/QSqlDatabase>

namespace Database
{
static QSqlDatabase _db;

void initialize();
bool openDatabase();
void closeDatabase();

void setupDefaultTables();

QVector<QStringList> execute(QString queryString);
};

