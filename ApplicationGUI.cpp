#include "ApplicationGUI.h"

namespace NSApplication {

CApplicationGUI::CApplicationGUI()
    : MainSeanceView_(AppWindow_.getSeanceView()),
      TextModeView_(AppWindow_.getTextModeInitData()),
      MainTextPrinter_(AppWindow_.getMainTextEdit()),
      SpeedPlotter_(AppWindow_.getSpeedPlotterParent()),
      StatisticsView_(AppWindow_.getStatisticsTable()),
      KeySchemePlotter_(AppWindow_.getKeySchemeParent()),
      FileMenu_(AppWindow_.getFileMenu()),
      ModifiersMenu_(AppWindow_.getModifiersMenuInit()),
      LanguageMenu_(AppWindow_.getLanguageMenu()),
      SettingsMenu_(AppWindow_.getSettingsMenu()) {
  // TO DO
  // should probably move this to CApplicationImpl or CApplication
  AppWindow_.show();
}

NSQt::CMainWindow* CApplicationGUI::mainWindow() {
  return &AppWindow_;
}

} // namespace NSApplication
