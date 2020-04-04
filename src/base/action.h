#pragma once

#include <type_traits>

#include <QObject>
#include <QVariant>
#include <QDebug>

class Action final {
public:
    Action() {};

    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    Action(E type, QVariant& data) : m_Type(static_cast<int>(type)), m_Data(data) {}

    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    Action(E type, QVariant&& data = QVariant()) : m_Type(static_cast<int>(type)), m_Data(std::move(data)) {}

    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    void setType(E type) {
        m_Type = static_cast<int>(type);
    }

    void setData(QVariant& data) {
        m_Data = data;
    }

    void setData(const QVariant& data) {
        m_Data = data;
    }

    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    E getType() const {
        return static_cast<E>(m_Type);
    }

    template<class T>
    T getData() const {
        return qvariant_cast<T>(m_Data);
    }

    void setError(bool error) {
        m_HasError = error;
    }

    void setErrorString(QString errorString) {
        m_ErrorString = errorString;
        if(!m_ErrorString.isEmpty()) {
            setError(true);
        }
    }

    bool hasError() const {
        return m_HasError;
    }

    QString getErrorString() const {
        return m_ErrorString;
    }

private:
    int m_Type;
    QVariant m_Data;
    bool m_HasError = false;
    QString m_ErrorString;
};

