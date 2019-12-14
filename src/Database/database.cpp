#include "database.h"

void Database::initialize()
{
    //If the database is open succesfully
    if(openDatabase())
        setupDefaultTables();
}

//Connect to the database
bool Database::openDatabase()
{
    //Get the database fo type sqlite3
    _db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbFilePath = Config::readValue("database/path");

    //Set the database path
    _db.setDatabaseName(dbFilePath);
    bool ok = _db.open();

    if(!ok)
    {
        qDebug() << "Can't open database!";
    }

    return ok;
}

//Close the database
void Database::closeDatabase()
{
    _db.close();
}

//Execute a query
QVector<QStringList> Database::execute(QString queryString)
{
    QSqlQuery query = _db.exec(queryString);

    //If there's been an error while executing the query
    if(_db.lastError().type() != QSqlError::NoError)
        qDebug() << "LOCALDB ERROR: " << _db.lastError();

    //Get the rows of the result of the query
    QVector<QStringList> results;

    for(int r = 0; query.next(); r++)
    {
        QStringList row;
        for(int i = 0; i < query.record().count(); i++)
        {
            row.append(query.value(i).toString());
        }
        results.append(row);
    }

    return results;
}

//Create the default tables if they don't exist
void Database::setupDefaultTables()
{
    QFile defaultTables(":DATABASE/Database/defaultTables.txt");

    if(!defaultTables.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open defaultTables.txt for the database!";
        return;
    }

    //Read every line
    QString query;
    QString line;
    while(!defaultTables.atEnd())
    {
        line = defaultTables.readLine();
        //If the readed line has no content, it's the end of the query
        if(line == "\n")
        {
            query.remove(query.length() - 1, 1);
            execute(query);
            query = "";
        }
        else
            query += line;
    }
    query.remove(query.length() - 1, 1);
    execute(query);

    defaultTables.close();
}
