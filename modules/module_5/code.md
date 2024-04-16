```
// Function to check the LED state and turn it off if it's on
void check_and_turn_off_red() {
    if (IN(red).is("on")) {
        IN(red).set("off");
    }
    do_later(5000, check_and_turn_off_red); // Schedule the next check in 5 seconds
}

void start() {
    check_and_turn_off_red(); // Start checking the red LED state every 5 seconds
};
