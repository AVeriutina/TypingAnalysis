#include "SettingsMenu.h"

#include <QAction>
#include <QMenu>

namespace NSApplication {
namespace NSInterface {
namespace NSSettingsMenuDetail {

CSettingsMenuImpl::CSettingsMenuImpl(QMenu* Menu)
    : Menu_(Menu), FingerLayoutAction_(new QAction(Menu_)),
      LocalizerInput_(
          [this](const CLocalizer& Localizer) { setLocale(Localizer); }),
      OpenFingerLayoutOutput_(false) {
  assert(Menu_);
  Menu_->addAction(FingerLayoutAction_);
  connect(FingerLayoutAction_, &QAction::triggered, this,
          &CSettingsMenuImpl::onFingerLayoutTriggered);
}

CSettingsMenuImpl::CLocalizerObserver* CSettingsMenuImpl::localizerInput() {
  return &LocalizerInput_;
}

void CSettingsMenuImpl::subscribeToOpenFingerLayout(COpenObserver* obs) {
  assert(obs);
  OpenFingerLayoutOutput_.subscribe(obs);
}

void CSettingsMenuImpl::onFingerLayoutTriggered() {
  OpenFingerLayoutOutput_.set(true);
}

void CSettingsMenuImpl::setLocale(const CLocalizer& Localizer) {
  Menu_->setTitle(Localizer.settingsMenuTitle());
  FingerLayoutAction_->setText(Localizer.windowTitle());
}

} // namespace NSSettingsMenuDetail
} // namespace NSInterface
} // namespace NSApplication
