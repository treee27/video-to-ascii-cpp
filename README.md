# Video to ASCII Converter (C++)

A real-time Video-to-ASCII Converter built using **C++** and **OpenCV**. The application reads frames from a video file, processes them using image-processing techniques, and converts each frame into ASCII art that is rendered directly in the terminal.

This project demonstrates concepts from **Computer Vision**, **Image Processing**, **Video Processing**, and **Real-Time Rendering**.

---

## Features

- Real-time video-to-ASCII conversion
- Supports video file input
- Frame-by-frame processing using OpenCV
- Grayscale image conversion
- Edge enhancement using Canny Edge Detection
- Adjustable ASCII resolution
- FPS synchronization for smooth playback
- Terminal-based rendering
- Cross-platform support (Windows, Linux, macOS)

---

## Demo

### Input

```text
Video File (MP4)
```

### Output

```text
@@@@@@@@@@@@@@@%%%%%%#######
@@@@@@@@@@@@@%%%%%%%######**
@@@@@@@@@@%%%%%%%#####******
@@@@@@@%%%%%%%#####*********
@@@@%%%%%%%#####************
```

The output updates continuously to create an ASCII-art video effect inside the terminal.

---

## Project Structure

```text
video-to-ascii-cpp/
│
├── main.cpp
├── build.sh
├── compile_commands.json
├── vid1.mp4
├── README.md
└── ascii.exe
```

---

## Technologies Used

### Language

- C++

### Libraries

- OpenCV 4.x

### Concepts

- Computer Vision
- Image Processing
- Video Processing
- Grayscale Conversion
- Edge Detection
- Real-Time Rendering
- Terminal Graphics

---

## How It Works

The application follows the pipeline below:

```text
Video File
     │
     ▼
Read Frame
     │
     ▼
Convert to Grayscale
     │
     ▼
Edge Detection (Canny)
     │
     ▼
Resize Frame
     │
     ▼
Pixel Intensity Mapping
     │
     ▼
ASCII Character Generation
     │
     ▼
Terminal Rendering
```

---

## ASCII Mapping

Each grayscale pixel intensity (0–255) is mapped to an ASCII character.

Example character set:

```cpp
const string ASCII_CHARS =
" .'`^\",:;Il!i~+_-?][}{1)(|\\/*tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
```

### Intensity Mapping

| Pixel Intensity | ASCII Character |
|---------------|----------------|
| Dark | Space |
| Low | . |
| Medium | + |
| High | # |
| Bright | @ |

---

## Installation

### Prerequisites

- C++ Compiler (g++)
- OpenCV 4.x
- MSYS2 MinGW64 (Windows)

---

## OpenCV Installation (Windows - MSYS2)

Update MSYS2:

```bash
pacman -Syu
```

Install OpenCV:

```bash
pacman -S mingw-w64-x86_64-opencv
```

Verify installation:

```bash
pkg-config --modversion opencv4
```

Expected output:

```text
4.x.x
```

---

## Build Instructions

### Using build.sh

```bash
chmod +x build.sh
./build.sh
```

### Manual Compilation

```bash
g++ main.cpp -o ascii.exe -std=c++11 $(pkg-config --cflags --libs opencv4)
```

---

## Running the Application

```bash
./ascii.exe
```

---

## Configuration

### Video File

Modify:

```cpp
string video_path = "vid1.mp4";
```

to use a different video.

---

### ASCII Resolution

Modify:

```cpp
int width = 200;
```

Higher values increase quality but require more terminal rendering power.

Recommended:

```cpp
width = 180 - 300
```

---

## Core OpenCV Functions Used

### VideoCapture

```cpp
VideoCapture cap(video_path);
```

Reads video frames.

---

### cvtColor

```cpp
cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
```

Converts RGB frame into grayscale.

---

### Canny Edge Detection

```cpp
Canny(gray_frame, edges, 50, 150);
```

Enhances object boundaries.

---

### addWeighted

```cpp
addWeighted(
    gray_frame,
    0.8,
    edges,
    0.2,
    0,
    enhanced_frame
);
```

Combines grayscale image with edge information.

---

### resize

```cpp
resize(
    enhanced_frame,
    resized_frame,
    Size(width, height),
    0,
    0,
    INTER_AREA
);
```

Resizes frame for terminal rendering.

---

## Performance Optimizations

- FPS-based playback synchronization
- Efficient ASCII character mapping
- Frame resizing before rendering
- ANSI terminal clearing instead of system calls
- Memory reuse using OpenCV matrices

---

## Example Output

```text
@@@@@@%%%%%%%%##########****
@@@@%%%%%%%%#########*******
@@%%%%%%%%########**********
%%%%%%%%########************
%%%%%%%#######**************
```

---

## Future Improvements

- Webcam support
- Colored ASCII rendering
- Live camera streaming
- GIF support
- Multi-threaded frame processing
- Terminal auto-scaling
- Adjustable brightness and contrast
- Export ASCII video to text files
- GUI version using OpenCV windows

---

## Skills Demonstrated

- C++
- OpenCV
- Computer Vision
- Image Processing
- Video Processing
- Real-Time Systems
- Performance Optimization
- Terminal Rendering

---

## Resume Description

**Video to ASCII Converter | C++, OpenCV**

- Developed a real-time video-to-ASCII conversion system using C++ and OpenCV.
- Implemented grayscale conversion, edge enhancement, and pixel-to-character mapping techniques.
- Processed video frames and rendered ASCII animations directly in the terminal.
- Optimized rendering through frame resizing and FPS-based synchronization.
- Demonstrated practical applications of computer vision and image processing concepts.

---

## License

This project is licensed under the MIT License.

Feel free to use, modify, and distribute this project.