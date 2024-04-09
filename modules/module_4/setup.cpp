/* setup.cpp
 * This is the configuration code for a IoTempower node.
 * Here, you define all the devices (and eventually their interactions)
 * connected to the node specified with this directory.
 * If you want to see more device configuration examples,
 * check $IOTEMPOWER_ROOT/examples/running-node-test-setup.cpp
 *
 * Or check out the command reference for potential devices you can add.
 * 
 * This whole comment block can be deleted
 * */
// Припустимо, що ви маєте LED підключений як "blue" у вашій конфігурації
// Для Arduino або сумісних пристроїв

// Налаштування виводу для вбудованого світлодіода, інвертування стану та встановлення початкового стану "ввімкнено"
output(red, ONBOARDLED, "off", "on");
m5stickc_display(console,1,270);


// Функція для блимання світлодіода
void blink() {
    IN(red).toggle(); // Змінює стан світлодіода
    do_later(2000, []() {}); // Запланувати наступне блимання через 2 секунди
};

input(mvmnt_detector, G26, "low", "high")
     .with_threshold(3)
     .on_change([] (Device& dev) {
          if(dev.is("high")) {
              IN(red).set("off");
          }
          if(dev.is("low")) {
              IN(red).set("on");
          }
          return true;
      });



void start() {
    IN(red).set("off");
// Виклик функції blink() для розпочаття блимання
    //blink();
};
