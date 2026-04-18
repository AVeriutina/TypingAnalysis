#ifndef NSAPPLICATION_NSINTERFACE_CSETTINGSMENU_H
#define NSAPPLICATION_NSINTERFACE_CSETTINGSMENU_H

#include "Library/Observer2/Observer.h"
#include "Library/StlExtension/MvcWrappers.h"
#include "Local/Localizer.h"

#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace NSApplication {
namespace NSInterface {

namespace NSSettingsMenuDetail {

class CSettingsMenuImpl : public QObject {
  Q_OBJECT

  using CLocalizer = NSLocal::CFingerLayoutLocalizer;
  using CLocalizerObserver = NSLibrary::CObserver<CLocalizer>;
  using CLocalizerInput = NSLibrary::CHotInput<CLocalizer>;

  using COpenObservable = NSLibrary::CObservableData<bool>;
  using COpenObserver = NSLibrary::CObserver<bool>;

public:
  explicit CSettingsMenuImpl(QMenu* Menu);

  CLocalizerObserver* localizerInput();
  void subscribeToOpenFingerLayout(COpenObserver* obs);

public Q_SLOTS:
  void onFingerLayoutTriggered();

private:
  void setLocale(const CLocalizer& Localizer);

  QMenu* Menu_;
  QAction* FingerLayoutAction_;
  CLocalizerInput LocalizerInput_;
  COpenObservable OpenFingerLayoutOutput_;
};

} // namespace NSSettingsMenuDetail

using CSettingsMenu =
    NSLibrary::CViewWrapper<NSSettingsMenuDetail::CSettingsMenuImpl>;

} // namespace NSInterface
} // namespace NSApplication

#endif // NSAPPLICATION_NSINTERFACE_CSETTINGSMENU_H
