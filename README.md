# qt_video_face_detection
- a Qt based video face detection with ability to cut out images 
- and save images with pixelation of faces if needed

# Build
- `mkdir build && cd build`
- `cmake ..`
- `make`

# Issues
- still got some bugs due to multithreading
  - caused crashes 
- pixelation isn't working working fine
  - maybe also related to multihreaded environment
