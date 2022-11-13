FROM epitechcontent/epitest-docker
WORKDIR /home/R-TYPE
COPY . .
CMD apt-get update && apt-get install -y cmake g++ libudev-dev pip pkg-config libgl-dev && sudo pip install conan