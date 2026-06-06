#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>

using namespace std;
using namespace cv;

string pixelToASCII(int pixel_intensity)
{
    const string ASCII_CHARS = "   ._-=+*!&#%$@";

    return string(
        1,
        ASCII_CHARS[
            pixel_intensity * (ASCII_CHARS.size() - 1) / 255
        ]
    );
}

int main()
{
    string video_path = "path_to_your_video.mp4";

    VideoCapture cap(video_path);

    if (!cap.isOpened())
    {
        cerr << "Error opening video stream or file" << endl;
        return -1;
    }

    double fps = cap.get(CAP_PROP_FPS);

    if (fps <= 0)
        fps = 30;

    cout << "FPS: " << fps << endl;

    int frame_duration_ms = static_cast<int>(1000 / fps);

    int width = 250;
    int height = 50;

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    cout << frame_width << " " << frame_height << endl;

    height = (width * frame_height / frame_width) * 0.4194;

    Mat frame, gray_frame, resized_frame;

    while (true)
    {
        cap >> frame;

        if (frame.empty())
            break;

        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);

        resize(
            gray_frame,
            resized_frame,
            Size(width, height),
            0,
            0,
            INTER_LINEAR
        );

        string ascii_frame;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ascii_frame += pixelToASCII(
                    resized_frame.at<uchar>(i, j)
                );
            }

            ascii_frame += "\n";
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << ascii_frame;

        this_thread::sleep_for(
            chrono::milliseconds(frame_duration_ms)
        );
    }

    cap.release();

    return 0;
}