#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_SPEECH_EXPERIMENTAL_MAIN_FUNCTIONS_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_SPEECH_EXPERIMENTAL_MAIN_FUNCTIONS_H_
// Initializes all data needed for the example. The name is important, and needs
// to be setup() for Arduino compatibility.
extern "C" void speech_test();

// Runs one iteration of data gathering and inference. This should be called
// repeatedly from the application code. The name needs to be loop() for Arduino
// compatibility.
//extern "C" int person_detect();

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_EXPERIMENTAL_MAIN_FUNCTIONS_H_