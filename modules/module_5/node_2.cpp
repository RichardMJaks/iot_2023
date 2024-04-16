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

led(blue, ONBOARDLED, "off", "on");

output(lock, D1, "off", "on").set("off").invert();

void turn_off() {
    IN(lock).set("off");
}

void check_and_turn_off_lock() {
    if (IN(lock).is("on")) {
            do_later(3000, turn_off); // Schedule the next check in 5 seconds
    }
    do_later(0, check_and_turn_off_lock); // Schedule the next check in 5 seconds
}


void start() {
    check_and_turn_off_lock(); // Start checking the red LED state every 5 seconds
};

