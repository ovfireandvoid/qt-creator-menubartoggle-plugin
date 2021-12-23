#pragma once

#include <QtGlobal>

namespace MenuBarToggle::Constants {

constexpr auto ACTION_ID = "MenuBarToggle.Action";
constexpr auto ACTION_KEY_SEQUENCE = QT_TRANSLATE_NOOP("MenuBarToggle", "Alt+M");
constexpr auto ACTION_TEXT = QT_TRANSLATE_NOOP("MenuBarToggle", "Show Menu Bar");

constexpr auto SETTINGS_GROUP = "MenuBarTogglePlugin";
constexpr auto SETTINGS_MENUBAR_VISIBLE = "menuBarVisible";

} // namespace MenuBarToggle::Constants

