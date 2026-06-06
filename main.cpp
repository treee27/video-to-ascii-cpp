#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

using namespace std;
using namespace cv;

// Convert pixel intensity to ASCII character
string pixelToASCII(int pixel_intensity)
{
    const string ASCII_CHARS =
        " .'`^\",:;Il!i~+_-?][}{1)(|\\/*tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    return string(
        1,
        ASCII_CHARS[
            pixel_intensity * (ASCII_CHARS.size() - 1) / 255
        ]
    );
}

int main()
{
    string video_path = "vid1.mp4";

    VideoCapture cap(video_path);

    if (!cap.isOpened())
    {
        cerr << "Error opening video file!" << endl;
        return -1;
    }

    double fps = cap.get(CAP_PROP_FPS);

    if (fps <= 0)
        fps = 30;

    cout << "FPS: " << fps << endl;

    int frame_duration_ms = static_cast<int>(1000.0 / fps);

    int width = 200;

    int frame_width = static_cast<int>(
        cap.get(CAP_PROP_FRAME_WIDTH));

    int frame_height = static_cast<int>(
        cap.get(CAP_PROP_FRAME_HEIGHT));

    int height =
        static_cast<int>(
            (width * frame_height /
             static_cast<double>(frame_width)) *
            0.55);

    cout << "Video Resolution: "
         << frame_width
         << " x "
         << frame_height
         << endl;

    Mat frame;
    Mat gray_frame;
    Mat edges;
    Mat enhanced_frame;
    Mat resized_frame;

    while (true)
    {
        cap >> frame;

        if (frame.empty())
            break;

        // Convert to grayscale
        cvtColor(
            frame,
            gray_frame,
            COLOR_BGR2GRAY);

        // Detect edges
        Canny(
            gray_frame,
            edges,
            50,
            150);

        // Mix grayscale + edges
        addWeighted(
            gray_frame,
            0.8,
            edges,
            0.2,
            0,
            enhanced_frame);

        // Resize for terminal
        resize(
            enhanced_frame,
            resized_frame,
            Size(width, height),
            0,
            0,
            INTER_AREA);

        string ascii_frame;

        ascii_frame.reserve(
            width * height + height);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ascii_frame +=
                    pixelToASCII(
                        resized_frame.at<uchar>(i, j));
            }

            ascii_frame += '\n';
        }

        // Fast terminal clear
        cout << "\033[2J\033[H";

        cout << ascii_frame << flush;

        this_thread::sleep_for(
            chrono::milliseconds(
                frame_duration_ms));
    }

    cap.release();

    return 0;
}