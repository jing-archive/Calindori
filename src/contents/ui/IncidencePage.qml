/*
 *   Copyright 2020 Dimitris Kardarakos <dimkard@posteo.net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.7
import org.kde.kirigami 2.4 as Kirigami

Kirigami.Page {
    id: root

    property var incidence
    property var calendar

    title: incidence.summary

    Loader {
        anchors.fill: parent
        sourceComponent: incidence.type == 0 ? eventCard : todoCard
    }

    Component {
        id: eventCard

        EventCard {
            dataModel: root.incidence
        }
    }

    Component {
        id: todoCard

        TodoCard {
            dataModel: root.incidence
        }
    }
}
