
#include "serverfunction.h"

QByteArray parse(QByteArray request) {
    // {"method": "register", "login": "qwer", "password": "pass", "email": "email"}
    // {"method": "authentication", "login": "qwer", "password": "pass"}
    // {"method": "getTask", "taskType": 1}
    // {"method": "checkTask", "taskId": 3, "answer": 1.0}
    // {"method": "getAllStat", "token": "10f6dc4fedbc5bedd4f6beff3171930d"}
    QJsonObject json_request = QJsonDocument::fromJson(request).object();
    qDebug() << json_request;
    QString response;
    QString method = json_request["method"].toString();
    if (method == QString("authentication")) {
        response = auth(json_request);
    }
    else if (method == QString("register")) {
        response = reg(json_request);
    }
    else if (method == QString("getTask")) {
        response = getTask(json_request);
    }
    else if (method == QString("checkTask")) {
        response = checkTask(json_request);
    }
    else if (method == QString("getUserStat")) {
        response = getUserStat(json_request);
    }
    else if (method == QString("getAllStat")) {
        response = getAllStat(json_request);
    }
    else {
        QVariantMap error_response;
        error_response["error"] = QString("Function is not defined");
        response = QJsonDocument::fromVariant(error_response).toJson(QJsonDocument::Compact);
    }
    return QByteArray((response + "\r\n").toUtf8());
}

QByteArray auth(QJsonObject request) {
    QVariantMap response;
    QString login = request["login"].toString();
    QString input_password = request["password"].toString();
    QString query = QString("SELECT * FROM Users WHERE login = \"%1\"").arg(login);
    QSqlQuery queryResult = Database::getInstance()->doSQLQuery(query);
    QSqlRecord record = queryResult.record();
    queryResult.first();
    QVariant dbPassword = queryResult.value(record.indexOf("password"));
    if (dbPassword == QVariant::Invalid) {
        response["status"] = "fail";
    }
    else if (dbPassword.toString() == input_password) {
        QString token = queryResult.value(record.indexOf("token")).toString();
        response["status"] = "success";
        response["token"] = token;
    }
    else {
        response["status"] = "fail";
    }

    qDebug() << QString("Autherisation with login %1 and password %2").arg(login, input_password);
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

QByteArray reg(QJsonObject request) {
    QVariantMap response;
    QString login = request["login"].toString();
    QString password = request["password"].toString();
    QString email = request["email"].toString();
    QString token = QString(QCryptographicHash::hash(((login+password).toUtf8()), QCryptographicHash::Sha3_256).toHex());
    QString query = QString("INSERT INTO Users(login, password, token, email) "
                            "VALUES (\"%1\", \"%2\", \"%3\", \"%4\")")
                        .arg(login, password, token, email);
    Database::getInstance()->doSQLQuery(query);
    response["token"] = token;
    response["status"] = "success";
    //response["isTeacher"] = false;
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

QByteArray getAllStat(QJsonObject request) {
    QVariantMap response;
    QString query = QString("SELECT Users.login, Tasks.type, COUNT(*) AS solved_tasks "
                            "FROM Users "
                            "JOIN UsersTasks ON Users.userID = UsersTasks.userID "
                            "JOIN Tasks ON Tasks.taskID = UsersTasks.taskID "
                            "GROUP BY Users.login, Tasks.type"
                            );
    QSqlQuery stat = Database::getInstance()->doSQLQuery(query);
    QMap<QString, QJsonObject> recordsMap;
    while(stat.next()) {
        QString login = stat.value("login").toString();
        int type = stat.value("type").toInt();
        int solved_tasks = stat.value("solved_tasks").toInt();

        if (!recordsMap.contains(login)) {
            QJsonObject recordObject;
            recordObject.insert("login", login);
            recordObject.insert("solved_tasks", QJsonObject());
            recordsMap.insert(login, recordObject);
        }

        QJsonObject recordObject = recordsMap.value(login);
        QJsonObject solvedTasksObject = recordObject["solved_tasks"].toObject();
        solvedTasksObject.insert(QString::number(type), solved_tasks);
        recordObject["solved_tasks"] = solvedTasksObject;
        recordsMap[login] = recordObject;
    }
    QJsonArray recordsArray;
    for (const QJsonObject &recordObject : recordsMap.values()) {
        recordsArray.push_back(recordObject);
    }
    response["status"] = "success";
    response["result"] = recordsArray;
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

QByteArray getUserStat(QJsonObject request) {
    QVariantMap response;
    QString userToken = request["token"].toString();
    QString query = QString("SELECT Tasks.type, COUNT(*) AS solved_tasks "
                            "FROM UsersTasks "
                            "JOIN Tasks ON Tasks.taskID = UsersTasks.taskID "
                            "WHERE UsersTasks.userID = (SELECT userID FROM Users WHERE token = \"%1\") "
                            "GROUP BY Tasks.type")
                        .arg(userToken);
    QSqlQuery stat = Database::getInstance()->doSQLQuery(query);
    QJsonArray recordsArray;
    while(stat.next()) {
        QJsonObject recordObject;
        for (int x = 0; x < stat.record().count(); x++) {
            recordObject.insert(stat.record().fieldName(x), QJsonValue::fromVariant(stat.value(x)));
        }
        recordsArray.push_back(recordObject);
    }
    response["status"] = "success";
    response["result"] = recordsArray;
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

QByteArray getTask(QJsonObject request) {
    QVariantMap response;
    QVariantMap task;
    int taskType = request["taskType"].toInt();
    if(taskType == 1)
    {
        task = get_result();
    }
    else if(taskType == 2)
    {
        task = Findtheminimumpoint();
    }
    else if(taskType == 3)
    {
        task = result_Vigenere();
    }
    else if(taskType == 4)
    {
        task = token_sha_256();
    }
    else
    {
        response["status"] = "fail";
        return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
    }
    QString taskText = task["text"].toString();
    QString taskAnswer = task["answer"].toString();
    QString query = QString("INSERT INTO Tasks(text, answer, type) "
                            "VALUES (\"%1\", \"%2\", %3)")
                        .arg(taskText).arg(taskAnswer).arg(taskType);
    QSqlQuery queryResult = Database::getInstance()->doSQLQuery(query);
    response["status"] = "success";
    response["taskId"] = queryResult.lastInsertId().toInt();
    response["taskText"] = taskText;
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}

QByteArray checkTask(QJsonObject request) {
    QVariantMap response;
    QString userToken = request["token"].toString();
    int taskId = request["taskId"].toInt();
    QString answer = request["answer"].toString();
    QString query = QString("SELECT * FROM Tasks WHERE taskId = %1").arg(taskId);
    QSqlQuery queryResult = Database::getInstance()->doSQLQuery(query);
    QSqlRecord record = queryResult.record();
    queryResult.next();
    QString correctAnswer = queryResult.value(record.indexOf("answer")).toString();
    if (answer == correctAnswer) {
        response["status"] = "success";
        QString query = QString("INSERT INTO UsersTasks(userID, taskid) "
                                "SELECT userID, %1 FROM Users WHERE token == \"%2\"")
                            .arg(taskId).arg(userToken);
        Database::getInstance()->doSQLQuery(query);
    }
    else {
        response["status"] = "fail";
    }
    return QJsonDocument::fromVariant(response).toJson(QJsonDocument::Compact);
}
