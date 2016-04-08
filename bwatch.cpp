#include "bwatch.h"
#include "ui_bwatch.h"

#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QTime>
#include <QTimer>

namespace {

const QPixmap& turnedOnLed()
{
  static QPixmap pxm(":/icons/ledred.png");
  return pxm;
}

const QPixmap& turnedOffLed()
{
  static QPixmap pxm(":/icons/ledgrey.png");
  return pxm;
}

}

namespace binwatch {

BinaryWatch::BinaryWatch(QWidget* parent) :
  QWidget(parent),
  ui_(new Ui::BinaryWatchWidget()),
  updTimer_(new QTimer(this))
{
  ui_->setupUi(this);
  connect(updTimer_, SIGNAL(timeout()), SLOT(slotUpdateState()));

  initLeds();
  updTimer_->start(500);
}

BinaryWatch::~BinaryWatch()
{
  delete ui_;
  ui_ = 0;
}

void BinaryWatch::initLeds()
{
  leds_.insert(Level::AM, Led(ui_->amLed));
  leds_.insert(Level::PM, Led(ui_->pmLed));

  leds_.insert(Level::H8, Led(ui_->hour8Led));
  leds_.insert(Level::H4, Led(ui_->hour4Led));
  leds_.insert(Level::H2, Led(ui_->hour2Led));
  leds_.insert(Level::H1, Led(ui_->hour1Led));

  leds_.insert(Level::M32, Led(ui_->minute32Led));
  leds_.insert(Level::M16, Led(ui_->minute16Led));
  leds_.insert(Level::M8, Led(ui_->minute8Led));
  leds_.insert(Level::M4, Led(ui_->minute4Led));
  leds_.insert(Level::M2, Led(ui_->minute2Led));
  leds_.insert(Level::M1, Led(ui_->minute1Led));

  leds_.insert(Level::S32, Led(ui_->second32Led));
  leds_.insert(Level::S16, Led(ui_->second16Led));
  leds_.insert(Level::S8, Led(ui_->second8Led));
  leds_.insert(Level::S4, Led(ui_->second4Led));
  leds_.insert(Level::S2, Led(ui_->second2Led));
  leds_.insert(Level::S1, Led(ui_->second1Led));
}

void BinaryWatch::slotUpdateState()
{
  QTime time = QTime::currentTime();
  updateHours(time.hour());
  updateMinutes(time.minute());
  updateSeconds(time.second());
}

void BinaryWatch::updateHours(int hours)
{
  hoursTurnOff();

  if (hours < 12) {
    leds_[Level::AM].turnOn();
  }
  else {
    leds_[Level::PM].turnOn();
    if (hours != 12) {
      hours -= 12;
    }
  }

  if (hours-8 >= 0) {
    leds_[Level::H8].turnOn();
    hours -= 8;
  }
  if (hours-4 >= 0) {
    leds_[Level::H4].turnOn();
    hours -= 4;
  }
  if (hours-2 >= 0) {
    leds_[Level::H2].turnOn();
    hours -= 2;
  }
  if (hours-1 >= 0) {
    leds_[Level::H1].turnOn();
  }
}

void BinaryWatch::updateMinutes(int minutes)
{
  minutesTurnOff();

  if (minutes-32 >= 0) {
    leds_[Level::M32].turnOn();
    minutes -= 32;
  }
  if (minutes-16 >= 0) {
    leds_[Level::M16].turnOn();
    minutes -= 16;
  }
  if (minutes-8 >= 0) {
    leds_[Level::M8].turnOn();
    minutes -= 8;
  }
  if (minutes-4 >= 0) {
    leds_[Level::M4].turnOn();
    minutes -= 4;
  }
  if (minutes-2 >= 0) {
    leds_[Level::M2].turnOn();
    minutes -= 2;
  }
  if (minutes-1 >= 0) {
    leds_[Level::M1].turnOn();
  }
}

void BinaryWatch::updateSeconds(int seconds)
{
  secondsTurnOff();

  if (seconds-32 >= 0) {
    leds_[Level::S32].turnOn();
    seconds -= 32;
  }
  if (seconds-16 >= 0) {
    leds_[Level::S16].turnOn();
    seconds -= 16;
  }
  if (seconds-8 >= 0) {
    leds_[Level::S8].turnOn();
    seconds -= 8;
  }
  if (seconds-4 >= 0) {
    leds_[Level::S4].turnOn();
    seconds -= 4;
  }
  if (seconds-2 >= 0) {
    leds_[Level::S2].turnOn();
    seconds -= 2;
  }
  if (seconds-1 >= 0) {
    leds_[Level::S1].turnOn();
  }
}

void BinaryWatch::hoursTurnOff()
{
  leds_[Level::AM].turnOff();
  leds_[Level::PM].turnOff();
  leds_[Level::H8].turnOff();
  leds_[Level::H4].turnOff();
  leds_[Level::H2].turnOff();
  leds_[Level::H1].turnOff();
}

void BinaryWatch::minutesTurnOff()
{
  leds_[Level::M32].turnOff();
  leds_[Level::M16].turnOff();
  leds_[Level::M8].turnOff();
  leds_[Level::M4].turnOff();
  leds_[Level::M2].turnOff();
  leds_[Level::M1].turnOff();
}

void BinaryWatch::secondsTurnOff()
{
  leds_[Level::S32].turnOff();
  leds_[Level::S16].turnOff();
  leds_[Level::S8].turnOff();
  leds_[Level::S4].turnOff();
  leds_[Level::S2].turnOff();
  leds_[Level::S1].turnOff();
}

Led::Led(QLabel* label) :
  label_(label)
{
}

void Led::turnOn()
{
  Q_CHECK_PTR(label_);

  label_->setPixmap(::turnedOnLed());
}

void Led::turnOff()
{
  Q_CHECK_PTR(label_);

  label_->setPixmap(::turnedOffLed());
}

} // binwatch
