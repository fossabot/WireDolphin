#pragma once

#include <QCloseEvent>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QSystemTrayIcon>
#include <QTreeWidgetItem>

#include "packetsource.h"
#include "statswindow.h"
#include "trayicon.h"

#define SNAP_LEN 128 * 1024 * 1024
#define PROMISC 1

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent* event) override;
    bool event(QEvent* event) override;

public:
    void initWindow();
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;
    void changeInterfaceIndex(int index) const;
    void freePackets();
    void captureInterfaceStarted(string name, string message);
    void captureInterfaceStopped(string name, string message) const;
    void resetCapture();
    void acceptPacket(int index, Packet* p) const;
    void initSlots();
    void loadOfflineFile() const;
    void tableItemClicked(const QModelIndex& index);
    void toggleStartBtn();
    void initWidgets();
    void updateCaptureStatusLabel() const;
    void initInterfaceList();
    void about();
    void activateStatsWindow() const;
    void initMenus();

private:
    Ui::MainWindow* ui;
    pcap_if_t* allDevs = nullptr;
    PacketSource* packetSource;
    vector<Packet*> packets;
    bool captureStart = false;
    QLabel* interfaceStatusLabel = new QLabel("", this);
    QLabel* captureStatusLabel = new QLabel("", this);
    chrono::time_point<chrono::steady_clock> time_start;
    QTreeWidgetItem* frame = nullptr;
    QTreeWidgetItem* datalinkTree = nullptr;
    QTreeWidgetItem* networkTree = nullptr;
    QTreeWidgetItem* transportTree = nullptr;
    QTreeWidgetItem* applicationTree = nullptr;
    QMenu* hexTableMenu = nullptr;
    TrayIcon* trayIcon = nullptr;
    StatsWindow* statsWindow = nullptr;
    QMenu* fileMenu = nullptr;
    QMenu* helpMenu = nullptr;
    QMenu* windowMenu = nullptr;
    QAction* loadFileAct = nullptr;
    QAction* aboutAct = nullptr;
    QAction* statsAct = nullptr;
    QAction* aboutQtAct = nullptr;
};
