git clone --depth 1 git@github.com:spack/spack.git
source ./spack/share/spack/setup-env.sh
spack install rapidjson
spack load rapidjson cmake

mkdir build && cd build
cmake ..
make