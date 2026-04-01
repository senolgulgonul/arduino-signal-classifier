# Arduino Signal Classifier — Neural Network on Arduino Uno

A project that trains a neural network in Python and runs the weights directly on an Arduino Uno.

## What Does It Do?

Classifies analog signals from the A0 pin into 4 categories:
- **rising** — increasing signal
- **falling** — decreasing signal
- **U** — decreasing then increasing
- **inverted_U** — increasing then decreasing

Results are displayed in real-time on the Serial Plotter.

## Architecture
```
Python (PC)                    Arduino Uno
-----------                    -----------
Generate synthetic data        Forward pass only
Train neural network  ----->   W1 (16x8) + b1
Export weights                 W2 (8x4)  + b2
model_weights.h                Output: Serial Plotter
```

## Neural Network
```
Input:   16 measurement points (A0, 0-1023)
Hidden:  8 neurons (ReLU)
Output:  4 classes
Memory:  ~688 bytes (fits in Arduino Uno's 2KB RAM!)
```

## Files

- `train.ipynb` — Python training code (PyTorch)
- `sinyal_siniflandirici/sinyal_siniflandirici.ino` — Arduino sketch
- `sinyal_siniflandirici/model_weights.h` — Trained weights (C array)

## Requirements

### Python
```
pip install numpy scikit-learn matplotlib torch
```

### Arduino
- Arduino Uno
- Arduino IDE

## How To Use

1. Run `train.ipynb` — model is trained, `model_weights.h` is generated
2. Open `sinyal_siniflandirici.ino` in Arduino IDE
3. Upload to Arduino Uno
4. Open Serial Plotter at 115200 baud
5. Connect a potentiometer to A0 and turn it!

## How It Works

The neural network is trained in Python (PyTorch). The learned weights are exported
as C float arrays into `model_weights.h`. The Arduino only performs the **forward pass** —
just multiply and add operations. No backpropagation, no training on the device.
This keeps memory usage minimal.

## Trigger Logic

Continuous sampling is not used. Measurement starts when the A0 value changes by
more than 10 ADC units. 16 samples are collected at 100ms intervals (1.6 seconds total),
then the signal is classified and results are sent to the Serial Plotter.

## Results

- Training accuracy: 100%
- Test accuracy: 100%
- Arduino memory usage: ~688 bytes
