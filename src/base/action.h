#pragma once

#include <type_traits>

#include <QObject>
#include <QVariant>
#include <QDebug>


/*!
 *      \brief The Action class is a template class that is flux action
 *      Action<E, QVariant> stores action type E and action data.
 *      E can be any Enum
 */
class Action final {
public:
    /*!
     * Constructs an empty action
     */
    Action() {};

    /*!
     * Constructs action with given type E and data
     */
    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    Action(E type, QVariant& data) : m_Type(static_cast<int>(type)), m_Data(data) {}

    /*!
     * Constructs action with given type E and data
     */
    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    Action(E type, QVariant&& data = QVariant()) : m_Type(static_cast<int>(type)), m_Data(std::move(data)) {}

    /*!
     *  Sets type E
     */
    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    void setType(E type) {
        m_Type = static_cast<int>(type);
    }

    /*!
     * Sets data
     */
    void setData(QVariant& data) {
        m_Data = data;
    }

    /*!
     * Sets data
     */
    void setData(const QVariant& data) {
        m_Data = data;
    }

    /*!
     * Returns action type casted to E
     */
    template<class E, class = typename std::enable_if<std::is_enum<E>::value>::type>
    E getType() const {
        return static_cast<E>(m_Type);
    }

    /*!
     * Returns action data casted to T
     */
    template<class T>
    T getData() const {
        return qvariant_cast<T>(m_Data);
    }


    /*!
     * Sets action error marker
     */
    void setError(bool error) {
        m_HasError = error;
    }

    /*!
     * Sets action error string
     */
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

