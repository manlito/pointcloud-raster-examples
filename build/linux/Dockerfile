FROM ubuntu:18.10

# Install: cmake, which depengs on c++ compiler. Also liblas for LAS png support. 
# PNG to enable saving to images
RUN apt update && apt install -y \
    cmake \
    git \
    liblas-c-dev \
    liblas-dev \
    libpng-dev \
    && rm -rf /var/lib/apt/lists/

# Build and install google-test
RUN git clone --branch release-1.8.1 https://github.com/google/googletest /tmp/googletest \
    && mkdir -p /tmp/googletest-build \
    && cd /tmp/googletest-build \
    && cmake -DCMAKE_BUILD_TYPE=Release /tmp/googletest \
    && make \
    && make install \
    && rm -rf /tmp/googletest*

# Build and install pointcloud-raster
RUN git clone https://github.com/manlito/pointcloud-raster /tmp/pointcloud-raster \
    && mkdir -p /tmp/pointcloud-raster-build \
    && cd /tmp/pointcloud-raster-build/ \
    && cmake \
        -D CMAKE_BUILD_TYPE=Release \
        -D POINTCLOUD_RASTER_TEST_OUTPUT=/tmp/pointcloud-raster-build \
        -D POINTCLOUD_RASTER_BUILD_TESTS=On \
        -D POINTCLOUD_RASTER_LAS_SUPPORT=On \
        -D POINTCLOUD_RASTER_PNG_SUPPORT=On \
        /tmp/pointcloud-raster \
    && make \
    && make test \
    && make install \
    && rm -rf /tmp/pointcloud-raster*
 
# Build examples
ADD examples /examples

RUN mkdir -p /examples/rasterize-txt-build \
    && cd /examples/rasterize-txt-build/ \
    && cmake \
        -D CMAKE_BUILD_TYPE=Release \
        /examples/rasterize-txt \
    && make \
