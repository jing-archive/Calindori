/*
 * Copyright (C) 2019 Dimitris Kardarakos
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractListModel>
#include <KCalendarCore/Event>
#include <KCalendarCore/MemoryCalendar>
#include "localcalendar.h"

using namespace KCalendarCore;

class EventModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QDate filterdt READ filterdt WRITE setFilterdt NOTIFY filterdtChanged)
    Q_PROPERTY(LocalCalendar* calendar READ calendar WRITE setCalendar NOTIFY calendarChanged)

public:
    explicit EventModel(QObject* parent = nullptr);
    ~EventModel() override;

    enum Roles
    {
        Uid = Qt::UserRole+1,
        LastModified,
        DtStart,
        AllDay,
        Description,
        Summary,
        Location,
        Categories,
        Priority,
        Created,
        Secrecy,
        EndDate,
        Transparency,
        IsRepeating,
        RepeatPeriodType,
        RepeatEvery,
        RepeatStopAfter,
        DisplayDate,
        DisplayTime,
        IncidenceType
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QDate filterdt() const;
    void setFilterdt(const QDate & filterDate);

    LocalCalendar *calendar() const;
    void setCalendar(LocalCalendar *calendarPtr);

public Q_SLOTS:
    void loadEvents();


Q_SIGNALS:
    void filterdtChanged();
    void calendarChanged();
    void rowCountChanged();

private:
    /**
     * @return The INTERVAL of RFC 5545. It contains a positive integer representing at
      which intervals the recurrence rule repeats.
     */
    int repeatEvery(const int idx) const;

    /**
     * @return The COUNT of RFC 5545. It defines the number of occurrences at which to
      range-bound the recurrence.  The "DTSTART" property value always
      counts as the first occurrence.
     */
    int repeatStopAfter(const int idx) const;

    /**
     * return The FREQ rule part which identifies the type of recurrence rule
     */
    ushort repeatPeriodType(const int idx) const;

    Event::List m_events;
    QDate m_filterdt;
    LocalCalendar *m_calendar;
};

#endif //EVENTMODEL_H
