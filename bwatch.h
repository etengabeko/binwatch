#ifndef BINARY_WATCH_BWATCH_H
#define BINARY_WATCH_BWATCH_H

#include <QWidget>
#include <QHash>

class QLabel;
class QTimer;

namespace Ui {
  class BinaryWatchWidget;
}

namespace binwatch
{
class Led
{
public:
  explicit Led(QLabel* label = nullptr);

  void turnOn();
  void turnOff();

private:
  QLabel* label_;

};

class BinaryWatch : public QWidget
{
  Q_OBJECT

  enum class Level
  {
    AM,
    PM,
    H8,
    H4,
    H2,
    H1,
    M32,
    M16,
    M8,
    M4,
    M2,
    M1,
    S32,
    S16,
    S8,
    S4,
    S2,
    S1
  };

public:
  explicit BinaryWatch(QWidget* parent = 0);
  ~BinaryWatch();

private slots:
  void slotUpdateState();

private:
  void initLeds();

  void updateHours(int hours);
  void updateMinutes(int minutes);
  void updateSeconds(int seconds);

  void hoursTurnOff();
  void minutesTurnOff();
  void secondsTurnOff();

private:
  Ui::BinaryWatchWidget* ui_;
  QTimer* updTimer_;
  QHash<Level, Led> leds_;

  friend uint qHash(const binwatch::BinaryWatch::Level& level)
  {
    return qHash(static_cast<int>(level));
  }
};

} // binwatch

#endif //BINARY_WATCH_BWATCH_H
