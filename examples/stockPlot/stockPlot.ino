#include <GyverPortal.h>
#define PLOT_SIZE 100

int16_t arr[2][PLOT_SIZE];
GPunix dates[PLOT_SIZE];
const char *names[] = {"kek", "puk",};

// билдер страницы
void build() {
  String s;
  BUILD_BEGIN(s);
  add.THEME(GP_DARK);

  add.PLOT_STOCK_DARK<2, PLOT_SIZE>("plot", names, dates, arr);
  BUILD_END();
}

GyverPortal portal;

void setup() {
  GPunix startDate;
  startDate.set(2022, 1, 22, 21, 59, 00);
  dates[PLOT_SIZE-1] = startDate;
  for (int i = 0; i < PLOT_SIZE; i++) {
    GPaddInt(i*2, arr[0], PLOT_SIZE);
    GPaddInt(i*5, arr[1], PLOT_SIZE);
    GPaddUnix(5, dates, PLOT_SIZE);
  }

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  // подключаем билдер и запускаем
  portal.attachBuild(build);
  portal.start();
}

void loop() {
  portal.tick();

  static uint32_t tmr;
  if (millis() - tmr >= 5000) {
    tmr = millis();
    GPaddInt(random(100), arr[0], PLOT_SIZE);
    GPaddInt(random(100), arr[1], PLOT_SIZE);
    GPaddUnix(5, dates, PLOT_SIZE);
  }
}
