# Vivid
<img width="1080" alt="Screenshot 2023-02-03 at 4 12 49 PM" src="https://user-images.githubusercontent.com/45993519/218171952-624d8dda-5c49-4fe4-942f-301deaa502f4.png">

A renderer providing a user friendly interface for rendering 2D and 3D on OpenGL.


## 3D rendering
<img width="1512" alt="Screenshot 2023-01-14 at 9 29 19 PM" src="https://user-images.githubusercontent.com/45993519/212481445-95819cdf-72d6-4744-b5eb-12a8accfff09.png">

<img width="1031" alt="image" src="https://user-images.githubusercontent.com/45993519/191841279-a73a3ee9-94bb-4d39-bf76-8676b5948d13.png">

## 2D Rendering
<img width="1512" alt="Screenshot 2023-01-26 at 11 33 50 PM" src="https://user-images.githubusercontent.com/45993519/214913901-df2fa687-f1dc-460e-ae1d-2d4c13a074f2.png">

# Devlopment

## Dependencies
[CMake](https://cmake.org/install/) and [Ninja](https://ninja-build.org/).

## Build 

```
git clone git@github.com:Aviii06/Vivid.git
cd newton
git submodule update --init --recursive
mkdir build && cd build
cmake .. -G Ninja
ninja -j8
./marchingSquare
```
