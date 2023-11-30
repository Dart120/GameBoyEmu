# syntax=docker/dockerfile:1
FROM ubuntu:20.04
RUN apt-get update && \
      apt-get -y install sudo
ENV DEBIAN_FRONTEND=noninteractive
RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo
RUN sudo apt-get update -y
# Set an environment variable for XDG_RUNTIME_DIR
ENV XDG_RUNTIME_DIR=/tmp/runtime-dir

# Create the directory and ensure correct permissions
RUN mkdir -p $XDG_RUNTIME_DIR && chmod 0700 $XDG_RUNTIME_DIR
RUN sudo apt-get install -y python3-pip
RUN apt-get install -y libsdl2-dev --fix-missing
RUN pip3 install conan==1.54.0
WORKDIR /app
COPY . .
RUN apt-get install -y cmake
RUN apt-get install -y clang-tidy
RUN apt-get install -y vim
RUN vim build.sh -c "set ff=unix" -c ":wq"
RUN vim run.sh -c "set ff=unix" -c ":wq"
# RUN ./build.sh
# RUN yarn install --production
# CMD ["node", "src/index.js"]
# EXPOSE 3000