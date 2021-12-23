#pragma once

#include <extensionsystem/iplugin.h>

#include <QAction>
#include <QMenuBar>
#include <QPointer>
#include <QSettings>

namespace MenuBarToggle::Internal {

class MenuBarTogglePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "MenuBarToggle.json")

public:
    auto initialize(const QStringList &arguments, QString *errorString) -> bool final;
    void extensionsInitialized() final;
    auto aboutToShutdown() -> ShutdownFlag final;

public:
    auto eventFilter(QObject *object, QEvent *event) -> bool final;

private:
    void loadSettings(QSettings &settings);
    void saveSettings(QSettings &settings) const;

private:
    QAction *m_action{nullptr};
    QPointer<QMenuBar> m_menuBar;
};

} // namespace MenuBarToggle::Internal
