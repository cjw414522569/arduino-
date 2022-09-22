
#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#define BLINKER_PRINT Serial

#include <Blinker.h>

char auth[] = "9811aeb3596f";
char ssid[] = "CU_c6Yj";
char pswd[] = "ajrxg8bg";

int GPIO = D1; //定义继电器输入引脚

// 新建组件对象
BlinkerButton Button1("btn");

void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(GPIO, HIGH);

        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(GPIO, LOW);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}
// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(GPIO, !digitalRead(GPIO));
}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
}

void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif

    // 初始化有LED的IO
    pinMode(GPIO, OUTPUT);
    digitalWrite(GPIO, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
    BlinkerMIOT.attachPowerState(miotPowerState);
    
}

void loop() {
    Blinker.run();
}
