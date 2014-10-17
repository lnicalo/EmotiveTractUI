EmotiveTractUI
==============

C++ Application that allows steering a farm tractor using an Emotiv EPOC headset.

This application explores the use of EMG-based Human-machine interface (HMIs) in the steering of farm tractors. An Emotive EPOC headset, a low-cost human-computer interface (HCI), was employed. This device, by means of 14 saline sensors, measures and processes electromiographic (EMG) and electroencephalographic (EEG) signals from the scalp of the driver. 

The HMI takes into account four muscular events: eyes looking to the right and jaw opened, eyes looking to the right and jaw closed, eyes looking to the left and jaw opened, and eyes looking to the left and jaw closed.

Application description
=======================

Figure 1(a) shows the hardware components of the system and the connections between them. All components were mounted on a 6400 John Deere tractor (Figure 1(b,c)). As mentioned, the HMI model was an EPOC, from the Emotiv Company.

![alt tag](https://raw.githubusercontent.com/lnicalo/EmotiveTractUI/master/figures/architecture.png)
Figure 1. (a) Schematic of the connections between the hardware components of the developed system. (b) Tractor used in the tests. (c) Photo of the driver inside the tractor.

A DC RE-30 Maxon motor was installed to move the steering wheel by means of a reducer gear and a striated pulley. A controller box was specially designed to steer the tractor continuously according to the commanded orders sent by the laptop [81]. To achieve the desired angle, the box uses fuzzy logic control technology to power the DC motor by means of a PWM signal. This controller box measures the steering angle with a magnetic encoder.

An R4 Trimble receiver was used to measure the real trajectories of the results section and to perform the autonomous GPS guidance. The update of positions was configured to a rate of 5 Hz. This receiver employed real time kinematic (RTK) corrections to achieve an estimated precision of 2 cm. The corrections were provided by a virtual reference station (VRS) managed by the ITACyL, a Spanish regional agrarian institute.

A laptop computer ran our developed application, which was continuously: (i) obtaining information from the BCI about the driver brain activity, (ii) sending steering commands to the controller box about the desired steering angle, and (iii) saving the followed trajectory, obtained from the GPS.

Software description
====================

The neuroheadset acquires brain neuro-signals with 14 saline sensors placed on the user scalp. It also integrates two internal gyroscopes to provide user head position information. The communication of this device with a PC occurs wirelessly by means of a USB receiver.

The C++ application receives the processed user brain information through the Emotiv API and steers the tractor through the controller box. This application was configured to train some events according to the flow chart of Figure 2(a), and then, according to the flow chart of Figure 2(b), to operate with these events to steer the tractor. The chosen events in the developed application were four combinations of muscle movements:

* the user eyes looking to the left when the user’s jaw is open;
* the user eyes looking to the right when the user’s jaw is open;
* the user eyes looking to the left when the user’s jaw is closed;
* the user eyes looking to the right when the user’s jaw is closed.

![alt tag](https://raw.githubusercontent.com/lnicalo/EmotiveTractUI/master/figures/flowChartTraining.png)
Figure 2. Simplified flow chart of the (a) system training of the four events that the BCI has to detect and (b) system test following a trajectory with the tractor. 

The test driver was trained to use these events. In the training process, the EmoEngine analyzes the driver brainwaves to achieve a personalized signature of each particular event as well as one of a neutral background state. These signatures are stored in the EmoEngine memory. In the tractor steering process, the EmoEngine analyzes in real time the brainwaves acquired to detect signatures that match one of the previously stored signatures in the EmoEngine memory, and when this occurs, it communicates to the application that a specific event with a specific power emanated from the user brain.

Results
======

To see the application in action, watch the following video: http://www.youtube.com/watch?v=O5jYRoBJml8

[![ScreenShot](https://raw.githubusercontent.com/lnicalo/EmotiveTractUI/master/figures/screeshotApplication.jpg)](http://www.youtube.com/watch?v=O5jYRoBJml8)
