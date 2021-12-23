#include "menubartoggle_plugin.h"
#include "menubartoggle_constants.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <QMenu>

namespace MenuBarToggle::Internal {

auto MenuBarTogglePlugin::initialize(const QStringList &arguments, QString *errorString) -> bool
{
    Q_UNUSED(arguments)

    auto menuBar = Core::ActionManager::actionContainer(Core::Constants::MENU_BAR)->menuBar();

    if (menuBar == nullptr) {
        if (errorString != nullptr) {
            *errorString = tr("Qt Creator's menu bar not found");
        }
        return false;
    }

    if (menuBar->isNativeMenuBar()) {
        // NO-OP with native menu bar, e.g. on MacOS or Ubuntu Unity
        return true;
    }

    auto viewMenu = Core::ActionManager::actionContainer(Core::Constants::M_VIEW);

    if (viewMenu == nullptr) {
        if (errorString != nullptr) {
            *errorString = tr("Qt Creator's View menu not found");
        }
        return false;
    }

    m_menuBar = menuBar;
    m_menuBar->installEventFilter(this);

    m_action = new QAction(tr(Constants::ACTION_TEXT), this);
    m_action->setCheckable(true);
    m_action->setChecked(true);

    connect(m_action, &QAction::toggled, m_menuBar, &QMenuBar::setVisible);

    auto cmd = Core::ActionManager::registerAction(m_action,
                                                   Constants::ACTION_ID,
                                                   Core::Context{Core::Constants::C_GLOBAL});
    cmd->setAttribute(Core::Command::CA_UpdateText);
    cmd->setDefaultKeySequence(QKeySequence(tr(Constants::ACTION_KEY_SEQUENCE)));

    viewMenu->addAction(cmd);

    connect(Core::ICore::instance(), &Core::ICore::coreAboutToOpen, this, [this] {
        loadSettings(*Core::ICore::settings());
    });
    connect(Core::ICore::instance(), &Core::ICore::coreAboutToClose, this, [this] {
        saveSettings(*Core::ICore::settings());
    });

    return true;
}

void MenuBarTogglePlugin::extensionsInitialized() {}

auto MenuBarTogglePlugin::aboutToShutdown() -> ShutdownFlag
{
    return SynchronousShutdown;
}

auto MenuBarTogglePlugin::eventFilter(QObject *object, QEvent *event) -> bool
{
    if (object == m_menuBar) {
        switch (event->type()) {
        case QEvent::ShowToParent:
            m_action->setChecked(true);
            break;
        case QEvent::HideToParent:
            m_action->setChecked(false);
            break;
        default:
            break;
        }
    }

    return ExtensionSystem::IPlugin::eventFilter(object, event);
}

void MenuBarTogglePlugin::loadSettings(QSettings &settings)
{
    if (m_menuBar == nullptr) {
        return;
    }

    settings.beginGroup(QLatin1String{Constants::SETTINGS_GROUP});
    m_menuBar->setVisible(
        settings.value(QLatin1String{Constants::SETTINGS_MENUBAR_VISIBLE}, true).toBool());
    settings.endGroup();
}

void MenuBarTogglePlugin::saveSettings(QSettings &settings) const
{
    if (m_menuBar == nullptr) {
        return;
    }

    settings.beginGroup(QLatin1String{Constants::SETTINGS_GROUP});
    settings.setValue(QLatin1String{Constants::SETTINGS_MENUBAR_VISIBLE}, m_menuBar->isVisible());
    settings.endGroup();
}

} // namespace MenuBarToggle::Internal
