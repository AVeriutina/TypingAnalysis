#pragma once

#include <QColor>
#include <QString>

namespace NSApplication {
namespace NSFingers {
namespace NSViewDetails {

struct CButtonStyle {
  QColor background;
  QColor border = QColor(136, 136, 136);
  int borderWidth = 1;
  int borderRadius = 4;
  int fontSize = 16;
  bool bold = false;
  QColor textColor = QColor(40, 40, 40);

  QString toStyleSheet() const {
    return QString("QPushButton {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: %3px solid %4;"
                   "  border-radius: %5px;"
                   "  font-size: %6px;"
                   "  font-weight: %7;"
                   "}"
                   "QPushButton:hover   { background-color: %8; }"
                   "QPushButton:pressed { background-color: %9; }")
        .arg(background.name())
        .arg(textColor.name())
        .arg(borderWidth)
        .arg(border.name())
        .arg(borderRadius)
        .arg(fontSize)
        .arg(bold ? "bold" : "normal")
        .arg(background.darker(115).name())
        .arg(background.darker(115).name());
  }
};

inline constexpr int kKeyFontSize = 22;

inline CButtonStyle keyButtonStyle(const QColor& bg) {
  CButtonStyle s;
  s.background = bg;
  s.border = QColor(136, 136, 136);
  s.borderWidth = 1;
  s.borderRadius = 4;
  s.fontSize = kKeyFontSize;
  s.bold = false;
  return s;
}

inline CButtonStyle fingerButtonStyle(const QColor& bg, const QColor& border,
                                      int borderWidth, bool bold) {
  CButtonStyle s;
  s.background = bg;
  s.border = border;
  s.borderWidth = borderWidth;
  s.borderRadius = 0;
  s.fontSize = 18;
  s.bold = bold;
  return s;
}

inline CButtonStyle activeLayoutToggleStyle(const QColor& bg,
                                            const QColor& border,
                                            const QColor& text) {
  CButtonStyle s;
  s.background = bg;
  s.border = border;
  s.borderWidth = 2;
  s.borderRadius = 4;
  s.fontSize = 15;
  s.bold = true;
  s.textColor = text;
  return s;
}

inline CButtonStyle inactiveLayoutToggleStyle(const QColor& bg,
                                              const QColor& border,
                                              const QColor& text) {
  CButtonStyle s;
  s.background = bg;
  s.border = border;
  s.borderWidth = 1;
  s.borderRadius = 4;
  s.fontSize = 15;
  s.bold = false;
  s.textColor = text;
  return s;
}

inline CButtonStyle actionButtonStyle(const QColor& bg, const QColor& border) {
  CButtonStyle s;
  s.background = bg;
  s.border = border;
  s.borderWidth = 1;
  s.borderRadius = 6;
  s.fontSize = 16;
  s.bold = true;
  return s;
}

} // namespace NSViewDetails
} // namespace NSFingers
} // namespace NSApplication
