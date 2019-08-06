#ifndef ZEBRA_SQL_H
#define ZEBRA_SQL_H
#include <QtSql>
#include "zebra_datapacket.h"

#define ZEBRA_DB_KEY "zebra_key"

struct sZebraSqlItem{
    sZebraSqlItem():id(-1){}

    int id;
    QString node_id;
    QString public_key;
    QString private_key;
};


class Zebra_Sql
{
    Zebra_Sql();
public:
    static Zebra_Sql *bulid();

    bool updateItem(sZebraSqlItem &item);
    int countById(const QString &id) {return count("id", QString(" where node_id = %1").arg(id));}
    sZebraSqlItem findById(const QString &id){ return findItemById(id).first(); }
    void removeById(const QString &id) { remove(QString("node_id = %1").arg(id)); }

protected:
    void createTable();
    bool insertItem(sZebraSqlItem &item);
    void remove(const QString &condition);
    bool modifyItem(const sZebraSqlItem &item, const QString &cmd);
    void selectItem(QSqlQuery &query, sZebraSqlItem &item);
    void throwError(const QSqlError &err) ;
    int count(const QString &column_name, const QString &condition);
    QVector<sZebraSqlItem> selectItems(const QString &condition);
    QVector<sZebraSqlItem> findItemById(const QString &id){ return selectItems(QString("where node_id = %1").arg(id));}
    bool updateColumn(const QString& column_name, const QString& value, const QString &condition);
    QString tableName(){return QString("%1").arg(ZEBRA_DB_KEY);}
};

#endif // ZEBRA_SQL_H
