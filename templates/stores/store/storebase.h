{% set class = '{0}StoreBase'.format(interface) %}

#pragma once

#include <QtCore>
#include "action.h"
#include "{{interface|lower}}state.h"


class {{class}} : public QObject
{
    Q_OBJECT
    Q_PROPERTY({{interface}}State state READ state NOTIFY stateChanged)
{% for property in interface.properties %}
    Q_PROPERTY({{property|returnType}} {{property}} READ {{property}} NOTIFY stateChanged)
{% endfor %}
public:
    {{class}}(QObject *parent = nullptr);
    virtual ~{{class}}();
    enum ActionType {
{% for operation in interface.operations %}
{% if loop.last %}
        {{operation|upperfirst}}
{% else %}
        {{operation|upperfirst}},
{% endif %}
{% endfor %}
    };
public:
{% for property in interface.properties %}
    {{property|returnType}} {{property}}() const;
{% endfor %}
{% for operation in interface.operations %}
    Q_INVOKABLE {{operation|returnType}} {{operation}}({{operation|parameters}});
{% endfor %}
    {{interface}}State state() const;
    void dispatch(const Action& action);
    virtual {{interface}}State reduce(const Action& action, const {{interface}}State& state);
Q_SIGNALS:
    void stateChanged(const {{interface}}State& state);
private:
    {{interface}}State m_state;
public:
{% for operation in interface.operations %}
    static const QByteArray {{operation|upper}};
{% endfor %}
};
