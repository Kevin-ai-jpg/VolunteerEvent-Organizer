#include "JSONEventRepository.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

JSONEventRepository::JSONEventRepository(const QString& filename)
    : m_filename(filename) {
    load();
}

void JSONEventRepository::load() {
    m_events.clear();
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open event file for reading:" << m_filename;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    QJsonArray arr = doc.array();
    for (const QJsonValue& val : arr) {
        QJsonObject obj = val.toObject();
        int id = obj["id"].toInt();
        QString title = obj["title"].toString();
        QDate date = QDate::fromString(obj["date"].toString(), Qt::ISODate);
        QString location = obj["location"].toString();

        Event e(id, title, date, location);

        QJsonArray volunteers = obj["volunteerIds"].toArray();
        for (const QJsonValue& v : volunteers) {
            e.addVolunteer(v.toInt());
        }
        m_events.push_back(e);
    }
    qDebug() << "Loaded" << m_events.size() << "events from" << m_filename;
}

void JSONEventRepository::save() const {
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Could not open event file for writing:" << m_filename;
        return;
    }

    QJsonArray arr;
    for (const auto& e : m_events) {
        QJsonObject obj;
        obj["id"] = e.getId();
        obj["title"] = e.getTitle();
        obj["date"] = e.getDate().toString(Qt::ISODate);
        obj["location"] = e.getLocation();

        QJsonArray volunteerIds;
        for (int vId : e.getVolunteerIds()) {
            volunteerIds.append(vId);
        }
        obj["volunteerIds"] = volunteerIds;

        arr.append(obj);
    }

    QJsonDocument doc(arr);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    qDebug() << "Saved" << m_events.size() << "events to" << m_filename;
}

void JSONEventRepository::add(const Event& event) {
    for (const auto& e : m_events) {
        if (e.getId() == event.getId()) {
            qWarning() << "Event with ID" << event.getId() << "already exists. Cannot add.";
            return;
        }
    }
    m_events.push_back(event);
    save();
    qDebug() << "Event added:" << event.getTitle();
}

void JSONEventRepository::remove(int id) {
    auto it = std::remove_if(m_events.begin(), m_events.end(),
                             [id](const Event& e) { return e.getId() == id; });
    if (it != m_events.end()) {
        m_events.erase(it, m_events.end());
        save();
        qDebug() << "Event with ID" << id << "removed.";
    } else {
        qWarning() << "Event with ID" << id << "not found for removal.";
    }
}

void JSONEventRepository::update(const Event& event) {
    for (auto& e : m_events) {
        if (e.getId() == event.getId()) {
            e = event;
            save();
            qDebug() << "Event with ID" << event.getId() << "updated.";
            return;
        }
    }
    qWarning() << "Event with ID" << event.getId() << "not found for update.";
}

std::vector<Event> JSONEventRepository::getAll() const {
    return m_events;
}