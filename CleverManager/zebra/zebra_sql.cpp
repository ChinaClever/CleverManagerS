/*
 *
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "zebra_sql.h"

Zebra_Sql::Zebra_Sql()
{
    createTable();
}

Zebra_Sql *Zebra_Sql::bulid()
{
    static Zebra_Sql* sington = nullptr;
    if(sington == nullptr)
        sington = new Zebra_Sql();
    return sington;
}


int Zebra_Sql::count(const QString &column_name, const QString &condition)
{
    int count = -1;
    QSqlQuery query;
    if(query.exec(QString("select count(DISTINCT %1) from %2 %3").arg(column_name).arg(tableName()).arg(condition))){
        if(query.next())
            count = query.value(0).toInt();
    } else
        qDebug()<< "sqlcom count:" << query.lastError();
    return count;
}

void Zebra_Sql::remove(const QString &condition)
{
    QSqlQuery query;
    if(!query.exec(QString("DELETE FROM %1 WHERE %2").arg(tableName()).arg(condition))) {
        qDebug()<< "remove:" << query.lastError();
        throwError(query.lastError());
    }
}

void Zebra_Sql::throwError(const QSqlError &err)
{
    qCritical() << "Sql_Error:" << err.text() << err.type();
}

QVector<sZebraSqlItem> Zebra_Sql::selectItems(const QString &condition)
{
    QVector<sZebraSqlItem> items;
    QSqlQuery query;
    QString sqlcom = QString("SELECT * from %1 %2").arg(tableName()).arg(condition);
    query.prepare(sqlcom);
    if(query.exec()){
        sZebraSqlItem item;
        while(query.next()){
            selectItem(query,item);
            items.append(item);
        }
    } else {
        qDebug()<<" "<<query.lastError().databaseText();
        qDebug()<<" "<<query.lastError().driverText();
        qDebug()<<sqlcom;
        throwError(query.lastError());
    }
    return items;
}



void Zebra_Sql::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "node_id        VCHAR,"
            "public_key     VCHAR,"
            "private_key     VCHAR);";
    QSqlQuery query;
    if(!query.exec(cmd.arg(tableName()))) {
        throwError(query.lastError());
    }
}

bool Zebra_Sql::insertItem(sZebraSqlItem &item)
{
    QString cmd = "insert into %1 (node_id, public_key, private_key) "
                  "values(:node_id,:public_key,:private_key)";
    return modifyItem(item,cmd.arg(tableName()));
}

bool Zebra_Sql::updateItem(sZebraSqlItem &item)
{
    QString id = item.node_id;
    int rtn = countById(id);
    if(rtn>0) {
        QString cmd = QString(" where node_id = %1").arg(id);
        sZebraSqlItem key = findById(id);
        if(key.public_key != item.public_key) {
             updateColumn("public_key", item.public_key, cmd);
        }
        if(key.private_key != item.private_key) {
             updateColumn("private_key", item.private_key, cmd);
        }
    } else {
        insertItem(item);
    }

    return true;
}

bool Zebra_Sql::updateColumn(const QString& column_name, const QString& value, const QString &condition)
{
    bool ret = false;
    QSqlQuery query;
    ret = query.exec(QString("update  %1 set %2=\"%3\" %4").arg(tableName()).arg(column_name).arg(value).arg(condition));
    if(!ret)
        qDebug()<< "sqlcom updateColumn 2:" << query.lastError();
    return ret;
}


bool Zebra_Sql::modifyItem(const sZebraSqlItem &item, const QString &cmd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare(cmd);
    query.bindValue(":node_id",item.node_id);
    query.bindValue(":public_key",item.public_key);
    query.bindValue(":private_key",item.private_key);
    ret = query.exec();
    if(!ret) throwError(query.lastError());
    return ret;
}

void Zebra_Sql::selectItem(QSqlQuery &query, sZebraSqlItem &item)
{
    item.id = query.value("id").toInt();
    item.node_id = query.value("node_id").toString();
    item.public_key = query.value("public_key").toString();
    item.private_key = query.value("private_key").toString();
}
