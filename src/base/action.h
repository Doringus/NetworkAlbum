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
    E getType() const {
        return static_cast<E>(m_Type);
    }

    template<class T>
    T getData() const {
        return qvariant_cast<T>(m_Data);
    }

private:
    int m_Type;
    QVariant m_Data;
};

