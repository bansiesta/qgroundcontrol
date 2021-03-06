/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009 - 2011 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

#ifndef QGCTOOLBAR_H
#define QGCTOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QComboBox>
#include <QTimer>
#include "UASInterface.h"
#include "SerialLink.h"

class QGCToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit QGCToolBar(QWidget* parent = 0);
    void setPerspectiveChangeActions(const QList<QAction*> &action);
    void setPerspectiveChangeAdvancedActions(const QList<QAction*> &action);
    ~QGCToolBar();

public slots:
    /** @brief Set the system that is currently displayed by this widget */
    void setActiveUAS(UASInterface* active);
    /** @brief Set the link which is currently handled with connecting / disconnecting */
    void addLink(LinkInterface* link);
    /** @brief Remove link which is currently handled */
    void removeLink(LinkInterface* link);
    /** @brief Set the system state */
    void updateState(UASInterface* system, QString name, QString description);
    /** @brief Set the system mode */
    void updateMode(int system, QString name, QString description);
    /** @brief Update the system name */
    void updateName(const QString& name);
    /** @brief Set the MAV system type */
    void setSystemType(UASInterface* uas, unsigned int systemType);
    /** @brief Received system text message */
    void receiveTextMessage(int uasid, int componentid, int severity, QString text);
    /** @brief Update battery charge state */
    void updateBatteryRemaining(UASInterface* uas, double voltage, double current, double percent, int seconds);
    /** @brief Update current waypoint */
    void updateCurrentWaypoint(quint16 id);
    /** @brief Update distance to current waypoint */
    void updateWaypointDistance(double distance);
    /** @brief Update arming state */
    void updateArmingState(bool armed);
    /** @brief Repaint widgets */
    void updateView();
    /** @brief Update connection timeout time */
    void heartbeatTimeout(bool timeout, unsigned int ms);
    /** @brief Update global position */
    void globalPositionChanged(UASInterface* uas, double lat, double lon, double altAMSL, double altWGS84, quint64 usec);
    /** @brief Create or connect link */
    void connectLink(bool connect);
    /** @brief Clear status string */
    void clearStatusString();
    /** @brief Set an activity action as checked in menu */
    void advancedActivityTriggered(QAction* action);
    void updateComboBox();

    /**
     * @brief User selected baud rate
     * @param index The current index of the combo box
     */
    void baudSelected(int index);

    /**
     * @brief User selected port
     * @param index The current index of the combo box
     */
    void portSelected(int index);

protected:
    void storeSettings();
    void loadSettings();
    void createUI();
    void resetToolbarUI();
    UASInterface* mav;
    QLabel* symbolLabel;
    QLabel* toolBarNameLabel;
    QLabel* toolBarTimeoutLabel;
    QAction* toolBarTimeoutAction; ///< Needed to set label (in)visible.
    QAction* toolBarMessageAction;
    QAction* toolBarPortAction;
    QAction* toolBarBaudAction;
    QAction* toolBarWpAction;
    QAction* toolBarBatteryBarAction;
    QAction* toolBarBatteryVoltageAction;
    QLabel* toolBarSafetyLabel;
    QLabel* toolBarModeLabel;
    QLabel* toolBarStateLabel;
    QLabel* toolBarWpLabel;
    QLabel* toolBarMessageLabel;
    QPushButton* connectButton;
    QProgressBar* toolBarBatteryBar;
    QLabel* toolBarBatteryVoltageLabel;

    QComboBox *portComboBox;
    QComboBox *baudcomboBox;
    QTimer portBoxTimer;
    bool userBaudChoice;
    bool userPortChoice;
    bool changed;
    float batteryPercent;
    float batteryVoltage;
    int wpId;
    double wpDistance;
    float altitudeMSL;
    float altitudeRel;
    QString state;
    QString mode;
    QString systemName;
    QString lastSystemMessage;
    quint64 lastSystemMessageTimeMs;
    QTimer updateViewTimer;
    bool systemArmed;
    LinkInterface* currentLink;
    QAction* firstAction;
    QToolButton *advancedButton;
    QButtonGroup *group;
    
private slots:
    void _linkConnected(void);
    void _linkDisconnected(void);
    
private:
    /** @brief Update the link state */
    void _updateLinkState(bool connected);
};

#endif // QGCTOOLBAR_H
