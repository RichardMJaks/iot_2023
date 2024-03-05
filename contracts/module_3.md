Agreement:

As students in this class, we agree to fulfill and present the results of a selection of the following tasks (we are picking at least 3 of the optional tasks):

- (M) Set up a team network infrastructure with:
  - Fill in the form [Form Link](https://forms.gle/Pvaw8h5CDU1GrySaA) when you pick-up hardware from us. I.e (Laptop or Raspberry Pi)
  - Set up Accesspoint using an old laptop (done in the classroom). If you prefer more advanced alternatives, you can talk to us. Possible to use an Openwrt router, Raspberry Pi, Atomic Pi, and ESP AP.

- (O) Button to LED directly on the microcontroller. (Resistance, PULLUP/PULLDOWN, V.Divider later).
  - Read more about PULLUP/PULLDOWN resistors.
  - What is the option INPUT_PULLUP?
- Computer (browser or phone) to Microcontroller via Webrequest.
  - (O) Install webhook, flask, or express and generate memes and/or jokes on request with browser and curl or httpie. Use at least two different forms of requests (get/put).
  - (M) Computer (browser or phone) to microcontroller onboard LED via Web request.
  - (O) WiFi and HTTP on the microcontroller consume the web endpoint of another microcontroller. The button turns on the onboard LED on the other.
  - (O) Button to Webhook (output locally on stdout).
  - (O) Button to Webhook, Webhook to curl to Led. (Integration step).
    - What is the advantage of having a gateway in the middle?
  - (O) Add more hardware: the second node with a button to change colors on an RGB led.

- (M) SSH key exchange so that every team member can log in without a password.
- (M) Central team git repository on the gateway with the option to pull - small stack to automate the pull via SSH from one of your laptops.
- (O) Create an easy way to display web dashboards.
  - Kiosk mode for the browser to show one particular URL. Best on a dedicated browser profile or tablet/ old phone.
